/*
 * tracking.c
 *
 *  Created on: 2024年10月12日
 *      Author: A
 */

#include "headfile.h"
#include <float.h>
#include <math.h>

float (*mid_track)[2];
int32_t mid_track_count;
float pure_angle;
float pure_angle_half;
float curvature;
float dx_near;
float last_curvature;
float (*rpts)[2];
int rpts_num;
float last_pure_angle = 0.0f;
int8_t turn_flag      = 0;
int circle_flag       = 1;
int pingbi_num        = 0;
int last_garage_type  = GARAGE_NONE;
float turn_threshold  = 12.0f;

// 计算最小二乘法斜率的函数
float leastSquaresSlope(float points[][2], int n)
{
    float sum_x         = 0;
    float sum_y         = 0;
    float sum_xy        = 0;
    float sum_x_squared = 0;

    // 计算各项和
    for (int i = 0; i < n; i++) {
        sum_x += points[i][1];
        sum_y += points[i][0];
        sum_xy += points[i][1] * points[i][0];
        sum_x_squared += points[i][1] * points[i][1];
    }

    // 计算斜率
    float numerator   = (float)n * sum_xy - sum_x * sum_y;
    float denominator = (float)n * sum_x_squared - sum_x * sum_x;

    if (denominator == 0) {
        // 避免除以零错误
        printf("Error: denominator is zero.\n");
        return 0;
    }

    float temp = denominator / numerator;

    return temp;
}


// 计算曲率的函数
float calculate_curvature(float x[], float y[], int n)
{
    float total_curvature = 0.0;
    n = (int)((float)n * 0.8f);

    for (int i = 1; i < n -1; i++) {
        float x1 = x[i - 1], y1 = y[i - 1];
        float x2 = x[i], y2 = y[i];
        float x3 = x[i + 1], y3 = y[i + 1];

        float dx1 = x2 - x1;
        float dy1 = y2 - y1;
        float dx2 = x3 - x2;
        float dy2 = y3 - y2;

        float dx = (dx1 + dx2) / 2;
        float dy = (dy1 + dy2) / 2;

        float ddx = x3 - 2 * x2 + x1;
        float ddy = y3 - 2 * y2 + y1;

        float numerator   = dx * ddy - dy * ddx;
        float denominator = powf(dx * dx + dy * dy, 1.5f);

        if (fabs(denominator) > FLT_EPSILON) {
            total_curvature += numerator / denominator;
        }
    }

    return total_curvature / (float)(n - 2);
}

float calculateX(float a_x, float a_y, float slope, float b_y)
{
    float b_x = a_x - (b_y - a_y) * slope;
    return b_x;
}

void tracking_line(void)
{

    if (pts_resample_left_count < pts_resample_right_count / 2 && pts_resample_left_count < 50) {
        track_type = TRACK_RIGHT;
    } else if (pts_resample_right_count < pts_resample_left_count / 2 && pts_resample_right_count < 58) {
        track_type = TRACK_LEFT;
    } else if (pts_resample_left_count < 20 && pts_resample_right_count > pts_resample_left_count) {
        track_type = TRACK_RIGHT;
    } else if (pts_resample_right_count < 20 && pts_resample_left_count > pts_resample_right_count) {
        track_type = TRACK_LEFT;
    }

}


void ElementJudge(void)
{

    if (shield_type == SHIELD_NONE) {
        CheckGarage();
        if (garage_type == GARAGE_NONE) {
            CheckCross();
            if (cross_type == CROSS_NONE) {
                CheckBarrier();
                if (barrier_type == BARRIER_NONE) {
                    CheckCircle();
                    if(circle_type==CIRCLE_NONE){
                        CheckLost();
                    }
                }
            }
        }
    }

    if (garage_type != GARAGE_NONE) {
        cross_type   = CROSS_NONE;
        circle_type  = CIRCLE_NONE;
        barrier_type = BARRIER_NONE;
        lost_type    = LOST_NONE;
    }
    if (cross_type != CROSS_NONE) {
        circle_type  = CIRCLE_NONE;
        barrier_type = BARRIER_NONE;
        lost_type    = LOST_NONE;
    }
    if (barrier_type != BARRIER_NONE) {
        circle_type = CIRCLE_NONE;
        lost_type   = LOST_NONE;
    }
    if(circle_type!=CIRCLE_NONE){
        lost_type  = LOST_NONE;
    }
}

void ElementRun(void)
{
    if (garage_type != GARAGE_NONE) {
        RunGarage();
    }

    else if (cross_type != CROSS_NONE) {
        RunCross();
    } else if (barrier_type != BARRIER_NONE) {
        RunBarrier();
    } else if (circle_type != CIRCLE_NONE) {
        RunCircle();
    }
}


void aim_distance_select(void)
{
    if (cross_type != CROSS_NONE) {
        aim_distance = cross_aim;
    } else if (circle_type != CIRCLE_NONE) {
        aim_distance = cricle_aim;
    } else if (barrier_type != BARRIER_NONE) {
        aim_distance = barrier_aim;
    }
}


void MidLineTrack(void){
    if (cross_type == CROSS_IN) {
        if (track_type == TRACK_LEFT) {
            mid_track = mid_left; // 这是为了预先分配内存
            GetMidLine_Left(pts_far_resample_left + far_Lpt0_rpts0s_id, pts_far_resample_left_count - far_Lpt0_rpts0s_id, mid_left, (int)round(ANGLEDIST / RESAMPLEDIST), PIXPERMETER * ROADWIDTH / 2);
            mid_track_count = pts_far_resample_left_count - far_Lpt0_rpts0s_id;
        } else {
            mid_track = mid_right; // 这是为了预先分配内存
            GetMidLine_Right(pts_far_resample_right + far_Lpt1_rpts1s_id, pts_far_resample_right_count - far_Lpt1_rpts1s_id, mid_right, (int)round(ANGLEDIST / RESAMPLEDIST), PIXPERMETER * ROADWIDTH / 2);
            mid_track_count = pts_far_resample_right_count - far_Lpt1_rpts1s_id;
        }
    }else {
        if (track_type == TRACK_LEFT) {
            mid_track       = mid_left;
            mid_track_count = mid_left_count;
        } else {
            mid_track       = mid_right;
            mid_track_count = mid_right_count;
        }

        float x[100] = {0};
        float y[100] = {0};

        for (int i = 0; i < mid_track_count; i++) {
            x[i] = mid_track[i][1];
            y[i] = mid_track[i][0];
        }

        if (mid_track_count <= 5) {
            curvature = last_curvature;
        } else {
            curvature = calculate_curvature(x, y, mid_track_count);
        }
        last_curvature = curvature;
    }


    //以下为偏移角度计算

    // 车轮对应点 (纯跟踪起始点)
    float cx = InverseMapW[(int)(IMAGE_H * 0.9f)][70];
    float cy = InverseMapH[(int)(IMAGE_H * 0.9f)][70];

    int neary = (int)mid_track[0][0];
    int nearx = (int)mid_track[0][1];

    // 找最近点 (起始点中线归一化)
    float min_dist = 1e10;

    int begin_id = -1;
    for (int i = 0; i < mid_track_count; i++) {
        float dx   = mid_track[i][1] - cx;
        float dy   = mid_track[i][0] - cy;
        float dist = Q_sqrt(dx * dx + dy * dy);
        if (dist < min_dist) {
            min_dist = dist;
            begin_id = i;
        }
    }

    if (begin_id >= 0 && mid_track_count - begin_id >= 3) {
        // 归一化中线
        mid_track[begin_id][0] = cy;
        mid_track[begin_id][1] = cx;
        rptsn_num              = sizeof(rptsn) / sizeof(rptsn[0]);
        GetLinesResample(mid_track + begin_id, mid_track_count - begin_id, rptsn, &rptsn_num, RESAMPLEDIST * PIXPERMETER);


        //十字路口中的时候计算曲率
        if (cross_type == CROSS_IN) {
            float x[rptsn_num];
            float y[rptsn_num];

            for (int i = 0; i < rptsn_num; i++) {
                x[i] = rptsn[i][1];
                y[i] = rptsn[i][0];
            }
            if (rptsn_num <= 5) {
                curvature = last_curvature;

            } else {
                curvature = calculate_curvature(x, y, rptsn_num);
            }
            last_curvature = curvature;
        }

        // 远预锚点位置-
        int aim_idx       = clip(round(aim_distance / RESAMPLEDIST), 0, rptsn_num - 1);
        int aim_idx_judge = clip(round(aim_judge_far / RESAMPLEDIST), 0, mid_track_count - 1);

        // 近锚点位置
        //int aim_idx_near = clip(round(aim_distance / 2 / RESAMPLEDIST), 0, rptsn_num - 1);

        float dx1     = mid_track[3 * (mid_track_count / 4)][1] - mid_track[aim_idx_judge][1];
        float dy1     = mid_track[3 * (mid_track_count / 4)][0] - mid_track[aim_idx_judge][0];
        float dn1     = Q_sqrt(dx1 * dx1 + dy1 * dy1);
        float dx2     = mid_track[aim_idx_judge][1] - nearx;
        float dy2     = mid_track[aim_idx_judge][0] - neary;
        float dn2     = Q_sqrt(dx2 * dx2 + dy2 * dy2);
        float c1      = dx1 / dn1;
        float s1      = dy1 / dn1;
        float c2      = dx2 / dn2;
        float s2      = dy2 / dn2;
        float angle_1 = atan2f(c1 * s2 - c2 * s1, c2 * c1 + s2 * s1);

        if (angle_1 >= 0.2f || angle_1 <= -0.2f) {
            state_type = TURN_STATE;
        } else {
            state_type = STRAIGHT_STATE;
        }

        // 计算远锚点偏差值
        float dx        = rptsn[aim_idx][1] - cx;
        float dy        = cy - rptsn[aim_idx][0]; // + 0.2f * PIXPERMETER;
        float dn        = (dx * dx + dy * dy);
        //float temp_near = 0;

        switch (barrier_type) {
            case BARRIER_LEFT_BEGIN:
                // dx_near    = mid_track[aim_idx_near][1] - cx + barrier_offset;
                pure_angle = -atanf(PIXPERMETER * 2.0f * 0.2f * 0.5f * dx / dn) / PI32 * 180.0f;
                break;
            case BARRIER_RIGHT_BEGIN:
                pure_angle = -atanf(PIXPERMETER * 2.0f * 0.2f * 0.5f * dx / dn) / PI32 * 180.0f;
                break;
            default:
                // pure_angle  = -atanf(PIXPERMETER * 2.0f * 0.2f * 0.5f * dx / dn) / PI32 * 180.0f;
                if (dy > 0) {
                    pure_angle      = -atanf(dx / dy) / PI32 * 180.0f;
                    last_pure_angle = pure_angle;
                    // last_pure_angle_half = pure_angle_half;
                } else {
                    pure_angle = last_pure_angle;
                    // pure_angle_half = last_pure_angle_half;
                }
        }
        if (garage_type == GARAGE_FOUND) {
            pure_angle = 0.f;
        }
        if (cross_type == CROSS_IN) {
            pure_angle = -atanf(dx / (dy / 1.5)) / PI32 * 180.0f;
        }
    }


    //以下为大模式切换和描点切换
    if (circle_type == CIRCLE_LEFT_IN || circle_type == CIRCLE_RIGHT_IN || circle_type == CIRCLE_LEFT_BEGIN || circle_type == CIRCLE_RIGHT_BEGIN) {
        state_type = CIRCLE_STATE;
        Atimer_clear(3);
        Atimer_start(3);
    }
    if (circle_type == CIRCLE_LEFT_RUNNING || circle_type == CIRCLE_RIGHT_RUNNING || circle_type == CIRCLE_RIGHT_OUT || circle_type == CIRCLE_LEFT_OUT) {
        if (circle_flag == 1) {
            state_type = CIRCLE_STATE;
        }

        uint16 ti = Atimer_get(3);
        if (ti >= 1000) {
            Atimer_stop(3);
            Atimer_clear(3);

            circle_flag = 0;
        }
        if (circle_flag == 0) {
            state_type = CIRCLE_RUNNING_STATE;
        }
    }

    if (circle_type == CIRCLE_NONE) {
        circle_flag = 1;
    }

    if (circle_type == CIRCLE_LEFT_END || circle_type == CIRCLE_RIGHT_END) {
        state_type = STRAIGHT_STATE;
    }

    if (barrier_type == BARRIER_LEFT_BEGIN || barrier_type == BARRIER_LEFT_RUNNING || barrier_type == BARRIER_RIGHT_BEGIN || barrier_type == BARRIER_RIGHT_RUNNING) {
        state_type = BARRIER_STATE;
    }

    if (cross_type == CROSS_BEGIN || cross_type == CROSS_IN) {
        state_type = STRAIGHT_STATE;
    }

    if (state_type == STRAIGHT_STATE) {
        aim_distance = straight_aim;
    } else if (state_type == TURN_STATE) {
        if (fabs(curvature * 1000.f) >= turn_threshold) {
            aim_distance = turn_aim;
        }
        else if (fabs(curvature * 1000.f) < turn_threshold) {
            aim_distance = mid_aim;
        }
    }
    if (cross_type == CROSS_IN) {
        aim_distance = cross_aim;
    }

    if (garage_type == GARAGE_FOUND) {
        last_garage_type = GARAGE_FOUND;
    }

    if (last_garage_type == GARAGE_FOUND) {
        pingbi_num++;
        if (pingbi_num >= 300) {
            pingbi_num = 300;
        }

        if (pingbi_num >= 100) {
            if (state_type != BARRIER_STATE || garage_type != GARAGE_FOUND) {
                if ((pts_left_count <= 2) && (pts_right_count <= 2) && (GET_PIX_1C(mt9v03x_image_copy[0], BEGINH_L, IMAGE_W / 2 - BEGINW_R) <= FIX_BINTHRESHOLD) && (GET_PIX_1C(mt9v03x_image_copy[0], BEGINH_L, IMAGE_W / 2 + BEGINW_L) <= FIX_BINTHRESHOLD)) {
                    garage_type = OUT_STOP;
                }
            }
        } else {
            if (garage_type == OUT_STOP) {
                garage_type = GARAGE_FOUND;
            }
        }
    } else {
        if (state_type != BARRIER_STATE || garage_type != GARAGE_FOUND) {
            if ((pts_left_count <= 2) && (pts_right_count <= 2) && (GET_PIX_1C(mt9v03x_image_copy[0], BEGINH_L, IMAGE_W / 2 - BEGINW_R) <= FIX_BINTHRESHOLD) && (GET_PIX_1C(mt9v03x_image_copy[0], BEGINH_L, IMAGE_W / 2 + BEGINW_L) <= FIX_BINTHRESHOLD)) {
                garage_type = OUT_STOP;
            }
        }
    }

    if(lost_type == LOST_YES){
        state_type = LOST_STATE;
    }

}
