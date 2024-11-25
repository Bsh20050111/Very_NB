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
* �ļ�����          cpu1_main
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

#include "zf_common_headfile.h"
#pragma section all "cpu1_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU1��RAM��

// **************************** �������� ****************************

#include "headfile.h"

void core1_main(void)
{
    disable_Watchdog();                     // �رտ��Ź�
    interrupt_global_enable(0);             // ��ȫ���ж�
    // �˴���д�û����� ���������ʼ�������

    mt9v03x_init();//��ͷ��ʼ��

    // �˴���д�û����� ���������ʼ�������
    cpu_wait_event_ready();                 // �ȴ����к��ĳ�ʼ�����
    system_start();//���ö�ʱ��
    while (TRUE)
    {
//        Atimer_start(1);
        if (mt9v03x_finish_flag) {
            memcpy(mt9v03x_image_copy[0], mt9v03x_image[0], (sizeof(mt9v03x_image_copy) / sizeof(uint8_t)));
            mt9v03x_finish_flag = 0;
            state_type = COMMON_STATE;
            GetImgBin_Average(mt9v03x_image_copy[0], &FIX_BINTHRESHOLD);//ƽ��ֵ��
            img_processing();
            get_corners();
            tracking_line();//ѡ��Ѳ�߷�ʽ��Ѳ����or����
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

            //�����������Ϊmid_track��mid_track_count
            //��󴫳��Ƕ�Ϊtracking.c�е�pure_angle
            /*���������У�
             * 1��ʮ����ʱ��tracking.c�е�curvature�����ߵ���������
             * 2��date.c�е�angle_new_left/right�������ϸ��������
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
// **************************** �������� ****************************
