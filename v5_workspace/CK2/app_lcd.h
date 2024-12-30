/*
 * lcd_app.h
 *
 *  Created on: Nov 4, 2024
 *      Author: Phat_Dang
 */

#ifndef APP_LCD_H_
#define APP_LCD_H_

void memlcd_app_init(int temp_byte1, int temp_byte2, int humid_byte1, int humid_byte2, int trans_period, int adv_period);

void display(int);

void memlcd_app_process_action(void);


#endif /* APP_LCD_H_ */
