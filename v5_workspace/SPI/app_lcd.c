/*
 * lcd.c
 *
 *  Created on: Nov 4, 2024
 *      Author: Phat_Dang
 */
#include <stdio.h>

#include "sl_board_control.h"
#include "em_assert.h"
#include "glib.h"
#include "dmd.h"
#include "sl_sleeptimer.h" // Đảm bảo file này được include

#ifndef LCD_MAX_LINES
#define LCD_MAX_LINES      11
#endif

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static GLIB_Context_t glibContext;
static int currentLine = 0;

static unsigned int hours = 0, minutes = 0, seconds = 0;
static sl_sleeptimer_timer_handle_t timer_handle;  // Định nghĩa bộ đếm thời gian
/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize example.
 ******************************************************************************/
void timer_callback(sl_sleeptimer_timer_handle_t *handle, void *data)
{
  (void) handle;
  (void) data;

  // Increment seconds
  seconds++;
  if (seconds >= 60) {
    seconds = 0;
    minutes++;
    if (minutes >= 60) {
      minutes = 0;
      hours = (hours + 1) % 24; // Reset to 0 after 23:59:59
    }
  }
}

void memlcd_app_init(void)
{
  uint32_t status;

  /* Enable the memory lcd */
  status = sl_board_enable_display();
  EFM_ASSERT(status == SL_STATUS_OK);

  /* Initialize the DMD support for memory lcd display */
  status = DMD_init(0);
  EFM_ASSERT(status == DMD_OK);

  /* Initialize the glib context */
  status = GLIB_contextInit(&glibContext);
  EFM_ASSERT(status == GLIB_OK);

  glibContext.backgroundColor = White;
  glibContext.foregroundColor = Black;

  /* Fill lcd with background color */
  GLIB_clear(&glibContext);

  /* Use Narrow font */
  GLIB_setFont(&glibContext, (GLIB_Font_t *) &GLIB_FontNarrow6x8);

  /* Draw text on the memory lcd display*/
  GLIB_drawStringOnLine(&glibContext,
                        "LAB 3 SPI",
                        currentLine++,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);

  DMD_updateDisplay();
  /* Initialize and start a timer to update time every second */
    sl_sleeptimer_start_periodic_timer_ms(&timer_handle, 1000, timer_callback, NULL, 0, 0);
}

/***************************************************************************//**
 * Ticking function.
 ******************************************************************************/
void memlcd_app_process_action(void)
{
  char timeString[9]; // Format HH:MM:SS

  // Format time as HH:MM:SS
  snprintf(timeString, sizeof(timeString), "%02d:%02d:%02d", hours, minutes, seconds);
  // Clear the previous time display line
   // GLIB_clear(&glibContext);

    // Display the updated time on LCD
    GLIB_drawStringOnLine(&glibContext, timeString, currentLine, GLIB_ALIGN_LEFT, 5, 5, true);

    DMD_updateDisplay();
  }
