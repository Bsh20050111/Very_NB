/*
 * motor_control.h
 *
 *  Created on: 2024Äê9ÔÂ21ÈÕ
 *      Author: lenovo
 */

#ifndef USER_CONTORL_SMART_MOTOR_H_
#define USER_CONTORL_SMART_MOTOR_H_

#include "zf_common_headfile.h"
#include "Smart_headfile.h"

void PID_LMotor_Init(motor_element *left_element);
void PID_RMotor_Init(motor_element *left_element);
void PID_Servo_Init(servo_element *servo_element);
void PID_DIF_Init(dif_element *dif_element);


void PID_Motor(motor_element *left_element);
void PID_SERVO(servo_element *servo_fuck,float angle);
void PID_DIF(dif_element *dif_element,float angle);
void Read_Enconder(motor_element *right_element,motor_element *left_element,float data_1,float data_3);
void Motor_begin(motor_element *left_wheel,motor_element *right_wheel,dif_element *dif_wheel);

#endif /* USER_CONTORL_SMART_MOTOR_H_ */
