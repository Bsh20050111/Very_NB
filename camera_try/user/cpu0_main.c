/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          cpu0_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.4
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "cpu0_main.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设

// **************************** 代码区域 ****************************

#define BOUNDARY_NUM            (MT9V03X_H * 3 / 2)
// 只有X边界
uint8 xy_x1_boundary[BOUNDARY_NUM], xy_x2_boundary[BOUNDARY_NUM], xy_x3_boundary[BOUNDARY_NUM];

// 只有Y边界
uint8 xy_y1_boundary[BOUNDARY_NUM], xy_y2_boundary[BOUNDARY_NUM], xy_y3_boundary[BOUNDARY_NUM];

// X Y边界都是单独指定的
uint8 x1_boundary[MT9V03X_H], x2_boundary[MT9V03X_H], x3_boundary[MT9V03X_H];
uint8 y1_boundary[MT9V03X_W], y2_boundary[MT9V03X_W], y3_boundary[MT9V03X_W];

// 图像备份数组，在发送前将图像备份再进行发送，这样可以避免图像出现撕裂的问题
uint8 image_copy[MT9V03X_H][MT9V03X_W];


int core0_main(void)
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等

    mt9v03x_init();//镜头初始化
    encoder_quad_init(ENCODER_1, ENCODER_1_A, ENCODER_1_B);          // 初始化编码器模块与引脚 正交解码编码器模式
    encoder_dir_init (ENCODER_3, ENCODER_3_A, ENCODER_3_B);          // 初始化编码器模块与引脚 带方向增量编码器模式

    pwm_init(ATOM1_CH3_P21_5,17000,1000);
    pwm_init(ATOM1_CH0_P21_2,17000,1000);
    pwm_init(SERVO_MOTOR_PWM,50,740);

    system_init();
    PID_LMotor_Init(&left_wheel);
    PID_RMotor_Init(&right_wheel);
    PID_Servo_Init(&servo_fuck);
    PID_DIF_Init(&dif_wheel);
    system_start();//启用定时器


    // 此处编写用户代码 例如外设初始化代码等
    pit_ms_init(CCU60_CH1, INTERTIME);

    cpu_wait_event_ready();         // 等待所有核心初始化完毕
    while (TRUE)
    {
        if (mt9v03x_finish_flag) {
            memcpy(mt9v03x_image_copy[0], mt9v03x_image[0], (sizeof(mt9v03x_image_copy) / sizeof(uint8_t)));
            mt9v03x_finish_flag = 0;
            state_type = COMMON_STATE;
            //GetImgBin_Average(mt9v03x_image_copy[0], &FIX_BINTHRESHOLD);//平均值法
            img_processing();
            get_corners();
            tracking_line();//选择巡线方式，巡左线or右线
            ElementJudge();
            aim_distance_select();
            ElementRun();
            MidLineTrack();
        }
        // 此处编写需要循环执行的代码

        Key_Proc(&Key_Val,&Key_Old,&Key_Down,&Key_Up);
        menu_disp(menu_index,disp_index);
        menu_control(&menu_index,&disp_index,Key_Down,&left_wheel,&right_wheel,&dif_wheel,&servo_fuck);
        // 此处编写需要循环执行的代码
//        printf("%f\n",(Voltage-3875)/2);
        ips200_show_float(5,155, left_wheel.out_speed - (dif_wheel.dif_out/2),4,2);
        ips200_show_float(5,175,right_wheel.out_speed + (dif_wheel.dif_out/2),4,2);
        ips200_show_float(5,195,dif_wheel.dif_out,4,2);

    }
}

IFX_INTERRUPT(cc60_pit_ch1_isr, 0, CCU6_0_CH1_ISR_PRIORITY)
{
    interrupt_global_enable(0);                     // 开启中断嵌套
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

    data_1 =  encoder_get_count(ENCODER_1);                          // 获取编码器计数
    data_3 = -encoder_get_count(ENCODER_3);                          // 获取编码器计数

    encoder_clear_count(ENCODER_1);                                 // 清空编码器计数
    encoder_clear_count(ENCODER_3);                                 // 清空编码器计数

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


// **************************** 代码区域 ****************************
