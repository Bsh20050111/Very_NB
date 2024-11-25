/*
 * Smart_ips.h
 *
 *  Created on: 2024Äê9ÔÂ19ÈÕ
 *      Author: lenovo
 */

#ifndef USER_CONTORL_SMART_IPS_H_
#define USER_CONTORL_SMART_IPS_H_

#include "zf_common_headfile.h"
#include "Smart_headfile.h"

extern int16 menu_index ;
extern int16 disp_index ;
extern uint16 star[6];
extern uint16 change[6];
extern uint16 change_dif[6];

void menu_disp(uint16 menu_index,uint16 disp_index);
void menu_control(int16* menu_index,int16* disp_index,int16 key_down,motor_element* left_wheel,motor_element* right_wheel,dif_element *dif_wheel,servo_element *servo_fuck);


#endif /* USER_CONTORL_SMART_IPS_H_ */
