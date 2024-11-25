/*
 * Kalman.c
 *
 *  Created on: 2024年11月24日
 *      Author: lenovo
 */

#include "Smart_headfile.h"
#include "zf_common_headfile.h"
#include "Kalman.h"

KalmanFilter ENCODER01_ERROR;
KalmanFilter ENCODER03_ERROR;
KalmanFilter ANGLE_ERROR;

void kalman_init(KalmanFilter *kf, float initial_estimate, float initial_error, float process_noise, float measurement_noise) {
    kf->x = initial_estimate;  // 初始估计
    kf->P = initial_error;     // 初始误差协方差
    kf->Q = process_noise;     // 过程噪声协方差
    kf->R = measurement_noise; // 测量噪声协方差
    kf->K = 0.0f;              // 卡尔曼增益初始化
}


// 卡尔曼滤波预测和更新
void kalman_update(KalmanFilter *kf, float measurement) {
    // 预测步骤 (通常模型不变时，可以直接用上一个状态值作为预测)
    // 预测估计（此例中x = x_prev + u, 由于u为空，简化为预测为当前估计）

    // 更新卡尔曼增益
    kf->K = kf->P / (kf->P + kf->R);

    // 更新估计值（校正）
    kf->x = kf->x + kf->K * (measurement - kf->x);

    // 更新误差协方差
    kf->P = (1 - kf->K) * kf->P + kf->Q;
}
