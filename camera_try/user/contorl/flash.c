/*
 * flash.c
 *
 *  Created on: 2024年12月5日
 *      Author: lenovo
 */

#include "flash.h"

void Flash_Pid_storage(void)
{
    flash_buffer_clear();
    flash_union_buffer[0].float_type = left_wheel.kp;
    flash_union_buffer[1].float_type = left_wheel.ki;
    flash_union_buffer[2].float_type = right_wheel.kp;
    flash_union_buffer[3].float_type = right_wheel.ki;
    flash_union_buffer[4].float_type = dif_wheel.kp;
    flash_union_buffer[5].float_type = dif_wheel.ki;
    flash_union_buffer[6].float_type = servo_fuck.kp;
    flash_union_buffer[7].float_type = servo_fuck.kd;
    flash_union_buffer[8].float_type= cricle_aim;
    flash_union_buffer[9].float_type= cross_aim;
    flash_union_buffer[10].float_type= common_aim;
    flash_union_buffer[11].float_type= straight_aim;
    flash_union_buffer[12].float_type= turn_aim;
    flash_union_buffer[13].float_type= mid_aim;
    flash_union_buffer[14].float_type= barrier_aim;
    flash_write_page_from_buffer(0, PID_PAGE_INDEX);
}

void Flash_Pid_read(void)
{
    flash_buffer_clear();//清空缓冲区
    if(flash_check(0, PID_PAGE_INDEX)){
        flash_read_page_to_buffer(0, PID_PAGE_INDEX);
        left_wheel.kp = flash_union_buffer[0].float_type;
        left_wheel.ki = flash_union_buffer[1].float_type;
        right_wheel.kp = flash_union_buffer[2].float_type;
        right_wheel.ki = flash_union_buffer[3].float_type;
        dif_wheel.kp = flash_union_buffer[4].float_type;
        dif_wheel.ki = flash_union_buffer[5].float_type;
        servo_fuck.kp = flash_union_buffer[6].float_type;
        servo_fuck.kd = flash_union_buffer[7].float_type;
        cricle_aim = flash_union_buffer[8].float_type;
        cross_aim = flash_union_buffer[9].float_type;
        common_aim = flash_union_buffer[10].float_type;
        straight_aim = flash_union_buffer[11].float_type;
        turn_aim = flash_union_buffer[12].float_type;
        mid_aim = flash_union_buffer[13].float_type;
        barrier_aim = flash_union_buffer[14].float_type;
    }
}

