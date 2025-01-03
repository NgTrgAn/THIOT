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
#include <stdio.h>
#include <app_lcd.h>

#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_timer.h"
#include "app_log.h"
#include "em_device.h"
#include "em_system.h"
#include "em_core.h"
#include "sl_udelay.h"
#include "sl_sleeptimer.h"
#include "app.h"

#define BSP_TXPORT gpioPortA
#define BSP_RXPORT gpioPortA
#define BSP_TXPIN 5
#define BSP_RXPIN 6
#define BSP_ENABLE_PORT gpioPortD
#define BSP_ENABLE_PIN 4

#define BSP_GPIO_LEDS
#define BSP_GPIO_LED0_PORT gpioPortD
#define BSP_GPIO_LED0_PIN 2
#define BSP_GPIO_LED1_PORT gpioPortD
#define BSP_GPIO_LED1_PIN 3
#define BSP_GPIO_PB0_PORT gpioPortB
#define BSP_GPIO_PB0_PIN 0
#define BSP_GPIO_PB1_PORT gpioPortB
#define BSP_GPIO_PB1_PIN 1

#define DHT_PORT gpioPortB
#define DHT_PIN 1

uint32_t temp_humid_measurement_cycle = 2000; // default 2 seconds
uint8_t temp_byte1, humid_byte1, temp_byte2, humid_byte2, checksum;

void initGPIO(void)
{
  GPIO_PinModeSet(BSP_TXPORT, BSP_TXPIN, gpioModePushPull, 1);
  GPIO_PinModeSet(BSP_RXPORT, BSP_RXPIN, gpioModeInput, 0);
  GPIO_PinModeSet(BSP_ENABLE_PORT, BSP_ENABLE_PIN, gpioModePushPull, 1);
}

void initUSART0(void)
{
  USART_InitAsync_TypeDef init;
  init.enable = usartEnable;
  init.refFreq = 0;
  init.baudrate = 115200;
  init.oversampling = usartOVS16;
  init.databits = usartDatabits8;
  init.parity = USART_FRAME_PARITY_NONE;
  init.stopbits = usartStopbits1;
  init.mvdis = false;
  init.prsRxEnable = false;
  init.prsRxCh = 0;
  init.autoCsEnable = false;
  init.csInv = false;
  init.autoCsHold = 0;
  init.autoCsSetup = 0;
  init.hwFlowControl = usartHwFlowControlNone;

  GPIO->USARTROUTE[0].TXROUTE = (BSP_TXPORT << _GPIO_USART_TXROUTE_PORT_SHIFT)
            | (BSP_TXPIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[0].RXROUTE = (BSP_RXPORT << _GPIO_USART_RXROUTE_PORT_SHIFT)
            | (BSP_RXPIN << _GPIO_USART_RXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_RXPEN | GPIO_USART_ROUTEEN_TXPEN;

  USART_InitAsync(USART0, &init);
  USART_Enable(USART0, usartEnable);
}

//void initTIMER0(void)
//{
//  TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
//  TIMER_Init(TIMER0, &timerInit);
//  TIMER_TopSet(TIMER0, 0xFFFFFFFF);
//}

void Set_Pin_Output(GPIO_Port_TypeDef port, unsigned int pin) {
  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet(port, pin, gpioModePushPull, 0);
}

void Set_Pin_Input(GPIO_Port_TypeDef port, unsigned int pin) {
  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet(port, pin, gpioModeInputPullFilter, 1);
}

void DHT11_Start(GPIO_Port_TypeDef dht11_port, unsigned int dht11_pin) {
  Set_Pin_Output(dht11_port, dht11_pin);
  GPIO_PinOutClear(dht11_port, dht11_pin);
  sl_sleeptimer_delay_millisecond(18);
  GPIO_PinOutSet(dht11_port, dht11_pin);
  sl_udelay_wait(20);
  Set_Pin_Input(dht11_port, dht11_pin);
}

uint8_t DHT11_Check_Response(GPIO_Port_TypeDef dht11_port, unsigned int dht11_pin) {
  uint8_t response = 0;
  sl_udelay_wait(40);
  if (!GPIO_PinInGet(dht11_port, dht11_pin)) {
      sl_udelay_wait(80);
      if (GPIO_PinInGet(dht11_port, dht11_pin))
        response = 1;
      else
        response = -1;
  }
  while (GPIO_PinInGet(dht11_port, dht11_pin));
  return response;
}

uint8_t DHT11_Read(GPIO_Port_TypeDef dht11_port, unsigned int dht11_pin) {
  uint8_t i = 0;
  for (uint8_t j = 0; j < 8; j++) {
      while (!GPIO_PinInGet(dht11_port, dht11_pin));
      sl_udelay_wait(40);
      if (!GPIO_PinInGet(dht11_port, dht11_pin))
        i &= ~(1 << (7 - j));
      else
        i |= 1 << (7 - j);
      while (GPIO_PinInGet(dht11_port, dht11_pin));
  }
  return i;
}

void UART_Send_String(char *str) {
  while (*str) {
    USART_Tx(USART0, *str++);
  }
}

void UART_Send_Byte(uint8_t byte) {
  USART_Tx(USART0, byte);
}



void update_lcd_with_temp_humid(void) {
  DHT11_Start(DHT_PORT, DHT_PIN);
  if (DHT11_Check_Response(DHT_PORT, DHT_PIN)) {
    humid_byte1 = DHT11_Read(DHT_PORT, DHT_PIN);
    humid_byte2 = DHT11_Read(DHT_PORT, DHT_PIN);
    temp_byte1 = DHT11_Read(DHT_PORT, DHT_PIN);
    temp_byte2 = DHT11_Read(DHT_PORT, DHT_PIN);
    checksum = DHT11_Read(DHT_PORT, DHT_PIN);

    if (checksum == (humid_byte1 + humid_byte2 + temp_byte1 + temp_byte2)) {
        UART_Send_Byte(temp_byte1);
        UART_Send_Byte(temp_byte2);
        UART_Send_Byte(humid_byte1);
        UART_Send_Byte(humid_byte2);
        read_temp(temp_byte1, temp_byte2, humid_byte1, humid_byte2,temp_humid_measurement_cycle);
      memlcd_app_init(temp_byte1, temp_byte2, humid_byte1, humid_byte2, temp_humid_measurement_cycle);
    }
  }
}

void process_uart_command(uint8_t command) {
  switch (command) {
    case 0x01: // Set temperature/humidity measurement cycle
      {
        uint8_t cycle_high = USART_Rx(USART0);
        uint8_t cycle_low = USART_Rx(USART0);
        temp_humid_measurement_cycle = (cycle_high << 8) | cycle_low;
      }
      break;
    case 0x02: // Get temperature and humidity
      {
            UART_Send_Byte(temp_byte1);
            UART_Send_Byte(temp_byte2);
            UART_Send_Byte(humid_byte1);
            UART_Send_Byte(humid_byte2);
            memlcd_app_init(temp_byte1, temp_byte2 ,humid_byte1, humid_byte2, temp_humid_measurement_cycle);
      }
      break;
    default:
      break;
  }
}

int main(void)
{
  sl_system_init();
  initGPIO();
  initUSART0();

  read_temp(0, 0, 0, 0, temp_humid_measurement_cycle);
  app_init();




#if defined(SL_CATALOG_KERNEL_PRESENT)
  // Start the kernel. Task(s) created in app_init() will start running.
  sl_system_kernel_start();
#else // SL_CATALOG_KERNEL_PRESENT
  CMU_ClockEnable(cmuClock_GPIO, true);
  while (1) {
      sl_system_process_action();

      // Application process.
      app_process_action();



      char data = USART0->RXDATA;
      if(data == '1' || data == '2'){
      uint8_t command = USART_Rx(USART0);
      process_uart_command(command);
      }

    update_lcd_with_temp_humid();
    sl_sleeptimer_delay_millisecond(temp_humid_measurement_cycle);
  }
#endif // SL_CATALOG_KERNEL_PRESENT
}
