/*
 * flash.h
 *
 *  Created on: 2024Äê12ÔÂ5ÈÕ
 *      Author: lenovo
 */

#ifndef USER_CONTORL_FLASH_H_
#define USER_CONTORL_FLASH_H_

#include "zf_common_headfile.h"
#include "Smart_headfile.h"
#include "headfile.h"

#define PID_PAGE_INDEX 8

void Flash_Pid_storage(void);
void Flash_Pid_read(void);

#endif /* USER_CONTORL_FLASH_H_ */
