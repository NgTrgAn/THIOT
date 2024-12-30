/***************************************************************************//**
 * @file main.c
 * @brief main() function.
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
#include "sl_component_catalog.h"
#include "sl_system_init.h"
#include "app.h"
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#endif
#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "sl_system_kernel.h"
#else // SL_CATALOG_KERNEL_PRESENT
#include "sl_system_process_action.h"
#endif // SL_CATALOG_KERNEL_PRESENT

#include "app_log.h"
#include "em_i2c.h"
#include "sl_i2cspm_instances.h"
#include "sl_sleeptimer.h"

// SI7021_Config_Settings Si7021 Configuration Settings
#define SI7021_I2C_DEVICE                (sl_i2cspm_sensor) /**< I2C device used to control the Si7021  */
#define SI7021_I2C_BUS_ADDRESS           0x40               /**< I2C bus address                        */
#define SI7021_DEVICE_ID                 0x15               /**< Si7021 device ID                       */
#define FIRMWARE_REV_1_0                 0xFF
#define FIRMWARE_REV_2_0                 0x20
// Si7021 command macro definitions
#define SI7021_CMD_MEASURE_RH            0xE5               /**< Measure Relative Humidity, Hold Master Mode */
#define SI7021_CMD_MEASURE_RH_NO_HOLD    0xF5               /**< Measure Relative Humidity, No Hold Master Mode */
#define SI7021_CMD_MEASURE_TEMP          0xE3               /**< Measure Temperature, Hold Master Mode */
#define SI7021_CMD_MEASURE_TEMP_NO_HOLD  0xF3               /**< Measure Temperature, No Hold Master Mode */
#define SI7021_CMD_READ_TEMP             0xE0               /**< Read Temperature Value from Previous RH Measurement */
#define SI7021_CMD_RESET                 0xFE               /**< Reset */
#define SI7021_CMD_WRITE_USER_REG1       0xE6               /**< Write RH/T User Register 1 */
#define SI7021_CMD_READ_USER_REG1        0xE7               /**< Read RH/T User Register 1 */
#define SI7021_CMD_WRITE_HEATER_CTRL     0x51               /**< Write Heater Control Register */
#define SI7021_CMD_READ_HEATER_CTRL      0x11               /**< Read Heater Control Register */
#define SI7021_CMD_READ_ID_BYTE1         { 0xFA, 0x0F }       /**< Read Electronic ID 1st Byte */
#define SI7021_CMD_READ_ID_BYTE2         { 0xFC, 0xC9 }       /**< Read Electronic ID 2nd Byte */
#define SI7021_CMD_READ_FW_REV           { 0x84, 0xB8 }       /**< Read Firmware Revision */

uint32_t decode_temp(uint8_t* read_register) {
    uint32_t rhValue;

    // Decode the read register value as per the Si7021 datasheet
    rhValue = ((uint32_t) read_register[0] << 8) + (read_register[1] & 0xfc);

    // Perform the temperature conversion
    // First, do the multiplication and then divide by 65536 to simulate a right shift by 16 bits
    // Finally, subtract the offset
    rhValue = (uint32_t)(((rhValue) * 175.72) / 65536) - 46.85;

    return rhValue;
}


uint8_t crc8(uint8_t *data, uint8_t length) {
    uint8_t crc = 0x00;

    for (uint8_t i = 0; i < length; i++) {
        crc ^= data[i];

        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x31;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

uint16_t crc16(uint8_t *data, uint8_t length) {
    uint16_t crc = 0xFFFF;

    for (uint8_t i = 0; i < length; i++) {
        crc ^= data[i];

        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}


static I2C_TransferReturn_TypeDef SI7021_transaction(uint16_t flag,
                                                     uint8_t *writeCmd,
                                                     uint16_t writeLen,
                                                     uint8_t *readCmd,
                                                     uint16_t readLen)
{
  I2C_TransferSeq_TypeDef seq;
  I2C_TransferReturn_TypeDef ret;

  seq.addr = SI7021_I2C_BUS_ADDRESS << 1;
  seq.flags = flag;

  switch (flag) {
    // Send the write command from writeCmd
    case I2C_FLAG_WRITE:
      seq.buf[0].data = writeCmd;
      seq.buf[0].len  = writeLen;

      break;

    // Receive data into readCmd of readLen
    case I2C_FLAG_READ:
      seq.buf[0].data = readCmd;
      seq.buf[0].len  = readLen;

      break;

    // Send the write command from writeCmd
    // and receive data into readCmd of readLen
    case I2C_FLAG_WRITE_READ:
      seq.buf[0].data = writeCmd;
      seq.buf[0].len  = writeLen;

      seq.buf[1].data = readCmd;
      seq.buf[1].len  = readLen;

      break;

    default:
      return i2cTransferUsageFault;
  }

  // Perform the transfer and return status from the transfer
  ret = I2CSPM_Transfer(SI7021_I2C_DEVICE, &seq);

  return ret;
}

// do nhiet do
static void SI7021_measure(uint32_t *tempData )
{
  I2C_TransferReturn_TypeDef ret;
  uint8_t cmd;
  uint8_t readData[3];

  // Start Read Temperature Value from Previous RH Measurement by writing command to si7021
  cmd = SI7021_CMD_READ_TEMP;
  ret = SI7021_transaction(I2C_FLAG_WRITE_READ, &cmd, 1, readData, 3);
  // Data is ready, decode the RH value
  if(ret == i2cTransferDone){
  *tempData = decode_temp(readData);
  }
}
// hold master mode
static void SI7021_measure_hold(uint32_t *tempData )
{
  I2C_TransferReturn_TypeDef ret;
  uint8_t cmd;
  uint8_t readData[3];

  // Start Read Temperature Value from Previous RH Measurement by writing command to si7021
  cmd = SI7021_CMD_MEASURE_TEMP;
  ret = SI7021_transaction(I2C_FLAG_WRITE_READ, &cmd, 1, readData, 3);
  if(ret == i2cTransferDone){
      uint8_t check_crc = crc8( readData, 2 );
       if (check_crc == readData[2]) {
           app_log("CRC HM measure is true\r\n");
       } else {
           app_log("CRC FAILED\r\n");
       }
       *tempData = decode_temp(readData);
  }
}

static void SI7021_measure_no_hold(uint32_t *tempData)
{
  I2C_TransferReturn_TypeDef ret;
  uint8_t cmd;
  uint8_t readData[3];
  uint32_t timeout;

  // Start no-hold measurement by writing command to si7021
  cmd = SI7021_CMD_MEASURE_TEMP_NO_HOLD;
  ret = SI7021_transaction(I2C_FLAG_WRITE, &cmd, 1, 0, 0);

  // Wait for data to become ready
  timeout = 300;
  while (timeout--) {
    ret = SI7021_transaction(I2C_FLAG_READ, 0, 0, readData, 3);
    if (ret == i2cTransferDone) {
      break;
    } else if (ret == i2cTransferNack) {
      // Si7021 returns a Nack if data not ready
      continue;
    }
  }

  // comment the following code
  uint8_t check_crc = crc8( readData, 2 );

  if (check_crc == readData[2]) {
      app_log("CRC HM measure is true\r\n");
  } else {
      app_log("CRC FAILED\r\n");
  }

  // Data is ready, decode the RH value
  *tempData = decode_temp(readData);
}

static void SI7021_read_serial_number_hold(uint64_t *serialNumber) {
    I2C_TransferReturn_TypeDef ret;
    uint8_t cmd[2];
    uint8_t readData1[8];  // First 4 bytes
    uint8_t readData2[6];  // Next 4 bytes

    // First command to read the first part of the serial number
    cmd[0] = 0xFA;
    cmd[1] = 0x0F;
    ret = SI7021_transaction(I2C_FLAG_WRITE_READ, cmd, 2, readData1, 8);

    if (ret == i2cTransferDone) {
        // Second command to read the next part of the serial number
        // Check CRC 8-bit for each byte in first access
                        for (int i = 0; i < 8; i++) {  // Check first 3 bytes against the 4th byte CRC
                            uint8_t check_crc = crc8(readData1[i], 2);  // Adapt the data and length accordingly
                            if (check_crc == readData1[i+1]) {
                                app_log("CRC 1st ID %d is true\r\n", i);
                            } else {
                                app_log("CRC FAILED for ID %d\r\n", i);
                            }
                        }
        cmd[0] = 0xFC;
        cmd[1] = 0xC9;
        ret = SI7021_transaction(I2C_FLAG_WRITE_READ, cmd, 2, readData2, 6);
        if (ret == i2cTransferDone) {
            uint16_t check_crc16_1 = crc16((readData2[1]<<8|readData2[0]), 4);
                        if (check_crc16_1 == readData2[2]) {
                            app_log("CRC 2nd ID 1st check is true\r\n");
                        } else {
                            app_log("CRC FAILED for 1st check\r\n");
                        }

                        // Second CRC 16-bit check for second access
                        uint16_t check_crc16_2 = crc16((readData2[3]<<8|readData2[4]), 2);
                        if (check_crc16_2 == readData2[5]) {
                            app_log("CRC 2nd ID 2nd check is true\r\n");
                        } else {
                            app_log("CRC FAILED for 2nd check\r\n");
                        }
            // Combine the 8 bytes into a single 64-bit serial number
            *serialNumber = ((uint64_t)readData1[0] << 56) | ((uint64_t)readData1[2] << 48) |
                            ((uint64_t)readData1[4] << 40) | ((uint64_t)readData1[6] << 32) |
                            ((uint64_t)readData2[0] << 24) | ((uint64_t)readData2[1] << 16) |
                            ((uint64_t)readData2[3] << 8)  | ((uint64_t)readData2[4]);
            if(readData2[0] == 13){
                app_log("Serial Number: Si7013\r\n");
            }else if(readData2[0] == 20){
                app_log("Serial Number: Si7020\r\n");
            }else if(readData2[0] == 21){
                app_log("Serial Number: Si7021\r\n");
            }else {
                app_log("Serial Number: no name\r\n");
            }
            app_log("Serial Number: %d\r\n", *serialNumber);
        } else {
            app_log("I2C Transfer Error in second access\r\n");
        }
    } else {
        app_log("I2C Transfer Error in first access\r\n");
    }
}

static uint8_t read_firmware_revision(void) {
    uint8_t cmd [2] = SI7021_CMD_READ_FW_REV ;
    uint8_t readData[2]; // Only need 2 bytes for firmware version check

    // Send command to read firmware revision
    SI7021_transaction(I2C_FLAG_WRITE_READ, cmd, 2, readData, 2);

    uint8_t firmware_revision = readData[0];
    app_log_info("Firmware Revision: 0x%02X\r\n", firmware_revision);

    // Check the firmware revision
    if (firmware_revision == FIRMWARE_REV_1_0) {
        app_log_info("Firmware version 1.0 detected.\r\n");
    } else if (firmware_revision == FIRMWARE_REV_2_0) {
        app_log_info("Firmware version 2.0 detected.\r\n");
    } else {
        app_log("Unknown firmware version detected.\r\n");
    }

    return firmware_revision;
}

int main(void)
{
  uint32_t tempa = 0;
  uint64_t serialNumber = 0;
  uint8_t firmwareRev = 0;
  // Initialize Silicon Labs device, system, service(s) and protocol stack(s).
  // Note that if the kernel is present, processing task(s) will be created by
  // this call.
  sl_system_init();

  // Initialize the application. For example, create periodic timer(s) or
  // task(s) if the kernel is present.
  app_init();

#if defined(SL_CATALOG_KERNEL_PRESENT)
  // Start the kernel. Task(s) created in app_init() will start running.
  sl_system_kernel_start();
#else // SL_CATALOG_KERNEL_PRESENT
  while (1) {
    // Do not remove this call: Silicon Labs components process action routine
    // must be called from the super loop.
    sl_system_process_action();

    // Application process.
    app_process_action();
    //bai 1
    app_log_info("Bai 1:\r\n");
    SI7021_measure( &tempa );
    app_log_info("Tempature in Celcius = %ld% C\r\n", tempa);
    SI7021_measure_hold(&tempa);
    //bai2
    app_log_info("Bai 2:\r\n");
    app_log_info("Tempature in Celcius with hold master mode = %ld% C\r\n", tempa);
    SI7021_measure_no_hold(&tempa);
    app_log_info("Tempature in Celcius with no hold master mode = %ld% C\r\n", tempa);
    //bai3
    app_log_info("Bai 3:\r\n");
    SI7021_read_serial_number_hold(&serialNumber);
    app_log_info("Bai 4:\r\n");
    firmwareRev = read_firmware_revision();
    app_log_info("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
    //bai4
    sl_sleeptimer_delay_millisecond(8000);

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
    // Let the CPU go to sleep if the system allows it.
    sl_power_manager_sleep();
#endif
  }
#endif // SL_CATALOG_KERNEL_PRESENT
}
