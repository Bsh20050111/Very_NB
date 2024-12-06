/*
 * Smart_ips.h
 *
 *  Created on: 2024��9��19��
 *      Author: lenovo
 */

#ifndef USER_CONTORL_SMART_IPS_H_
#define USER_CONTORL_SMART_IPS_H_

#include "zf_common_headfile.h"
#include "Smart_headfile.h"
#include "headfile.h"
#include "flash.h"

#define x_pixel 10
#define y_pixel 20

typedef struct
{
    uint8 number;
    uint8 point_number;
} Menu_table;

extern uint8 menu;
extern uint8 key_real;
extern uint8 key_on_time;
extern uint8 key_on;
extern double change;
extern uint8 camera_show_flag;
void key_menu_process(void);

uint8 kbd_scan(void);
uint8 kbd_read(void);
void point_location(void);
void key1_next_page(Menu_table the_table);
float key_value_change(float value,float space);
float key_value_change_restriction(float value,float space,float lspace,float min,float max);

#endif /* USER_CONTORL_SMART_IPS_H_ */
