/***************************************************************************//**
 * @file custom_adv.c
 * @brief customize advertising
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <string.h>
#include "custom_adv.h"
#include "stdio.h"

void fill_adv_packet(CustomAdv_t *pData, uint8_t flags, uint8_t temp_byte1, uint8_t temp_byte2, uint8_t humid_byte1, uint8_t humid_byte2, uint16_t period, char *name)
{
  int n;

  pData->len_flags = 0x02;
  pData->type_flags = 0x01;
  pData->val_flags = flags;

  pData->len_manuf = 9;  // 1+4+2 bytes for type, temp/humid, and period
  pData->type_manuf = 0xFF;

  pData->temp_byte1 = temp_byte1;
  pData->temp_byte2 = temp_byte2;
  pData->humid_byte1 = humid_byte1;
  pData->humid_byte2 = humid_byte2;

  pData->period = period;

  // Name length, excluding null terminator
  n = strlen(name);
  if (n > NAME_MAX_LENGTH) {
    // Incomplete name
    pData->type_name = 0x08;
  } else {
    pData->type_name = 0x09;
  }

  strncpy(pData->name, name, NAME_MAX_LENGTH);

  if (n > NAME_MAX_LENGTH) {
    n = NAME_MAX_LENGTH;
  }

  pData->len_name = 1 + n; // length of name element is the name string length + 1 for the AD type

  // Calculate total length of advertising data
  pData->data_size = 3 + (1 + pData->len_manuf) + (1 + pData->len_name);
}

void start_adv(CustomAdv_t *pData, uint8_t advertising_set_handle)
{
  sl_status_t sc;
  // Set custom advertising payload 
  sc = sl_bt_legacy_advertiser_set_data(advertising_set_handle, 0, pData->data_size, (const uint8_t *)pData);
  app_assert(sc == SL_STATUS_OK,
                "[E: 0x%04x] Failed to set advertising data\n",
                (int)sc);

  // Start advertising using custom data 
  sc = sl_bt_legacy_advertiser_start(advertising_set_handle, sl_bt_legacy_advertiser_connectable);
  app_assert(sc == SL_STATUS_OK,
                  "[E: 0x%04x] Failed to start advertising\n",
                  (int)sc);
}

void update_adv_data(CustomAdv_t *pData, uint8_t advertising_set_handle, uint8_t temp_byte1, uint8_t temp_byte2, uint8_t humid_byte1, uint8_t humid_byte2, uint16_t period)
{
  sl_status_t sc;
  // Update the variable fields in the custom advertising packet
  pData->temp_byte1 = temp_byte1;
  pData->temp_byte2 = temp_byte2;
  pData->humid_byte1 = humid_byte1;
  pData->humid_byte2 = humid_byte2;

  pData->period = period;

  // Set custom advertising payload 
  sc = sl_bt_legacy_advertiser_set_data(advertising_set_handle, 0, pData->data_size, (const uint8_t *)pData);
  app_assert(sc == SL_STATUS_OK,
                  "[E: 0x%04x] Failed to set advertising data\n",
                  (int)sc);
}
