/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "em_common.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "gatt_db.h"
#include "app.h"
#include "app_log.h"
#include "custom_adv.h"
#include "app_timer.h"
#include "globals.h"
#include "sl_status.h"
#include "sl_bt_api.h"
#include "gatt_db.h" // Ensure this is included

CustomAdv_t sData; // Our custom advertising data stored here

// This action creates a memory area for our "timer variable".
static app_timer_t update_timer;

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;
static uint8_t connection_handle = 0xff;

uint8_t temp_byte1 = 0;
uint8_t temp_byte2 = 0;
uint8_t humid_byte1 = 0;
uint8_t humid_byte2 = 0;

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
static void update_timer_cb(app_timer_t *timer, void *data)
{
  (void)data;
  (void)timer;
  // You can update other data in this void
  update_adv_data(&sData, advertising_set_handle, temp_byte1, temp_byte2, humid_byte1, humid_byte2, ble_broadcast_cycle);
  app_log("Updated advertising data\r\n");
}

SL_WEAK void app_init(void)
{
  sl_status_t sc;
  // Init IRQ update data.
  sc = app_timer_start(&update_timer,
                             1*1000,              // ms
                             update_timer_cb,
                             NULL,
                             true);
  app_assert_status(sc);
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;
  uint8_t system_id[8];

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:

      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      app_assert_status(sc);

      // Pad and reverse unique ID to get System ID.
      system_id[0] = address.addr[5];
      system_id[1] = address.addr[4];
      system_id[2] = address.addr[3];
      system_id[3] = 0xFF;
      system_id[4] = 0xFE;
      system_id[5] = address.addr[2];
      system_id[6] = address.addr[1];
      system_id[7] = address.addr[0];

      sc = sl_bt_gatt_server_write_attribute_value(gattdb_system_id,
                                                   0,
                                                   sizeof(system_id),
                                                   system_id);
      app_assert_status(sc);

      // Create an advertising set.
      sc = sl_bt_advertiser_create_set(&advertising_set_handle);
      app_assert_status(sc);

      // Set advertising interval to the initial period.
      sc = sl_bt_advertiser_set_timing(
        advertising_set_handle,
        1000 * 1.6, // min. adv. interval (milliseconds * 1.6)
        1000 * 1.6, // max. adv. interval (milliseconds * 1.6)
        0,   // adv. duration
        0);  // max. num. adv. events
      app_assert_status(sc);

      // Setting channel
      sl_bt_advertiser_set_channel_map(advertising_set_handle, 7);
      app_assert_status(sc);

      // Add data to Adv packet
      fill_adv_packet(&sData, FLAG, temp_byte1, temp_byte2, humid_byte1, humid_byte2, ble_broadcast_cycle, "An");
      app_log("fill_adv_packet completed\r\n");

      // Start advertise
      start_adv(&sData, advertising_set_handle);
      app_log("Started advertising\r\n");

      app_log("System boot\r\n");
      break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      connection_handle = evt->data.evt_connection_opened.connection;
      app_log("Connection opened\r\n");
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      // Generate data for advertising
      sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                                 sl_bt_advertiser_general_discoverable);
      app_assert_status(sc);

      // Restart advertising after client has disconnected.
      sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                         sl_bt_advertiser_connectable_scannable);
      app_assert_status(sc);

      app_log("Connection closed, advertising restarted\r\n");
      break;

    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}

void send_bluetooth_data(uint8_t temp_byte1, uint8_t temp_byte2, uint8_t humid_byte1, uint8_t humid_byte2, uint32_t period) {
  uint8_t data[8] = {temp_byte1, temp_byte2, humid_byte1, humid_byte2, (uint8_t)(period >> 8), (uint8_t)period, 'N', 'M'};
  sl_bt_gatt_server_send_characteristic_notification(
    connection_handle,
    gattdb_temperature_measurement,
    sizeof(data),
    data);
}
