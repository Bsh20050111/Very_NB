/*
 * Smart_key.h
 *
 *  Created on: 2024Äê11ÔÂ23ÈÕ
 *      Author: lenovo
 */

#ifndef USER_CONTORL_SMART_KEY_H_
#define USER_CONTORL_SMART_KEY_H_

#include "zf_common_headfile.h"

extern int16 Key_Val,Key_Down,Key_Up,Key_Old;

unsigned char Key_Read(void);
void Key_Proc(int16 *Key_Val,int16 *Key_Old,int16 *Key_Down,int16 *Key_Up);

#endif /* USER_CONTORL_SMART_KEY_H_ */
