/*
 * Smart_Init.c
 *
 *  Created on: 2024Äê9ÔÂ18ÈÕ
 *      Author: lenovo
 */


#include "Smart_Init.h"
#include "Kalman.h"

int16 encoder_data_1 = 0;
int16 encoder_data_3 = 0;

extern KalmanFilter ENCODER01_ERROR;
extern KalmanFilter ENCODER03_ERROR;
extern KalmanFilter ANGLE_ERROR;

void system_init(void)
{
    ips200_init(IPS200_TYPE_SPI);



    kalman_init(&ENCODER01_ERROR,0.0f,1.0f,0.1f,1.0f);
    kalman_init(&ENCODER03_ERROR,0.0f,1.0f,0.1f,1.0f);
    kalman_init(&ANGLE_ERROR    ,0.0f,1.0f,0.1f,1.0f);
}

