/*
 * Smart_headfile.h
 *
 *  Created on: 2024年9月19日
 *      Author: lenovo
 */

#ifndef USER_CONTORL_SMART_HEADFILE_H_
#define USER_CONTORL_SMART_HEADFILE_H_


#define ENCODER_1                   (TIM2_ENCODER)
#define ENCODER_1_A                 (TIM2_ENCODER_CH1_P33_7)
#define ENCODER_1_B                 (TIM2_ENCODER_CH2_P33_6)

#define ENCODER_3                   (TIM6_ENCODER)
#define ENCODER_3_A                 (TIM6_ENCODER_CH1_P20_3)
#define ENCODER_3_B                 (TIM6_ENCODER_CH2_P20_0)

#define KEY1                    (P20_6)
#define KEY2                    (P20_7)
#define KEY3                    (P11_2)
#define KEY4                    (P11_3)

#define IPS200_TYPE     (IPS200_TYPE_PARALLEL8)

#define SERVO_MOTOR_PWM             (ATOM0_CH6_P02_6)                           // 定义主板上舵机对应引脚
#define SERVO_MOTOR_FREQ            (50 )                                       // 定义主板上舵机频率  请务必注意范围 50-300

#define PWM_SPEED_LEFT            (1.117)//1000pwm=1.117m/s
#define PWM_SPEED_RIGHT           (1.185)//1000pwm=1.185m/s
#define ENCODER_SPEED_LEFT        (0.00745)//0.00745*encoder = 1m
#define ENCODER_SPEED_RIGHT       (0.00790)//0.007*encoder = 1m

#define INTERTIME                 (5)
typedef struct  {
        float kp;
        float ki;
        float kd;
        float set_speed;
        float now_speed;
        float out_speed;
        float max_speed;
        float min_speed;
        float err_now;
        float err_last;
        float err_llast;
        int duty;
} motor_element;

typedef struct {
        float kp;
        float ki;
        float kd;
        float out_turn;
        float max_turn;
        float min_turn;
        float err_now;
        float err_last;
        float err_llast;
}servo_element;

typedef struct {
        float kp;
        float ki;
        float kd;
        float dif_out;
        float dif_max;
        float dif_min;
        float err_now;
        float err_last;
}dif_element;

typedef struct {
    float x;  // 当前状态（估计的速度）
    float P;  // 当前状态的误差协方差
    float Q;  // 过程噪声协方差
    float R;  // 测量噪声协方差
    float K;  // 卡尔曼增益
} KalmanFilter;// 定义卡尔曼滤波器结构















#endif /* USER_CONTORL_SMART_HEADFILE_H_ */
