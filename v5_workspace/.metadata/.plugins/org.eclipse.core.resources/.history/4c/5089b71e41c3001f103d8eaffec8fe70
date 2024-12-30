/***************************************************************************//**
 * @file
 * @brief Application interface provided to main().
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

#ifndef APP_H
#define APP_H
#include "stdint.h"

//  uint8_t temp_byte1;
//  uint8_t humid_byte1;
//  uint8_t temp_byte2;
//  uint8_t humid_byte2;
//  uint8_t checksum;
//  uint8_t Presence;
//
//  uint32_t temp_humid_val = 0;
//  uint8_t temp ;
//  uint8_t humid ;

uint32_t init_adv_data(uint8_t temp_byte1, uint8_t temp_byte2, uint8_t humid_byte1, uint8_t humid_byte2);

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(void);

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
void app_process_action(void);

void read_temp(uint8_t temp_byte1, uint8_t temp_byte2, uint8_t humid_byte1, uint8_t humid_byte2, uint8_t adv_period);

#endif // APP_H
