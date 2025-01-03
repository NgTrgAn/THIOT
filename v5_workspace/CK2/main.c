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

#include <string.h>
#include <stdbool.h>

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
#include "app_timer.h"
#include "em_emu.h"
#include "sl_iostream_usart.h"
#include "sl_iostream_init_usart_instances.h"
#include "sl_iostream.h"

#define BSP_TXPORT gpioPortA
#define BSP_RXPORT gpioPortA
#define BSP_TXPIN 5
#define BSP_RXPIN 6
#define BSP_ENABLE_PORT gpioPortD
#define BSP_ENABLE_PIN 4

#define DHT_PORT gpioPortB
#define DHT_PIN 0


uint8_t trans_period = 1;
uint8_t adv_period = 2;


/**************************************************************************//**
 * @brief
 *    GPIO initialization
 *****************************************************************************/
void initGPIO(void)
{
  // Configure the USART TX pin to the board controller as an output
  GPIO_PinModeSet(BSP_TXPORT, BSP_TXPIN, gpioModePushPull, 1);

  // Configure the USART RX pin to the board controller as an input
  GPIO_PinModeSet(BSP_RXPORT, BSP_RXPIN, gpioModeInput, 0);

  /*
   * Configure the BCC_ENABLE pin as output and set high.  This enables
   * the virtual COM port (VCOM) connection to the board controller and
   * permits serial port traffic over the debug connection to the host
   * PC.
   *
   * To disable the VCOM connection and use the pins on the kit
   * expansion (EXP) header, comment out the following line.
   */
  GPIO_PinModeSet(BSP_ENABLE_PORT, BSP_ENABLE_PIN, gpioModePushPull, 1);
}

/**************************************************************************//**
 * @brief
 *    USART0 initialization
 *****************************************************************************/
void initUSART0(void)
{
  // Default asynchronous initializer (115.2 Kbps, 8N1, no flow control)
  USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
  //USART_InitAsync_TypeDef init;

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

  // Route USART0 TX and RX to the board controller TX and RX pins
  GPIO->USARTROUTE[0].TXROUTE = (BSP_TXPORT << _GPIO_USART_TXROUTE_PORT_SHIFT)
            | (BSP_TXPIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[0].RXROUTE = (BSP_RXPORT << _GPIO_USART_RXROUTE_PORT_SHIFT)
            | (BSP_RXPIN << _GPIO_USART_RXROUTE_PIN_SHIFT);

  // Enable RX and TX signals now that they have been routed
  GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_RXPEN | GPIO_USART_ROUTEEN_TXPEN;

  // Configure and enable USART0
  USART_InitAsync(USART0, &init);

  // Enable RX interrupt
  USART_IntClear(USART0, _USART_IF_MASK);  // Clear all interrupt flags
  USART_IntEnable(USART0, USART_IEN_RXDATAV);  // Enable RXDATAV interrupt
  NVIC_EnableIRQ(USART0_RX_IRQn);  // Enable USART0 interrupt in NVIC
}

// Init timer
void initTIMER0(void)
{
  // Initialize the timer
  TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
  TIMER_Init(TIMER0, &timerInit);
  TIMER_TopSet(TIMER0, 0xFFFFFFFF);
}

//void USART0_RX_IRQHandler() {
//  app_log("Hehe");
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
  sl_sleeptimer_delay_millisecond(18); // wait for 18ms
  GPIO_PinOutSet(dht11_port, dht11_pin);
  sl_udelay_wait(20); // wait for 20us
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
        response = -1; // 255
  }

  while (GPIO_PinInGet(dht11_port, dht11_pin)); // wait for the pin go to low

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

      while (GPIO_PinInGet(dht11_port, dht11_pin)); // wait for the pin go to low
  }

  return i;
}



int main(void)
{
  // Initialize Silicon Labs device, system, service(s) and protocol stack(s).
  // Note that if the kernel is present, processing task(s) will be created by
  // this call.
  sl_system_init();

  // Initialize the application. For example, create periodic timer(s) or
  // task(s) if the kernel is present.
  read_temp(0, 0, 0, 0, adv_period);
  app_init();
  initUSART0();

  //sl_iostream_usart_init_vcom();
  uint8_t temp_byte1 = 0;
  uint8_t humid_byte1 = 0;
  uint8_t temp_byte2 = 0;
  uint8_t humid_byte2 = 0;
  uint8_t checksum = 0;
  uint8_t Presence = 0;

  //uint8_t buffer = 0;
  uint8_t buffer_trans = 0;
  uint8_t buffer_adv = 0;
  uint8_t choice = 0;
  uint8_t count = 0;
  //app_init();

#if defined(SL_CATALOG_KERNEL_PRESENT)
  // Start the kernel. Task(s) created in app_init() will start running.
  sl_system_kernel_start();
#else // SL_CATALOG_KERNEL_PRESENT

  CMU_ClockEnable(cmuClock_GPIO, true);
  while (1) {


    // Application process.
    app_process_action();


    uint32_t data = USART0->RXDATA;
    if(data == '1' || data == '2') {
        app_log("Received data from USART: %d\r\n", data);
        choice = data - '0';
        if(choice == 1) {
            do {
                buffer_trans = USART_Rx(USART0);
            } while (buffer_trans == 0);
            app_log("Received buffer_trans: %c\r\n", buffer_trans);
            trans_period = buffer_trans - '0';
        }
        if (choice == 2) {
            do {
                buffer_adv = USART_Rx(USART0);
            } while (buffer_adv == 0);
            app_log("Received buffer_adv: %c\r\n", buffer_adv);
            adv_period = buffer_adv - '0';
        }
    }

    DHT11_Start(DHT_PORT, DHT_PIN);
    Presence = DHT11_Check_Response(DHT_PORT, DHT_PIN);
    humid_byte1 = DHT11_Read(DHT_PORT, DHT_PIN);
    humid_byte2 = DHT11_Read(DHT_PORT, DHT_PIN);
    temp_byte1 = DHT11_Read(DHT_PORT, DHT_PIN);
    temp_byte2 = DHT11_Read(DHT_PORT, DHT_PIN);
    checksum = DHT11_Read(DHT_PORT, DHT_PIN);
    if (checksum == humid_byte1 + humid_byte2 + temp_byte1 + temp_byte2) {
        app_log("Checksum completed\r\n");
        app_log("Temp: %d.%d\r\n", temp_byte1, temp_byte2);
        app_log("Humid: %d.%d\r\n", humid_byte1, humid_byte2);
        app_log("Transmit Period: %ds\r\n", trans_period);
        app_log("ADV Period: %ds\r\n", adv_period);
        memlcd_app_init(temp_byte1, temp_byte2 ,humid_byte1, humid_byte2, trans_period, adv_period);
        read_temp(temp_byte1, temp_byte2, humid_byte1, humid_byte2, adv_period);
    } else app_log("Checksum failed\r\n");
    sl_sleeptimer_delay_millisecond(trans_period * 1000);


#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
    // Let the CPU go to sleep if the system allows it.
    sl_power_manager_sleep();
#endif
  }
#endif // SL_CATALOG_KERNEL_PRESENT
}
