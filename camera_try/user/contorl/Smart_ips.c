/*
 * Smart_ips.c
 *
 *  Created on: 2024年9月19日
 *      Author: lenovo
 */

#include "Smart_ips.h"


int16 menu_index = 0;
int16 disp_index = 0;
uint16 star[6] = {0,0,0,0,0,0};
uint16 change[6] = {0,0,0,0,0,0};
uint16 change_dif[6] = {0,0,0,0,0,0};

extern motor_element right_wheel;
extern motor_element left_wheel;
extern dif_element   dif_wheel;
extern servo_element servo_fuck;

void menu_disp(uint16 menu_index,uint16 disp_index)
{
    switch(menu_index)
    {
        case 0://主菜单
        {
            switch(disp_index)
            {
                case 0:
                {
                    ips200_show_string(5,5 ,"> wheel_PID");
                    ips200_show_string(5,25,"  Dif_PID");
                    ips200_show_string(5,45,"  Line_PID");
                    ips200_show_string(5,65,"  Image_display");
                    break;
                }
                case 1:
                {
                    ips200_show_string(5,5 ,"  wheel_PID");
                    ips200_show_string(5,25,"> Dif_PID");
                    ips200_show_string(5,45,"  Line_PID");
                    ips200_show_string(5,65,"  Image_display");
                    break;
                }
                case 2:
                {
                    ips200_show_string(5,5 ,"  wheel_PID");
                    ips200_show_string(5,25,"  Dif_PID");
                    ips200_show_string(5,45,"> Line_PID");
                    ips200_show_string(5,65,"  Image_display");
                    break;
                }
                case 3:
                {
                    ips200_show_string(5,5 ,"  wheel_PID");
                    ips200_show_string(5,25,"  Dif_PID");
                    ips200_show_string(5,45,"  Line_PID");
                    ips200_show_string(5,65,"> Image_display");
                    break;
                }
            }
            break;
        }
        case 1://wheel菜单
        {
            switch(disp_index)
            {
                case 0:
                {
                    ips200_show_string(5, 5,">leftwheel_P:");
                    ips200_show_float(120,5,left_wheel.kp,2,2);
                    ips200_show_string(5,25," leftwheel_I:");
                    ips200_show_float(120,25,left_wheel.ki,2,2);
                    ips200_show_string(5,45," leftwheel_D:");
                    ips200_show_float(120,45,left_wheel.kd,2,2);
                    ips200_show_string(5,65," right_wheel_P:");
                    ips200_show_float(120,65,right_wheel.kp,2,2);
                    ips200_show_string(5,85," right_wheel_I:");
                    ips200_show_float(120,85,right_wheel.ki,2,2);
                    ips200_show_string(5,105," right_wheel_D:");
                    ips200_show_float(120,105,right_wheel.kd,2,2);
                    break;
                }
                case 1:
                {
                    ips200_show_string(5, 5," leftwheel_P:");
                    ips200_show_float(120,5,left_wheel.kp,2,2);
                    ips200_show_string(5,25,">leftwheel_I:");
                    ips200_show_float(120,25,left_wheel.ki,2,2);
                    ips200_show_string(5,45," leftwheel_D:");
                    ips200_show_float(120,45,left_wheel.kd,2,2);
                    ips200_show_string(5,65," right_wheel_P:");
                    ips200_show_float(120,65,right_wheel.kp,2,2);
                    ips200_show_string(5,85," right_wheel_I:");
                    ips200_show_float(120,85,right_wheel.ki,2,2);
                    ips200_show_string(5,105," right_wheel_D:");
                    ips200_show_float(120,105,right_wheel.kd,2,2);
                    break;
                }
                case 2:
                {
                    ips200_show_string(5, 5," leftwheel_P:");
                    ips200_show_float(120,5,left_wheel.kp,2,2);
                    ips200_show_string(5,25," leftwheel_I:");
                    ips200_show_float(120,25,left_wheel.ki,2,2);
                    ips200_show_string(5,45,">leftwheel_D:");
                    ips200_show_float(120,45,left_wheel.kd,2,2);
                    ips200_show_string(5,65," right_wheel_P:");
                    ips200_show_float(120,65,right_wheel.kp,2,2);
                    ips200_show_string(5,85," right_wheel_I:");
                    ips200_show_float(120,85,right_wheel.ki,2,2);
                    ips200_show_string(5,105," right_wheel_D:");
                    ips200_show_float(120,105,right_wheel.kd,2,2);
                    break;
                }
                case 3:
                {
                    ips200_show_string(5, 5," leftwheel_P:");
                    ips200_show_float(120,5,left_wheel.kp,2,2);
                    ips200_show_string(5,25," leftwheel_I:");
                    ips200_show_float(120,25,left_wheel.ki,2,2);
                    ips200_show_string(5,45," leftwheel_D:");
                    ips200_show_float(120,45,left_wheel.kd,2,2);
                    ips200_show_string(5,65,">right_wheel_P:");
                    ips200_show_float(120,65,right_wheel.kp,2,2);
                    ips200_show_string(5,85," right_wheel_I:");
                    ips200_show_float(120,85,right_wheel.ki,2,2);
                    ips200_show_string(5,105," right_wheel_D:");
                    ips200_show_float(120,105,right_wheel.kd,2,2);
                    break;
                }
                case 4:
                {
                    ips200_show_string(5, 5," leftwheel_P:");
                    ips200_show_float(120,5,left_wheel.kp,2,2);
                    ips200_show_string(5,25," leftwheel_I:");
                    ips200_show_float(120,25,left_wheel.ki,2,2);
                    ips200_show_string(5,45," leftwheel_D:");
                    ips200_show_float(120,45,left_wheel.kd,2,2);
                    ips200_show_string(5,65," right_wheel_P:");
                    ips200_show_float(120,65,right_wheel.kp,2,2);
                    ips200_show_string(5,85,">right_wheel_I:");
                    ips200_show_float(120,85,right_wheel.ki,2,2);
                    ips200_show_string(5,105," right_wheel_D:");
                    ips200_show_float(120,105,right_wheel.kd,2,2);
                    break;
                }
                case 5:
                {
                    ips200_show_string(5, 5," leftwheel_P:");
                    ips200_show_float(120,5,left_wheel.kp,2,2);
                    ips200_show_string(5,25," leftwheel_I:");
                    ips200_show_float(120,25,left_wheel.ki,2,2);
                    ips200_show_string(5,45," leftwheel_D:");
                    ips200_show_float(120,45,left_wheel.kd,2,2);
                    ips200_show_string(5,65," right_wheel_P :");
                    ips200_show_float(120,65,right_wheel.kp,2,2);
                    ips200_show_string(5,85," right_wheel_I:");
                    ips200_show_float(120,85,right_wheel.ki,2,2);
                    ips200_show_string(5,105,">right_wheel_D:");
                    ips200_show_float(120,105,right_wheel.kd,2,2);
                    break;
                }
            }
            break;
        }
        case 2:
        {
            switch(disp_index)
            {
                case 0:
                {
                    ips200_show_string(5, 5,">dif_wheel_P:");
                    ips200_show_float(120,5,dif_wheel.kp,2,2);
                    ips200_show_string(5,25," dif_wheel_I:");
                    ips200_show_float(120,25,dif_wheel.ki,2,2);
                    ips200_show_string(5,45," dif_wheel_D:");
                    ips200_show_float(120,45,dif_wheel.kd,2,2);
                    ips200_show_string(5,65," servo_fuck_P :");
                    ips200_show_float(120,65,servo_fuck.kp,2,2);
                    ips200_show_string(5,85," servo_fuck_I:");
                    ips200_show_float(120,85,servo_fuck.ki,2,2);
                    ips200_show_string(5,105," servo_fuck_D:");
                    ips200_show_float(120,105,servo_fuck.kd,2,2);
                    break;
                }
                case 1:
                {
                    ips200_show_string(5, 5," difwheel_P:");
                    ips200_show_float(120,5,dif_wheel.kp,2,2);
                    ips200_show_string(5,25,">difwheel_I:");
                    ips200_show_float(120,25,dif_wheel.ki,2,2);
                    ips200_show_string(5,45," difwheel_D:");
                    ips200_show_float(120,45,dif_wheel.kd,2,2);
                    ips200_show_string(5,65," servo_fuck_P :");
                    ips200_show_float(120,65,servo_fuck.kp,2,2);
                    ips200_show_string(5,85," servo_fuck_I:");
                    ips200_show_float(120,85,servo_fuck.ki,2,2);
                    ips200_show_string(5,105," servo_fuck_D:");
                    ips200_show_float(120,105,servo_fuck.kd,2,2);
                    break;
                }
                case 2:
                {
                    ips200_show_string(5, 5," difwheel_P:");
                    ips200_show_float(120,5,dif_wheel.kp,2,2);
                    ips200_show_string(5,25," difwheel_I:");
                    ips200_show_float(120,25,dif_wheel.ki,2,2);
                    ips200_show_string(5,45,">difwheel_D:");
                    ips200_show_float(120,45,dif_wheel.kd,2,2);
                    ips200_show_string(5,65," servo_fuck_P :");
                    ips200_show_float(120,65,servo_fuck.kp,2,2);
                    ips200_show_string(5,85," servo_fuck_I:");
                    ips200_show_float(120,85,servo_fuck.ki,2,2);
                    ips200_show_string(5,105," servo_fuck_D:");
                    ips200_show_float(120,105,servo_fuck.kd,2,2);
                    break;
                }
                case 3:
                {
                    ips200_show_string(5, 5," difwheel_P:");
                    ips200_show_float(120,5,dif_wheel.kp,2,2);
                    ips200_show_string(5,25," difwheel_I:");
                    ips200_show_float(120,25,dif_wheel.ki,2,2);
                    ips200_show_string(5,45," difwheel_D:");
                    ips200_show_float(120,45,dif_wheel.kd,2,2);
                    ips200_show_string(5,65,">servo_fuck_P :");
                    ips200_show_float(120,65,servo_fuck.kp,2,2);
                    ips200_show_string(5,85," servo_fuck_I:");
                    ips200_show_float(120,85,servo_fuck.ki,2,2);
                    ips200_show_string(5,105," servo_fuck_D:");
                    ips200_show_float(120,105,servo_fuck.kd,2,2);
                    break;
                }
                case 4:
                {
                    ips200_show_string(5, 5," difwheel_P:");
                    ips200_show_float(120,5,dif_wheel.kp,2,2);
                    ips200_show_string(5,25," difwheel_I:");
                    ips200_show_float(120,25,dif_wheel.ki,2,2);
                    ips200_show_string(5,45," difwheel_D:");
                    ips200_show_float(120,45,dif_wheel.kd,2,2);
                    ips200_show_string(5,65," servo_fuck_P :");
                    ips200_show_float(120,65,servo_fuck.kp,2,2);
                    ips200_show_string(5,85,">servo_fuck_I:");
                    ips200_show_float(120,85,servo_fuck.ki,2,2);
                    ips200_show_string(5,105," servo_fuck_D:");
                    ips200_show_float(120,105,servo_fuck.kd,2,2);
                    break;
                }
                case 5:
                {
                    ips200_show_string(5, 5," difwheel_P:");
                    ips200_show_float(120,5,dif_wheel.kp,2,2);
                    ips200_show_string(5,25," difwheel_I:");
                    ips200_show_float(120,25,dif_wheel.ki,2,2);
                    ips200_show_string(5,45," difwheel_D:");
                    ips200_show_float(120,45,dif_wheel.kd,2,2);
                    ips200_show_string(5,65," servo_fuck_P :");
                    ips200_show_float(120,65,servo_fuck.kp,2,2);
                    ips200_show_string(5,85," servo_fuck_I:");
                    ips200_show_float(120,85,servo_fuck.ki,2,2);
                    ips200_show_string(5,105,">servo_fuck_D:");
                    ips200_show_float(120,105,servo_fuck.kd,2,2);
                    break;
                }
            }
            break;
        }
    }
}



void menu_control(int16* menu_index,int16* disp_index,int16 key_down,motor_element* left_wheel,motor_element* right_wheel,dif_element *dif_wheel,servo_element *servo_fuck)
{
    switch(key_down)
    {
        case 1:
        {
            switch(*menu_index)
            {
                case 0:
                {
                    switch(*disp_index)
                    {
                        case 0:
                        {
                            ips200_clear();
                            *menu_index = 1;
                            *disp_index = 0;
                            break;
                        }
                        case 1:
                        {
                            ips200_clear();
                            *menu_index = 2;
                            *disp_index = 0;
                            break;
                        }
                    }
                    break;
                }
                case 1:
                {
                    switch(*disp_index)
                    {
                        case 0:
                        {
                            change[0] = 1;
                            star[0] = 1;
                            break;
                        }
                        case 1:
                        {
                            change[1] = 1;
                            star[1] = 1;
                            break;
                        }
                        case 2:
                        {
                            change[2] = 1;
                            star[2] = 1;
                            break;
                        }
                        case 3:
                        {
                            change[3] = 1;
                            star[3] = 1;
                            break;
                        }
                        case 4:
                        {
                            change[4] = 1;
                            star[4] = 1;
                            break;
                        }
                        case 5:
                        {
                            change[5] = 1;
                            star[5] = 1;
                            break;
                        }
                    }
                    break;
                }
                case 2:
                {
                    switch(*disp_index)
                    {
                        case 0:
                        {
                            change_dif[0] = 1;
                            break;
                        }
                        case 1:
                        {
                            change_dif[1] = 1;
                            break;
                        }
                        case 2:
                        {
                            change_dif[2] = 1;
                            break;
                        }
                        case 3:
                        {
                            change_dif[3] = 1;
                            break;
                        }
                        case 4:
                        {
                            change_dif[4] = 1;
                            break;
                        }
                        case 5:
                        {
                            change_dif[5] = 1;
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        case 2:
        {
            switch(*menu_index)
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    switch(*disp_index)
                    {
                        case 0:
                        {
                            ips200_clear();
                            if(change[0] == 1)
                            {
                                change[0] = 0;
                                star[0] = 0;
                            }
                            else if(change[0] == 0)
                            {
                                *menu_index = 0;
                                *disp_index = 0;
                            }
                            break;
                        }
                        case 1:
                        {
                            ips200_clear();
                            if(change[1] == 1)
                            {
                                change[1] = 0;
                                star[1] = 0;
                            }
                            else if(change[1] == 0)
                            {
                                ips200_clear();
                                *menu_index = 0;
                                *disp_index = 0;
                            }
                            break;
                        }
                        case 2:
                        {
                            ips200_clear();
                            if(change[2] == 1)
                            {
                                change[2] = 0;
                                star[2] = 0;
                            }
                            else if(change[2] == 0)
                            {
                                ips200_clear();
                                *menu_index = 0;
                                *disp_index = 0;
                            }
                            break;
                        }
                        case 3:
                        {
                            ips200_clear();
                            if(change[3] == 1)
                            {
                                change[3] = 0;
                                star[3] = 0;
                            }
                            else if(change[3] == 0)
                            {
                                ips200_clear();
                                *menu_index = 0;
                                *disp_index = 0;
                            }
                            break;
                        }
                        case 4:
                        {
                            ips200_clear();
                            if(change[4] == 1)
                            {
                                change[4] = 0;
                                star[4] = 0;
                            }
                            else if(change[4] == 0)
                            {
                                ips200_clear();
                                *menu_index = 0;
                                *disp_index = 0;
                            }
                            break;
                        }
                        case 5:
                        {
                            ips200_clear();
                            if(change[5] == 1)
                            {
                                change[5] = 0;
                                star[5] = 0;
                            }
                            else if(change[5] == 0)
                            {
                                ips200_clear();
                                *menu_index = 0;
                                *disp_index = 0;
                            }
                            break;
                        }
                    }
                    break;
                }
                case 2:
                {
                    switch(*disp_index)
                    {
                        case 0:
                        {
                            ips200_clear();
                            if(change_dif[0] == 1)
                            {
                                change_dif[0] = 0;
                            }
                            else if(change_dif[0] == 0)
                            {
                                *menu_index = 0;
                                *disp_index = 0;
                            }
                            break;
                        }
                        case 1:
                        {
                            ips200_clear();
                            if(change_dif[1] == 1)
                            {
                                change_dif[1] = 0;
                            }
                            else if(change_dif[1] == 0)
                            {
                                ips200_clear();
                                *menu_index = 0;
                                *disp_index = 0;
                            }
                            break;
                        }
                        case 2:
                        {
                            ips200_clear();
                            if(change_dif[2] == 1)
                            {
                                change_dif[2] = 0;
                            }
                            else if(change_dif[2] == 0)
                            {
                                ips200_clear();
                                *menu_index = 0;
                                *disp_index = 0;
                            }
                            break;
                        }
                        case 3:
                        {
                            ips200_clear();
                            if(change_dif[3] == 1)
                            {
                                change_dif[3] = 0;
                            }
                            else if(change_dif[3] == 0)
                            {
                                ips200_clear();
                                *menu_index = 0;
                                *disp_index = 0;
                            }
                            break;
                        }
                        case 4:
                        {
                            ips200_clear();
                            if(change_dif[4] == 1)
                            {
                                change_dif[4] = 0;
                            }
                            else if(change_dif[4] == 0)
                            {
                                ips200_clear();
                                *menu_index = 0;
                                *disp_index = 0;
                            }
                            break;
                        }
                        case 5:
                        {
                            ips200_clear();
                            if(change_dif[5] == 1)
                            {
                                change_dif[5] = 0;
                            }
                            else if(change_dif[5] == 0)
                            {
                                ips200_clear();
                                *menu_index = 0;
                                *disp_index = 0;
                            }
                            break;
                        }
                    }
                }
            }
            break;
        }
        case 3:
        {
            switch(*menu_index)
            {
                case 0:
                {
                    ips200_clear();
                    if(--*disp_index == -1)*disp_index = 3;
                    break;
                }
                case 1:
                {
                    ips200_clear();
                    if(change[0] == 1)left_wheel->kp += 0.1;
                    else if(change[1] == 1)left_wheel->ki += 0.1;
                    else if(change[2] == 1)left_wheel->kd += 0.1;
                    else if(change[3] == 1)right_wheel->kp += 0.1;
                    else if(change[4] == 1)right_wheel->ki += 0.1;
                    else if(change[5] == 1)right_wheel->kd += 0.1;
                    else
                    {
                        if(--*disp_index == -1)*disp_index = 5;
                    }
                    break;
                }
                case 2:
                {
                    ips200_clear();
                    if(change_dif[0] == 1)dif_wheel->kp += 0.1;
                    else if(change_dif[1] == 1)dif_wheel->ki += 0.1;
                    else if(change_dif[2] == 1)dif_wheel->kd += 0.1;
                    else if(change_dif[3] == 1)servo_fuck->kp += 0.1;
                    else if(change_dif[4] == 1)servo_fuck->ki += 0.1;
                    else if(change_dif[5] == 1)servo_fuck->kd += 0.1;
                    else
                    {
                        if(--*disp_index == -1)*disp_index = 5;
                    }
                    break;
                }
            }
            break;
        }
        case 4:
        {
            switch(*menu_index)
            {
                case 0:
                {
                    ips200_clear();
                    if(++*disp_index == 4)*disp_index = 0;
                    break;
                }
                case 1:
                {
                    ips200_clear();
                    if(change[0] == 1)left_wheel->kp -= 0.1;
                    else if(change[1] == 1)left_wheel->ki -= 0.1;
                    else if(change[2] == 1)left_wheel->kd -= 0.1;
                    else if(change[3] == 1)right_wheel->kp -= 0.1;
                    else if(change[4] == 1)right_wheel->ki -= 0.1;
                    else if(change[5] == 1)right_wheel->kd -= 0.1;
                    else
                    {
                        if(++*disp_index == 6)*disp_index = 0;
                    }
                    break;
                }
                case 2:
                {
                    ips200_clear();
                    if(change_dif[0] == 1)dif_wheel->kp -= 0.1;
                    else if(change_dif[1] == 1)dif_wheel->ki -= 0.1;
                    else if(change_dif[2] == 1)dif_wheel->kd -= 0.1;
                    else if(change_dif[3] == 1)servo_fuck->kp -= 0.1;
                    else if(change_dif[4] == 1)servo_fuck->ki -= 0.1;
                    else if(change_dif[5] == 1)servo_fuck->kd -= 0.1;
                    else
                    {
                        if(++*disp_index == 6)*disp_index = 0;
                    }
                    break;
                }
            }
        }
    }
}
