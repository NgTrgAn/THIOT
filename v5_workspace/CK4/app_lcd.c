/*
 * lcd.c
 *
 *  Created on: Nov 4, 2024
 *      Author: Phat_Dang
 */
#include <stdio.h>

#include "stdint.h"
#include "sl_board_control.h"
#include "em_assert.h"
#include "glib.h"
#include "dmd.h"
#include <string.h>


#ifndef LCD_MAX_LINES
#define LCD_MAX_LINES      11
#endif

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static GLIB_Context_t glibContext;
static int currentLine = 0;
static int nextLine = 1;

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize example.
 ******************************************************************************/
void memlcd_app_init(int temp_byte1, int temp_byte2, int humid_byte1, int humid_byte2, int period)
{
  uint32_t status;
  char temp_str[50];
  char humid_str[50];
  char p[50];
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

  /* Create string */
  snprintf(temp_str, 50, "Nhiet do: %d.%d\n", temp_byte1, temp_byte2);
  snprintf(humid_str, 50, "Do am: %d%%\n",humid_byte1,humid_byte2);
  snprintf(p, 50, "Chu ki: %d ms\n",period);
  /* Draw text on the memory lcd display*/
  GLIB_drawStringOnLine(&glibContext,
                        temp_str,
                        currentLine,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);

  GLIB_drawStringOnLine(&glibContext,
                        humid_str,
                        nextLine,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);
  GLIB_drawStringOnLine(&glibContext,
                          p,
                          nextLine+1,
                          GLIB_ALIGN_LEFT,
                          5,
                          5,
                          true);

  DMD_updateDisplay();
}


/***************************************************************************//**
 * Ticking function.
 ******************************************************************************/
void memlcd_app_process_action(void)
{
  return;
}

