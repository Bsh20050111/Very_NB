/*
 * circle.c
 *
 *  Created on: 2024��10��12��
 *      Author: A
 */

#include "headfile.h"

enum circle_type_e circle_type = CIRCLE_NONE;

int32_t Left_Border_None_Circle  = 0;
int32_t Right_Border_None_Circle = 0;

int32_t Left_Border_Have_Circle  = 0;
int32_t Right_Border_Have_Circle = 0;

int32_t Left_Border_ToLeft_Circle  = 0;
int32_t Right_Border_ToLeft_Circle = 0;

int32_t Left_Border_ToRight_Circle  = 0;
int32_t Right_Border_ToRight_Circle = 0;

int32_t ceshi = 0;

void CheckCircle()
{
    // ��Բ��ģʽ�£�����L�ǵ�, ���߳�ֱ��
    if (circle_type == CIRCLE_NONE && Lpt0_found && !Lpt1_found && is_straight1) {
        circle_type = CIRCLE_LEFT_BEGIN;
    }
    if (circle_type == CIRCLE_NONE && !Lpt0_found && Lpt1_found && is_straight0) {
        circle_type = CIRCLE_RIGHT_BEGIN;
    }
}


void RunCircle(){
    if (circle_type == CIRCLE_LEFT_BEGIN) // �󻷿�ʼ��Ѱ��ֱ������
    {
        track_type = TRACK_RIGHT;

        // �ȶ����ߺ�����
        if (pts_resample_left_count < 0.1 / RESAMPLEDIST) {
            Left_Border_None_Circle++;
        }
        if (pts_resample_left_count > 0.5 / RESAMPLEDIST && Left_Border_None_Circle > FRAMENONE) {
            Left_Border_Have_Circle++;
            if (Left_Border_Have_Circle > FRAMENONE) {
                circle_type             = CIRCLE_LEFT_IN;
                Left_Border_None_Circle = 0;
                Left_Border_Have_Circle = 0;
            }
        }
    } else if (circle_type == CIRCLE_LEFT_IN) // �뻷��Ѱ��Բ����
    {
        track_type = TRACK_LEFT;

        if (pts_resample_right[(int32_t)(0.2 / RESAMPLEDIST)][1] -
                pts_resample_right[0][1] <
            -2) {
            Right_Border_ToLeft_Circle++;
        }
        if (Right_Border_ToLeft_Circle > FRAMETOLEFT) {
            circle_type                = CIRCLE_LEFT_RUNNING;
            Right_Border_ToLeft_Circle = 0;
        }
    } else if (circle_type == CIRCLE_LEFT_RUNNING) // ����Ѳ�ߣ�Ѱ��Բ����
    {
        // track_type = TRACK_RIGHT;
        track_type = TRACK_LEFT; // ������һ��������߲��л�
        if (Lpt1_found) {
            pts_resample_right_count = mid_right_count = Lpt1_rpts1s_id;
        }
        if (Lpt1_found && Lpt1_rpts1s_id < 0.4 / RESAMPLEDIST) {
            circle_type = CIRCLE_LEFT_OUT;
        }
    } else if (circle_type == CIRCLE_LEFT_OUT) // ������Ѱ��Բ
    {
        track_type = TRACK_LEFT;

        if (is_straight1) // ����Ϊ��ֱ��
        {
            circle_type = CIRCLE_LEFT_END;
        }
    } else if (circle_type == CIRCLE_LEFT_END) // �߹�Բ����Ѱ����
    {
        track_type = TRACK_RIGHT;

        if (pts_resample_left_count < 0.2 / RESAMPLEDIST) // �����ȶ�����
        {
            Left_Border_None_Circle++;
        }
        if (pts_resample_left_count > 0.6 / RESAMPLEDIST &&
            Left_Border_None_Circle > FRAMENONE) {
            circle_type                 = CIRCLE_NONE;
            Left_Border_None_Circle     = 0;
            Left_Border_Have_Circle     = 0;
            Right_Border_ToLeft_Circle  = 0;
            Right_Border_ToRight_Circle = 0;
        }

    } else if (circle_type == CIRCLE_RIGHT_BEGIN) // �һ����ƣ�ǰ��Ѱ��ֱ��
    {
        track_type = TRACK_LEFT;

        // �ȶ����ߺ�����
        if (pts_resample_right_count < 0.3 / RESAMPLEDIST) {
            Right_Border_None_Circle++;
        }
        if (pts_resample_right_count > 0.5 / RESAMPLEDIST &&
            Right_Border_None_Circle > FRAMENONE) {
            Right_Border_Have_Circle++;
            if (Right_Border_Have_Circle > FRAMENONE) {
                circle_type              = CIRCLE_RIGHT_IN;
                Right_Border_None_Circle = 0;
                Right_Border_Have_Circle = 0;
            }
        }
    } else if (circle_type == CIRCLE_RIGHT_IN) // ���һ���Ѱ����Բ��
    {
        track_type = TRACK_RIGHT;

        if (pts_resample_left[(int32_t)(0.2 / RESAMPLEDIST)][1] -
                pts_resample_left[0][1] >
            2) {
            Left_Border_ToRight_Circle++;
        }
        if (Left_Border_ToRight_Circle > FRAMETORIGHT) {
            circle_type                = CIRCLE_RIGHT_RUNNING;
            Left_Border_ToRight_Circle = 0;
        }
    } else if (circle_type == CIRCLE_RIGHT_RUNNING) // ����Ѳ�ߣ�Ѱ��Բ����
    {
        track_type = TRACK_RIGHT;
        // track_type = TRACK_LEFT; // ������һ��������߲��л�
        if (Lpt0_found) // �⻷���ڹյ㣬���ټӹյ�����о� (�� L ��)
        {
            pts_resample_left_count = mid_left_count = Lpt0_rpts0s_id;
        }
        if (Lpt0_found && Lpt0_rpts0s_id < 0.4 / RESAMPLEDIST) {
            circle_type = CIRCLE_RIGHT_OUT;
        }
    } else if (circle_type == CIRCLE_RIGHT_OUT) // ������Ѱ��Բ
    {
        track_type = TRACK_RIGHT;

        if (is_straight0) // �Ӹ����߳����ж�
        {
            circle_type = CIRCLE_RIGHT_END;
        }
    } else if (circle_type == CIRCLE_RIGHT_END) // �߹�Բ����Ѱ����
    {
        track_type = TRACK_LEFT;

        if (pts_resample_right_count < 0.2 / RESAMPLEDIST) // �����ȶ�����
        {
            Right_Border_None_Circle++;
        }
        if (pts_resample_right_count > (0.7 / RESAMPLEDIST) && Right_Border_None_Circle > FRAMENONE) {
            circle_type                = CIRCLE_NONE;
            Right_Border_None_Circle   = 0;
            Right_Border_Have_Circle   = 0;
            Left_Border_ToLeft_Circle  = 0;
            Left_Border_ToRight_Circle = 0;
        }

    }
}
