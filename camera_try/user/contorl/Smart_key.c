/*
 * key.c
 *
 *  Created on: 2024年11月23日
 *      Author: lenovo
 */

#include "Smart_key.h"
#include "Smart_headfile.h"

int16 Key_Val,Key_Down,Key_Up,Key_Old;
uint8 key_slow = 0;

unsigned char Key_Read(void)
{
    uint8 key[4] = {0};
    uint8 temp = 0;
    key[0] = gpio_get_level(KEY1);
    key[1] = gpio_get_level(KEY2);
    key[2] = gpio_get_level(KEY3);
    key[3] = gpio_get_level(KEY4);
    if(key[0] == 0)temp = 1;
    if(key[1] == 0)temp = 2;
    if(key[2] == 0)temp = 3;
    if(key[3] == 0)temp = 4;
    return temp;
}

void Key_Proc(int16 *Key_Val,int16 *Key_Old,int16 *Key_Down,int16 *Key_Up)
{
    *Key_Val = Key_Read();//实时读取键码值
    *Key_Down = *Key_Val & (*Key_Old ^ *Key_Val);//捕捉按键下降沿
    *Key_Up = ~*Key_Val & (*Key_Old ^ *Key_Val);//捕捉按键上降沿
    *Key_Old = *Key_Val;//辅助扫描变量
}
