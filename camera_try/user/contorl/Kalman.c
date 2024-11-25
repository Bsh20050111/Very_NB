/*
 * Kalman.c
 *
 *  Created on: 2024��11��24��
 *      Author: lenovo
 */

#include "Smart_headfile.h"
#include "zf_common_headfile.h"
#include "Kalman.h"

KalmanFilter ENCODER01_ERROR;
KalmanFilter ENCODER03_ERROR;
KalmanFilter ANGLE_ERROR;

void kalman_init(KalmanFilter *kf, float initial_estimate, float initial_error, float process_noise, float measurement_noise) {
    kf->x = initial_estimate;  // ��ʼ����
    kf->P = initial_error;     // ��ʼ���Э����
    kf->Q = process_noise;     // ��������Э����
    kf->R = measurement_noise; // ��������Э����
    kf->K = 0.0f;              // �����������ʼ��
}


// �������˲�Ԥ��͸���
void kalman_update(KalmanFilter *kf, float measurement) {
    // Ԥ�ⲽ�� (ͨ��ģ�Ͳ���ʱ������ֱ������һ��״ֵ̬��ΪԤ��)
    // Ԥ����ƣ�������x = x_prev + u, ����uΪ�գ���ΪԤ��Ϊ��ǰ���ƣ�

    // ���¿���������
    kf->K = kf->P / (kf->P + kf->R);

    // ���¹���ֵ��У����
    kf->x = kf->x + kf->K * (measurement - kf->x);

    // �������Э����
    kf->P = (1 - kf->K) * kf->P + kf->Q;
}
