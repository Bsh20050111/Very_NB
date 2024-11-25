/*
 * time.c
 *
 *  Created on: 2024年11月21日
 *      Author: A
 */

#include "zf_common_headfile.h"

// 定义10纳秒到毫秒的换算
#define NS_TO_MS (100000) // 1ms = 1,000,000ns

typedef struct {
    bool is_running;       // 定时器是否正在运行
    uint32_t start_time;   // 定时器启动的时间（单位：10纳秒）
    uint32_t elapsed_time; // 已经过的时间（单位：10纳秒）
} ATimer;


ATimer Atimers[5];


void Atimer_start(uint8 timer_id){
    if (timer_id >= 5) return;

    Atimers[timer_id].start_time = system_getval();
    Atimers[timer_id].is_running = true;
    Atimers[timer_id].elapsed_time = 0; // 重置已用时间
}

void Atimer_stop(uint8 timer_id){
    if (timer_id >= 5 || !Atimers[timer_id].is_running) return;

    uint32_t current_time = system_getval();
    Atimers[timer_id].elapsed_time = current_time - Atimers[timer_id].start_time;

    Atimers[timer_id].is_running = false;

}

void Atimer_clear(uint8 timer_id){
    if (timer_id >= 5) return;

    Atimers[timer_id].is_running = false;
    Atimers[timer_id].start_time = 0;
    Atimers[timer_id].elapsed_time = 0;
}

uint16 Atimer_get(uint8 timer_id){
    uint16 return_value = 0;
    if (timer_id >= 5) return 0;

    if (Atimers[timer_id].is_running) {
        uint32_t current_time = system_getval();
        uint32_t elapsed_ns;
        elapsed_ns = current_time - Atimers[timer_id].start_time;
        return_value=elapsed_ns / NS_TO_MS;
        return return_value ;
    } else {
        return_value=Atimers[timer_id].elapsed_time / NS_TO_MS;
        return return_value ;
    }

}
