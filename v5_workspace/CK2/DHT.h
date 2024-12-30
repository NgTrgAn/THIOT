
#ifndef DHT_H_
#define DHT_H_
#include "stdint.h"

enum DHT_Status_t
{
  DHT_Ok,
  DHT_Error_Humidity,
  DHT_Error_Temperature,
  DHT_Error_Checksum,
  DHT_Error_Timeout
};

void DHT_ReadRaw(uint8_t Data[4]);
void extractData(uint8_t Data[4], uint8_t *temp, uint8_t *humidity);

#endif /* INC_DHT_H_ */
