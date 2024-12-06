/*
 * Smart_ips.c
 *
 *  Created on: 2024锟斤拷9锟斤拷19锟斤拷
 *      Author: lenovo
 */

#include "Smart_ips.h"

uint8 menu=0;
uint8 point_max=4;
uint8 key_real=0;
uint8 point_value=1;
uint8 flag_flywheel=0;
uint8 key_on=0;
uint8 time_key;
uint8 key_on_time;

//Main_Menu
//  PID_Argv
//        motor_PI
//        Dif_PI
//        Servo_PD
//  image_Argv
//        cricle_aim
//        cross_aim
//        common_aim
//        straight_aim
//        turn_aim
//        mid_aim
//        barrier_aim
//  Camera
//
//  Condition
//        speed_set
//        pure_angle
//        speed_leftwheel
//        speed_rightwheel
//
//  Veltage


Menu_table table[]=
{
    {0,3},//Main_Menu
    {1,9},//PID_Argv
    {2,8},//image_Argv
    {3,1},//Camera
    {4,2},//Condition
};

void key_menu(void){
    point_location();

    ips200_show_string(x_pixel*0, y_pixel*point_value, ">");
    if (menu==table[0].number)
    {
        ips200_show_string(x_pixel*1, y_pixel*0, "main menu");
        ips200_show_string(x_pixel*1, y_pixel*1, "PID_Argv");
        ips200_show_string(x_pixel*1, y_pixel*2, "image_Argv");
        ips200_show_string(x_pixel*1, y_pixel*3, "Camera");
        ips200_show_string(x_pixel*1, y_pixel*4, "Condition");
        ips200_show_string(x_pixel*1, y_pixel*5, "Voltage:");
        ips200_show_float (x_pixel*9, y_pixel*5,(Voltage-3875)/2.2,4,2);
        ips200_show_string(x_pixel*14, y_pixel*5,"%");
        if(point_value==1) {key1_next_page(table[1]);}
        if(point_value==2) {key1_next_page(table[2]);}
        if(point_value==3) {key1_next_page(table[3]);}
        if(point_value==4) {key1_next_page(table[4]);}
    }

    if (menu==table[1].number)
    {
        ips200_show_string(x_pixel*1, y_pixel*0, "PID_Argv");
        ips200_show_string(x_pixel*1, y_pixel*1, "Return");
        ips200_show_string(x_pixel*1, y_pixel*2, "motor_LP:");
        ips200_show_float (x_pixel*10, y_pixel*2, left_wheel.kp,2,3);
        ips200_show_string(x_pixel*1, y_pixel*3, "motor_LI:");
        ips200_show_float (x_pixel*10, y_pixel*3, left_wheel.ki,2,3);
        ips200_show_string(x_pixel*1, y_pixel*4, "motor_RP:");
        ips200_show_float (x_pixel*10, y_pixel*4, right_wheel.kp,2,3);
        ips200_show_string(x_pixel*1, y_pixel*5, "motor_RI:");
        ips200_show_float (x_pixel*10, y_pixel*5, right_wheel.ki,2,3);
        ips200_show_string(x_pixel*1, y_pixel*6, "Dif_P:");
        ips200_show_float (x_pixel*7, y_pixel*6, dif_wheel.kp,2,3);
        ips200_show_string(x_pixel*1, y_pixel*7, "Dif_I:");
        ips200_show_float (x_pixel*7, y_pixel*7, dif_wheel.ki,2,3);
        ips200_show_string(x_pixel*1, y_pixel*8, "Servo_P:");
        ips200_show_float (x_pixel*9, y_pixel*8, servo_fuck.kp,2,3);
        ips200_show_string(x_pixel*1, y_pixel*9, "Servo_D:");
        ips200_show_float (x_pixel*9, y_pixel*9, servo_fuck.kd,2,3);
        ips200_show_string(x_pixel*1, y_pixel*10,"Voltage:");
        ips200_show_float (x_pixel*9, y_pixel*10,(Voltage-3875)/2.2,4,2);
        ips200_show_string(x_pixel*14, y_pixel*10,"%");
        if(point_value==1){key1_next_page(table[0]);};
        if(point_value==2){left_wheel.kp=key_value_change(left_wheel.kp,0.1);}
        if(point_value==3){left_wheel.ki=key_value_change(left_wheel.ki,0.1);}
        if(point_value==4){right_wheel.kp=key_value_change(right_wheel.kp,0.1);}
        if(point_value==5){right_wheel.ki=key_value_change(right_wheel.ki,0.1);}
        if(point_value==6){dif_wheel.kp=key_value_change(dif_wheel.kp,0.1);}
        if(point_value==7){dif_wheel.ki=key_value_change(dif_wheel.ki,0.1);}
        if(point_value==8){servo_fuck.kp=key_value_change(servo_fuck.kp,0.1);}
        if(point_value==9){servo_fuck.kd=key_value_change(servo_fuck.kd,0.1);}

    }
    if(menu==table[2].number)
    {
        ips200_show_string(x_pixel*1, y_pixel*0, "image_Argv");
        ips200_show_string(x_pixel*1, y_pixel*1, "Return");
        ips200_show_string(x_pixel*1, y_pixel*2, "cricle_aim:");
        ips200_show_float (x_pixel*11, y_pixel*2, cricle_aim,2,3);
        ips200_show_string(x_pixel*1, y_pixel*3, "cross_aim:");
        ips200_show_float (x_pixel*11, y_pixel*3, cross_aim,2,3);
        ips200_show_string(x_pixel*1, y_pixel*4, "common_aim:");
        ips200_show_float (x_pixel*11, y_pixel*4, common_aim,2,3);
        ips200_show_string(x_pixel*1, y_pixel*5, "straight_aim:");
        ips200_show_float (x_pixel*13, y_pixel*5, straight_aim,2,3);
        ips200_show_string(x_pixel*1, y_pixel*6, "turn_aim:");
        ips200_show_float (x_pixel*9, y_pixel*6, turn_aim,2,3);
        ips200_show_string(x_pixel*1, y_pixel*7, "mid_aim:");
        ips200_show_float (x_pixel*9, y_pixel*7, mid_aim,2,3);
        ips200_show_string(x_pixel*1, y_pixel*8, "barrier_aim:");
        ips200_show_float (x_pixel*13, y_pixel*8, barrier_aim,2,3);
        ips200_show_string(x_pixel*1, y_pixel*9, "Voltage:");
        ips200_show_float (x_pixel*9, y_pixel*9,(Voltage-3875)/2.2,4,2);
        ips200_show_string(x_pixel*14, y_pixel*9,"%");
        if(point_value==1){key1_next_page(table[0]);};
        if(point_value==2){cricle_aim=key_value_change(cricle_aim,0.01);}
        if(point_value==3){cross_aim=key_value_change(cross_aim,0.01);}
        if(point_value==4){common_aim=key_value_change(common_aim,0.01);}
        if(point_value==5){straight_aim=key_value_change(straight_aim,0.01);}
        if(point_value==6){turn_aim=key_value_change(turn_aim,0.01);}
        if(point_value==7){mid_aim=key_value_change(mid_aim,0.01);}
        if(point_value==8){barrier_aim=key_value_change(barrier_aim,0.01);}
    }
    if (menu==table[3].number)
    {
        ips200_show_string(x_pixel*1, y_pixel*0, "Camera");
        ips200_show_string(x_pixel*1, y_pixel*1, "Return");
        ips200_show_string(x_pixel*1, y_pixel*2, "Angle:");
        ips200_show_float (x_pixel*7, y_pixel*2, pure_angle,2,3);
        ips200_show_string(x_pixel*1, y_pixel*3, "State:");
        ips200_show_uint(x_pixel*7, y_pixel*3,(uint16)state_type,3);
        ips200_show_string(x_pixel*1, y_pixel*4, "Time:");
        Atimer_stop(1);
        ips200_show_uint(x_pixel*6, y_pixel*4, Atimer_get(1),3);
        ips200_show_gray_image(0,y_pixel*5, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, 1.5*MT9V03X_W, 1.5*MT9V03X_H, FIX_BINTHRESHOLD);
        if(point_value==1){key1_next_page(table[0]);}
    }

    if(menu==table[4].number)
    {
        ips200_show_string(x_pixel*1, y_pixel*0, "Condition");
        ips200_show_string(x_pixel*1, y_pixel*1, "Return");
        ips200_show_string(x_pixel*1, y_pixel*2, "speed_set");
        ips200_show_string(x_pixel*1, y_pixel*3, "pure_angle");
        ips200_show_string(x_pixel*1, y_pixel*4, "left_wheel");
        ips200_show_float (x_pixel*11, y_pixel*4,left_wheel.out_speed,4,2);
        ips200_show_string(x_pixel*1, y_pixel*5, "right_wheel");
        ips200_show_float (x_pixel*12, y_pixel*5,right_wheel.out_speed,4,2);
        if(point_value==1){key1_next_page(table[0]);}
        if(point_value==2){set_speed=key_value_change(set_speed,0.1);}

    }
}
uint8 kbd_scan(void){
    uint8 key=0;
    if (!gpio_get_level(KEY1)) key=1;
    if (!gpio_get_level(KEY2)) key=2;
    if (!gpio_get_level(KEY3)) key=3;
    if (!gpio_get_level(KEY4)) key=4;
    return key;
}

uint8 kbd_read(void){
    static uint8 key_state;
    static uint8 key_rember;
    uint8 key_io=0,key_return=0;
    key_io=kbd_scan();
    switch(key_state){
        case 0:
            if(key_io) key_state=1;//如果按键按下，标志位为1
        break;
        case 1:
            if(key_io){//如果按键持续按下，标志位为2，返回值为按键值
                key_return=key_io;
                key_rember=key_return;
                key_state=2;
            }
            else key_state=0;//按键中断，标志位为0
        break;
        case 2:
            key_on_time++;//进入标志位2，时间累计
            if(key_on_time>2000) {key_return=key_rember;key_on=1;}//时间超过20，返回值为上一次返回值，长按标志位开启
            if(key_io==0) {//中断后，全归零
                key_on_time=0;
                key_on=0;
                key_state=0;
            }
        break;
    }
    return key_return;
}

void point_location(void)
{
    if(key_real==3)
    {
        if(point_value>=point_max) {ips200_clear();point_value=1;}
        else {ips200_clear();point_value++;}
    }
    if(key_real==4)
    {
        Flash_Pid_storage();
    }
}

void key1_next_page(Menu_table the_table)
{
    if(key_real==1)
    {
        ips200_clear();
        point_max=the_table.point_number;
        menu=the_table.number;
        point_value=0;
    }
}

float key_value_change(float value,float space)
{
    if(key_real==1)
    {
        if (key_on==0) value+=space;
        else value+=2*space;
    }
    if(key_real==2)
    {
        if (key_on==0) value-=space;
        else value-=2*space;
    }
    return value;
}

float key_value_change_restriction(float value,float space,float lspace,float min,float max)
{
    if(value>max) value=max;
    if(value<min) value=min;
    if(key_real==1)
    {
        if (key_on==0) value+=space;
        else value+=lspace*space;
    }
    if(key_real==2)
    {
        if (key_on==0) value-=space;
        else value-=lspace*space;
    }
    return value;
}

void key_menu_process(void){

    key_real=kbd_read();

    key_menu();
}




















