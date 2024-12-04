/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          cpu0_main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.4
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "cpu0_main.h"
#pragma section all "cpu0_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������

// **************************** �������� ****************************

#define BOUNDARY_NUM            (MT9V03X_H * 3 / 2)
// ֻ��X�߽�
uint8 xy_x1_boundary[BOUNDARY_NUM], xy_x2_boundary[BOUNDARY_NUM], xy_x3_boundary[BOUNDARY_NUM];

// ֻ��Y�߽�
uint8 xy_y1_boundary[BOUNDARY_NUM], xy_y2_boundary[BOUNDARY_NUM], xy_y3_boundary[BOUNDARY_NUM];

// X Y�߽綼�ǵ���ָ����
uint8 x1_boundary[MT9V03X_H], x2_boundary[MT9V03X_H], x3_boundary[MT9V03X_H];
uint8 y1_boundary[MT9V03X_W], y2_boundary[MT9V03X_W], y3_boundary[MT9V03X_W];

// ͼ�񱸷����飬�ڷ���ǰ��ͼ�񱸷��ٽ��з��ͣ��������Ա���ͼ�����˺�ѵ�����
uint8 image_copy[MT9V03X_H][MT9V03X_W];


int core0_main(void)
{
    clock_init();                   // ��ȡʱ��Ƶ��<��ر���>
    debug_init();                   // ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�û����� ���������ʼ�������

    mt9v03x_init();//��ͷ��ʼ��
    encoder_quad_init(ENCODER_1, ENCODER_1_A, ENCODER_1_B);          // ��ʼ��������ģ�������� �������������ģʽ
    encoder_dir_init (ENCODER_3, ENCODER_3_A, ENCODER_3_B);          // ��ʼ��������ģ�������� ����������������ģʽ

    pwm_init(ATOM1_CH3_P21_5,17000,1000);
    pwm_init(ATOM1_CH0_P21_2,17000,1000);
    pwm_init(SERVO_MOTOR_PWM,50,740);

    system_init();
    PID_LMotor_Init(&left_wheel);
    PID_RMotor_Init(&right_wheel);
    PID_Servo_Init(&servo_fuck);
    PID_DIF_Init(&dif_wheel);
    system_start();//���ö�ʱ��


    // �˴���д�û����� ���������ʼ�������
    pit_ms_init(CCU60_CH1, INTERTIME);

    cpu_wait_event_ready();         // �ȴ����к��ĳ�ʼ�����
    while (TRUE)
    {
        if (mt9v03x_finish_flag) {
            memcpy(mt9v03x_image_copy[0], mt9v03x_image[0], (sizeof(mt9v03x_image_copy) / sizeof(uint8_t)));
            mt9v03x_finish_flag = 0;
            state_type = COMMON_STATE;
            //GetImgBin_Average(mt9v03x_image_copy[0], &FIX_BINTHRESHOLD);//ƽ��ֵ��
            img_processing();
            get_corners();
            tracking_line();//ѡ��Ѳ�߷�ʽ��Ѳ����or����
            ElementJudge();
            aim_distance_select();
            ElementRun();
            MidLineTrack();
        }
        // �˴���д��Ҫѭ��ִ�еĴ���

        Key_Proc(&Key_Val,&Key_Old,&Key_Down,&Key_Up);
        menu_disp(menu_index,disp_index);
        menu_control(&menu_index,&disp_index,Key_Down,&left_wheel,&right_wheel,&dif_wheel,&servo_fuck);
        // �˴���д��Ҫѭ��ִ�еĴ���
//        printf("%f\n",(Voltage-3875)/2);
        ips200_show_float(5,155, left_wheel.out_speed - (dif_wheel.dif_out/2),4,2);
        ips200_show_float(5,175,right_wheel.out_speed + (dif_wheel.dif_out/2),4,2);
        ips200_show_float(5,195,dif_wheel.dif_out,4,2);

    }
}

IFX_INTERRUPT(cc60_pit_ch1_isr, 0, CCU6_0_CH1_ISR_PRIORITY)
{
    interrupt_global_enable(0);                     // �����ж�Ƕ��
    pit_clear_flag(CCU60_CH1);


    if(++key_slow == 500)
    {
        key_slow = 0;
        Voltage = adc_mean_filter_convert(ADC0_CH8_A8,50);
        ips200_show_string(5,215,"Voltage:");
        ips200_show_float(75,215,(Voltage-3875)/2.2,4,2);
        ips200_show_string(110,215,"%");
    }

    float data_1,data_3;

    data_1 =  encoder_get_count(ENCODER_1);                          // ��ȡ����������
    data_3 = -encoder_get_count(ENCODER_3);                          // ��ȡ����������

    encoder_clear_count(ENCODER_1);                                 // ��ձ���������
    encoder_clear_count(ENCODER_3);                                 // ��ձ���������

    Read_Enconder(&left_wheel,&right_wheel,data_1,data_3);

    PID_Motor(&left_wheel);
    PID_Motor(&right_wheel);
    PID_DIF(&dif_wheel,pure_angle);
    PID_SERVO(&servo_fuck,pure_angle);

//    Motor_begin(&left_wheel,&right_wheel,&dif_wheel);





    pwm_set_duty(SERVO_MOTOR_PWM,servo_fuck.out_turn);
    pwm_set_duty(ATOM1_CH3_P21_5, left_wheel.out_speed - (dif_wheel.dif_out/2));
    pwm_set_duty(ATOM1_CH0_P21_2,right_wheel.out_speed + (dif_wheel.dif_out/2));

}
#pragma section all restore


// **************************** �������� ****************************
