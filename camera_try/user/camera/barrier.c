/*
 * barrier.c
 *
 *  Created on: 2024Äê10ÔÂ12ÈÕ
 *      Author: A
 */
#include "headfile.h"

enum barrier_type_e barrier_type = BARRIER_NONE;
enum s_type_e s_type             = S_NONE;
enum shield_type_e shield_type   = SHIELD_NONE;
float (*mid_track_s)[2];
int32_t mid_track_count_s;
int temp_min_s;
int temp_max_s;
int barrier_begin_flag = 0;
int barrier_count      = 0;
float barrirer_time=500.f;

void CheckBarrier()
{
    if (barrier_type == BARRIER_NONE && Lpt0_found_barrier_in && !Lpt1_found_barrier_in && is_straight1) {
        barrier_type = BARRIER_LEFT_BEGIN;
    }
    if (barrier_type == BARRIER_NONE && !Lpt0_found_barrier_in && Lpt1_found_barrier_in && is_straight0) {
        barrier_type = BARRIER_RIGHT_BEGIN;
    }
}

void RunBarrier()
{
    if (barrier_type == BARRIER_LEFT_BEGIN || barrier_type == BARRIER_LEFT_RUNNING) {
        track_type = TRACK_RIGHT;
        if (barrier_type == BARRIER_LEFT_BEGIN)
        {
            Atimer_clear(2);
            Atimer_start(2);
            barrier_type = BARRIER_LEFT_RUNNING;
        }
        if (barrier_type == BARRIER_LEFT_RUNNING)
        {
            if (Atimer_get(2) >= barrirer_time)
            {
                barrier_type = BARRIER_NONE;
                Atimer_stop(2);
                Atimer_clear(2);
            }
            else{
                barrier_type = BARRIER_LEFT_RUNNING;
            }
        }

    }

    if (barrier_type == BARRIER_RIGHT_BEGIN || barrier_type == BARRIER_RIGHT_RUNNING) {
        track_type = TRACK_LEFT;
        if (barrier_type == BARRIER_RIGHT_BEGIN)
        {
            Atimer_clear(2);
            Atimer_start(2);
            barrier_type = BARRIER_RIGHT_RUNNING;
        }
        if (barrier_type == BARRIER_RIGHT_RUNNING)
        {
            if (Atimer_get(2) >= barrirer_time)
            {
                barrier_type = BARRIER_NONE;
                Atimer_stop(2);
                Atimer_clear(2);
            }
            else{
                barrier_type = BARRIER_RIGHT_RUNNING;
            }
        }
    }
}


void Check_s()
{
    if (track_type == TRACK_LEFT) {
        mid_track_s       = mid_left;
        mid_track_count_s = mid_left_count;
    } else {
        mid_track_s       = mid_right;
        mid_track_count_s = mid_right_count;
    }

    int min_s = 1000;
    int max_s = 1;

    for (int i = 0; i < mid_track_count_s; i++) {
        if (mid_track_s[i][1] < min_s) {
            min_s      = mid_track_s[i][1];
            temp_min_s = min_s;
        }
        if (mid_track_s[i][1] > max_s) {
            max_s      = mid_track_s[i][1];
            temp_max_s = max_s;
        }
    }

    if (is_straight0 == false && is_straight1 == false && (max_s - min_s) <= 30 && (max_s - min_s) >= 5) {
        s_type = S_BEGIN;
    }
}

void RunS()
{

    if (temp_max_s - temp_min_s > 30 || (is_straight0 && is_straight1)) {
        s_type = S_NONE;
    }
}

