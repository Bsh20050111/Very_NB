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
* 文件名称          cpu1_main
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

#include "zf_common_headfile.h"
#pragma section all "cpu1_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU1的RAM中

// **************************** 代码区域 ****************************

#include "headfile.h"

void core1_main(void)
{
    disable_Watchdog();                     // 关闭看门狗
    interrupt_global_enable(0);             // 打开全局中断
    // 此处编写用户代码 例如外设初始化代码等

    mt9v03x_init();//镜头初始化

    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();                 // 等待所有核心初始化完毕
    system_start();//启用定时器
    while (TRUE)
    {
//        Atimer_start(1);
        if (mt9v03x_finish_flag) {
            memcpy(mt9v03x_image_copy[0], mt9v03x_image[0], (sizeof(mt9v03x_image_copy) / sizeof(uint8_t)));
            mt9v03x_finish_flag = 0;
            state_type = COMMON_STATE;
            GetImgBin_Average(mt9v03x_image_copy[0], &FIX_BINTHRESHOLD);//平均值法
            img_processing();
            get_corners();
            tracking_line();//选择巡线方式，巡左线or右线
            ElementJudge();
            aim_distance_select();
            ElementRun();
            MidLineTrack();
//            printf("%d",(int16)pure_angle);
//            if(abs((pure_angle)*1.2)<=75)
//                pwm_set_duty(ATOM0_CH6_P02_6,740+(pure_angle)*1.2);
//            else
//                pwm_set_duty(ATOM0_CH6_P02_6,740+75);
//
//            pwm_set_duty(ATOM1_CH3_P21_5,800);
//            pwm_set_duty(ATOM1_CH0_P21_2,800);

            //最后的输出中线为mid_track和mid_track_count
            //最后传出角度为tracking.c中的pure_angle
            /*可用数据有：
             * 1、十字内时，tracking.c中的curvature，中线的整体曲率
             * 2、date.c中的angle_new_left/right，边线上各点的曲率
             */

//            ips200_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, 2*MT9V03X_W, 2*MT9V03X_H, FIX_BINTHRESHOLD);
//
//            for(uint16 i=0;i<pts_resample_left_count;i++){
//                ips200_draw_point((uint16)pts_resample_left[i][1]*2, (uint16)pts_resample_left[i][0]*2, RGB565_RED);
//            }
//            for(uint16 i=0;i<pts_resample_right_count;i++){
//                ips200_draw_point((uint16)pts_resample_right[i][1]*2, (uint16)pts_resample_right[i][0]*2, RGB565_BLUE);
//            }
//
//            for(uint16 i=0;i<mid_track_count;i++){
//                ips200_draw_point((uint16)mid_track[i][1]*2, (uint16)mid_track[i][0]*2, RGB565_BLACK);
//            }
//
//            ips200_show_int(50,210,(int16)pure_angle,3);
//            ips200_show_uint(0,210,(uint16)state_type,3);
//            Atimer_stop(1);
//            ips200_show_uint(100,210,Atimer_get(1),3);
        }

    }
}
#pragma section all restore
// **************************** 代码区域 ****************************
