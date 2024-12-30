#ifndef _CUSTOM_ADV_H_
#define _CUSTOM_ADV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "sl_bt_api.h"
#include "app_assert.h"

#define NAME_MAX_LENGTH 14

// define for packet
#define FLAG  0x06

typedef struct
{
  // 3 bytes for Flag type
  uint8_t len_flags;
  uint8_t type_flags;
  uint8_t val_flags;

  // Then use type for Manufacturer Specific Data
  uint8_t len_manuf;
  uint8_t type_manuf;

  // Data for Manufacturer specific data
  uint8_t temp_byte1;
  uint8_t temp_byte2;
  uint8_t humid_byte1;
  uint8_t humid_byte2;

  // Measurement period
  uint16_t period;

  // length of the name AD element is variable, adding it last to keep things simple
  uint8_t len_name;
  uint8_t type_name;

  // NAME_MAX_LENGTH must be sized so that total length of data does not exceed 31 bytes
  char name[NAME_MAX_LENGTH];

  // These values are NOT included in the actual advertising payload, just for bookkeeping
  char dummy;        // Space for null terminator
  uint8_t data_size; // Actual length of advertising data
} CustomAdv_t;

void fill_adv_packet(CustomAdv_t *pData, uint8_t flags, uint8_t temp_byte1, uint8_t temp_byte2, uint8_t humid_byte1, uint8_t humid_byte2, uint16_t period, char *name);
void start_adv(CustomAdv_t *pData, uint8_t advertising_set_handle);
void update_adv_data(CustomAdv_t *pData, uint8_t advertising_set_handle, uint8_t temp_byte1, uint8_t temp_byte2, uint8_t humid_byte1, uint8_t humid_byte2, uint16_t period);

#ifdef __cplusplus
}
#endif

#endif
