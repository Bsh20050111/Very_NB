/*
 * motor_control.c
 *
 *  Created on: 2024年9月21日
 *      Author: lenovo
 */


#include "Smart_motor.h"
#include "Kalman.h"
#include "math.h"


#define PWM_CHANGE_ANGEL 0.332125

float set_speed;

motor_element right_wheel;
motor_element left_wheel;
dif_element   dif_wheel;
servo_element servo_fuck;

void PID_LMotor_Init(motor_element *left_element)
{
    left_element->set_speed = 1500;
    if(left_element->kp == 0)
    {
        left_element->set_speed = 1000;
        left_element->max_speed = 4000;
        left_element->min_speed = -4000;
        left_element->kp=5;
        left_element->ki=0.05;
        left_element->out_speed = left_element->set_speed;
    }
}

void PID_RMotor_Init(motor_element *left_element)
{
    left_element->set_speed = 1000;
    if(left_element->kp == 0)
    {
//        left_element->set_speed = 1500;
        left_element->max_speed = 4000;
        left_element->min_speed = -4000;
        left_element->kp=5;
        left_element->ki=0.1;
        left_element->out_speed = left_element->set_speed;
    }
}

void PID_DIF_Init(dif_element *dif_element)
{
    dif_element->dif_max =  1500;
    if(dif_element->kp==0)
    {
        dif_element->dif_max =  1500;
        dif_element->dif_min = -1500;
        dif_element->kp=1.5;
        dif_element->ki=0.15;
    }
}

void PID_Servo_Init(servo_element *servo_element)
{
    servo_element->out_turn = 740;
    if(servo_element->kp==0)
    {
        servo_element->kp = 0.5;
        servo_element->kd = 0.4;
        servo_element->max_turn = 800;
        servo_element->min_turn = 680;
        servo_element->out_turn = 740;
    }
}

void PID_Motor(motor_element *left_element)
{
    left_element->err_now = left_element->set_speed - left_element->now_speed;    //速度偏差计算

    left_element->out_speed += left_element->kp*(left_element->err_now - left_element->err_last) + left_element->ki * left_element->err_now;//电机增量式PI运算，PI基本就够了，加D也可以

    if(left_element->out_speed >= left_element->max_speed)left_element->out_speed = left_element->max_speed;
    if(left_element->out_speed <= left_element->min_speed)left_element->out_speed = left_element->min_speed;

    left_element->err_last = left_element->err_now;
}

void PID_DIF(dif_element *dif_element,float angle)
{
    dif_element->err_now = angle;

    dif_element->dif_out = dif_element->kp*(dif_element->err_now-dif_element->err_last)+dif_element->ki*dif_element->err_now;
    dif_element->dif_out *= 300;

    if(dif_element->dif_out >= dif_element->dif_max)dif_element->dif_out = dif_element->dif_max;
    if(dif_element->dif_out <= dif_element->dif_min)dif_element->dif_out = dif_element->dif_min;

    dif_element->err_last = dif_element->err_now;
}

void PID_SERVO(servo_element *servo_fuck,float angle)
{
     servo_fuck->err_now = angle;

     servo_fuck->out_turn += servo_fuck->kp * (servo_fuck->err_now - servo_fuck->err_last) + servo_fuck->kd*(servo_fuck->err_now - 2*servo_fuck->err_last + servo_fuck->err_llast);
     servo_fuck->err_last = servo_fuck->err_now;
     servo_fuck->err_llast = servo_fuck->err_last;

     if(servo_fuck->out_turn >= servo_fuck->max_turn)servo_fuck->out_turn = servo_fuck->max_turn;
     if(servo_fuck->out_turn <= servo_fuck->min_turn)servo_fuck->out_turn = servo_fuck->min_turn;
}
void Read_Enconder(motor_element *left_element,motor_element *right_element,float data_1,float data_3)
{
    left_element->now_speed  = (data_1*ENCODER_SPEED_LEFT*1000/INTERTIME) *10/PWM_SPEED_LEFT;
    right_element->now_speed = (data_3*ENCODER_SPEED_RIGHT*1000/INTERTIME)*10/PWM_SPEED_RIGHT;
}

void Motor_begin(motor_element *left_wheel,motor_element *right_wheel,dif_element *dif_wheel)
{

    left_wheel->out_speed = left_wheel->out_speed - dif_wheel->dif_out/2;
    right_wheel->out_speed = right_wheel->out_speed + dif_wheel->dif_out/2;

}


