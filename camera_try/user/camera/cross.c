/*
 * cross.c
 *
 *  Created on: 2024年10月12日
 *      Author: A
 */

#include "headfile.h"

enum cross_type_e cross_type = CROSS_NONE;
bool far_Lpt0_found, far_Lpt1_found;
int32_t Both_Boder_None_Cross;
int far_Lpt0_rpts0s_id, far_Lpt1_rpts1s_id;
int cross_easy   = 0;
float cross_open = 1;

void CheckCross()
{
    if (circle_type != CIRCLE_LEFT_OUT || circle_type != CIRCLE_RIGHT_OUT || circle_type != CIRCLE_LEFT_IN || circle_type != CIRCLE_RIGHT_IN) {
        bool Xfound = Lpt0_found && Lpt1_found;
        if ((int)cross_open == 0) {
            if (cross_type == CROSS_NONE && Xfound) {
                cross_type = CROSS_BEGIN;
            }
        }
        if ((int)cross_open == 1) {
            if (cross_type == CROSS_NONE && Xfound && cross_easy == 0) {
                cross_type = CROSS_BEGIN;
            }
            if (cross_type == CROSS_NONE && cross_easy == 1 && (((Lpt0_found || Lpt1_found) && (pts_resample_left_count <= 3 || pts_resample_right_count <= 3)) || Xfound)) {
                cross_type = CROSS_BEGIN;
            }
        }
    }
}

void RunCross()
{
    bool Xfound = Lpt0_found && Lpt1_found;
    // 检测到十字，先按照近线走
    if (cross_easy == 0) {
        if (cross_type == CROSS_BEGIN) {
            if (Lpt0_found) {
                mid_left_count = pts_resample_left_count = Lpt0_rpts0s_id;
                track_type                               = TRACK_LEFT;
            } else if (Lpt1_found) {
                mid_right_count = pts_resample_right_count = Lpt1_rpts1s_id;
                track_type                                 = TRACK_RIGHT;
            }

            // 近角点过少，进入远线控制
            if ((Xfound && (Lpt0_rpts0s_id < 0.2 / RESAMPLEDIST && Lpt1_rpts1s_id < 0.2 / RESAMPLEDIST)) || (pts_resample_left_count < 20 && pts_resample_right_count < 20)) {
                cross_type = CROSS_IN;
            }
        }
        // 远线控制进十字,begin_y渐变靠近防丢线
        if (cross_type == CROSS_IN) {
            // 寻远线,算法与近线相同
            cross_farline();

            if (pts_resample_left_count < 5 && pts_resample_right_count < 5) {
                Both_Boder_None_Cross++;
            }
            if (Both_Boder_None_Cross > 2 && pts_resample_left_count > 20 && pts_resample_right_count > 20) {
                cross_type            = CROSS_NONE;
                Both_Boder_None_Cross = 0;
                cross_easy            = 1;
            }
            if (far_Lpt1_found) {
                track_type = TRACK_RIGHT;
            } else if (far_Lpt0_found) {
                track_type = TRACK_LEFT;
            } else if (Both_Boder_None_Cross > 0 && pts_resample_right_count < 5) {
                track_type = TRACK_RIGHT;
            } else if (Both_Boder_None_Cross > 0 && pts_resample_left_count < 5) {
                track_type = TRACK_LEFT;
            }
        }
    }

    if (cross_easy == 1) {
        if (cross_type == CROSS_BEGIN) {
            if (Lpt0_found) {
                mid_left_count = pts_resample_left_count = Lpt0_rpts0s_id;
                track_type                               = TRACK_LEFT;
            } else if (Lpt1_found) {
                mid_right_count = pts_resample_right_count = Lpt1_rpts1s_id;
                track_type                                 = TRACK_RIGHT;
            }

            // 近角点过少，进入远线控制
            if ((Xfound && (Lpt0_rpts0s_id < 0.2 / RESAMPLEDIST && Lpt1_rpts1s_id < 0.2 / RESAMPLEDIST)) || (pts_resample_left_count < 20 && pts_resample_right_count < 20)) {
                cross_type = CROSS_IN;
            }
        }
        // 远线控制进十字,begin_y渐变靠近防丢线
        if (cross_type == CROSS_IN) {
            // 寻远线,算法与近线相同
            cross_farline();

            if (pts_resample_left_count < 5 && pts_resample_right_count < 5) {
                Both_Boder_None_Cross++;
            }
            if (Both_Boder_None_Cross > 2 && pts_resample_left_count > 20 && pts_resample_right_count > 20) {
                cross_type            = CROSS_NONE;
                Both_Boder_None_Cross = 0;
                cross_easy            = 0;
            }
            if (far_Lpt1_found) {
                track_type = TRACK_RIGHT;
            } else if (far_Lpt0_found) {
                track_type = TRACK_LEFT;
            } else if (Both_Boder_None_Cross > 0 && pts_resample_right_count < 5) {
                track_type = TRACK_RIGHT;
            } else if (Both_Boder_None_Cross > 0 && pts_resample_left_count < 5) {
                track_type = TRACK_LEFT;
            }
        }
    }
}

void cross_farline()
{
    int cross_width = 4;
    int far_y1 = 0, far_y2 = 0;
    int far_x1 = 0, far_x2 = 0;
    bool white_found   = false;
    pts_far_left_count = sizeof(pts_far_left) / sizeof(pts_far_left[0]);

    int w1 = IMAGE_W / 2 - BEGINW_R, h1 = BEGINH_L;
    for (; w1 > cross_width * 2; w1--) {
        if (GET_PIX_1C(mt9v03x_image_copy[0], h1, w1 - 1) < FIX_BINTHRESHOLD) {
            far_x1 = w1 - cross_width;
            break;
        }
    }
    /*如果一行全为白色没写*/
    if (far_x1 <= 4) {
        far_x1 = 4;
    }

    for (; h1 > 0; h1--) {
        // 先黑后白，先找white
        if (GET_PIX_1C(mt9v03x_image_copy[0], h1, far_x1) >= FIX_BINTHRESHOLD) { white_found = true; }
        if (GET_PIX_1C(mt9v03x_image_copy[0], h1 - 1, far_x1) < FIX_BINTHRESHOLD && white_found) {
            far_y1 = h1;
            break;
        }
    }
    if (GET_PIX_1C(mt9v03x_image_copy[0], far_y1, far_x1) >= FIX_BINTHRESHOLD) {
        SearchLineAdaptive_Left(mt9v03x_image_copy[0], SELFADAPT_KERNELSIZE, SELFADAPT_OFFSET, far_y1, far_x1, pts_far_left, &pts_far_left_count);
    } else
        pts_far_left_count = 0;

    int w2 = IMAGE_W / 2 + BEGINW_L, h2 = BEGINH_R;
    white_found         = false;
    pts_far_right_count = sizeof(pts_far_right) / sizeof(pts_far_right[0]);
    for (; w2 < IMAGE_W - cross_width * 2; w2++) {
        if (GET_PIX_1C(mt9v03x_image_copy[0], h2, w2 + 1) < FIX_BINTHRESHOLD) {
            far_x2 = w2 + cross_width;
            break;
        }
    }
    /*如果一行全为白色没写*/
    if (far_x2 >= 136) {
        far_x2 = 136;
    }

    for (; h2 > 0; h2--) {
        // 先黑后白，先找white
        if (GET_PIX_1C(mt9v03x_image_copy[0], h2, far_x2) >= FIX_BINTHRESHOLD) { white_found = true; }
        if (GET_PIX_1C(mt9v03x_image_copy[0], h2 - 1, far_x2) < FIX_BINTHRESHOLD && white_found) {
            far_y2 = h2;
            break;
        }
    }
    if (GET_PIX_1C(mt9v03x_image_copy[0], far_y2, far_x2) >= FIX_BINTHRESHOLD) {
        SearchLineAdaptive_Right(mt9v03x_image_copy[0], SELFADAPT_KERNELSIZE, SELFADAPT_OFFSET, far_y2, far_x2, pts_far_right, &pts_far_right_count);
    } else
        pts_far_right_count = 0;

    // 透视变换
    for (int i = 0; i < pts_far_left_count; i++) {
        pts_far_inv_l[i][1] = fclip(InverseMapW[pts_far_left[i][0]][pts_far_left[i][1]], 0, IMAGE_W);
        pts_far_inv_l[i][0] = fclip(InverseMapH[pts_far_left[i][0]][pts_far_left[i][1]], 0, IMAGE_H);
    }
    pts_far_inv_l_count = pts_far_left_count;

    for (int i = 0; i < pts_far_right_count; i++) {
        pts_far_inv_r[i][1] = fclip(InverseMapW[pts_far_right[i][0]][pts_far_right[i][1]], 0, IMAGE_W);
        pts_far_inv_r[i][0] = fclip(InverseMapH[pts_far_right[i][0]][pts_far_right[i][1]], 0, IMAGE_H);
    }
    pts_far_inv_r_count = pts_far_right_count;

    // 边线滤波
    GetLinesFilter(pts_far_inv_l, pts_far_inv_l_count, pts_far_filter_l, (int)round(FILTER_KERNELSIZE));
    pts_far_filter_l_count = pts_far_inv_l_count;
    GetLinesFilter(pts_far_inv_r, pts_far_inv_r_count, pts_far_filter_r, (int)round(FILTER_KERNELSIZE));
    pts_far_filter_r_count = pts_far_inv_r_count;

    // 边线等距采样
    pts_far_resample_left_count = sizeof(pts_far_resample_left) / sizeof(pts_far_resample_left[0]);
    GetLinesResample(pts_far_filter_l, pts_far_filter_l_count, pts_far_resample_left, &pts_far_resample_left_count, RESAMPLEDIST * PIXPERMETER);
    pts_far_resample_right_count = sizeof(pts_far_resample_right) / sizeof(pts_far_resample_right[0]);
    GetLinesResample(pts_far_filter_r, pts_far_filter_r_count, pts_far_resample_right, &pts_far_resample_right_count, RESAMPLEDIST * PIXPERMETER);

    int valid_far_points_count = 0;

    for (int i = 0; i < pts_far_resample_left_count; i++) {
        int x = pts_far_resample_left[i][1];
        int y = pts_far_resample_left[i][0];

        if (y < IMAGE_H - 3 && x > 3 && x < IMAGE_W - 3 && y >= 3) {
            pts_far_resample_left[valid_far_points_count][0] = pts_far_resample_left[i][0];
            pts_far_resample_left[valid_far_points_count][1] = pts_far_resample_left[i][1];
            valid_far_points_count++;
        }
    }
    pts_far_resample_left_count = valid_far_points_count;

    valid_far_points_count = 0;

    for (int i = 0; i < pts_far_resample_right_count; i++) {
        int x = pts_far_resample_right[i][1];
        int y = pts_far_resample_right[i][0];

        if (y <= IMAGE_H - 3 && x >= 3 && x <= IMAGE_W - 3 && y >= 3) {
            pts_far_resample_right[valid_far_points_count][0] = pts_far_resample_right[i][0];
            pts_far_resample_right[valid_far_points_count][1] = pts_far_resample_right[i][1];
            valid_far_points_count++;
        }
    }

    pts_far_resample_right_count = valid_far_points_count;

    // 边线角度变化率
    local_angle_points(pts_far_resample_left, pts_far_resample_left_count, far_angle_left, (int)round(ANGLEDIST / RESAMPLEDIST));
    far_angle_left_num = pts_far_resample_left_count;
    local_angle_points(pts_far_resample_right, pts_far_resample_right_count, far_angle_right, (int)round(ANGLEDIST / RESAMPLEDIST));
    far_angle_right_num = pts_far_resample_right_count;

    // 角度变化率非极大值抑制
    nms_angle(far_angle_left, far_angle_left_num, far_angle_new_left, (int)round(ANGLEDIST / RESAMPLEDIST) * 2 + 1);
    far_angle_new_left_num = far_angle_left_num;
    nms_angle(far_angle_right, far_angle_right_num, far_angle_new_right, (int)round(ANGLEDIST / RESAMPLEDIST) * 2 + 1);
    far_angle_new_right_num = far_angle_right_num;

    // 找远线上的L角点
    far_Lpt0_found = far_Lpt1_found = false;
    // is_far_straight0 = pts_far_resample_left_count > 1.0 / RESAMPLEDIST;
    // is_far_straight1 = pts_far_resample_right_count > 1.0 / RESAMPLEDIST;
    for (int i = 0; i < pts_far_resample_left_count; i++) {
        if (far_angle_new_left[i] == 0) continue;
        int im1    = clip(i - (int)round(ANGLEDIST / RESAMPLEDIST), 0, pts_far_resample_left_count - 1);
        int ip1    = clip(i + (int)round(ANGLEDIST / RESAMPLEDIST), 0, pts_far_resample_left_count - 1);
        float conf = fabs(far_angle_left[i]) - (fabs(far_angle_left[im1]) + fabs(far_angle_left[ip1])) / 2;

        // L角点阈值
        if (far_Lpt0_found == false && (66. / 180. * PI32) < conf && conf < (140. / 180. * PI32) && i < 0.7 / RESAMPLEDIST) {
            far_Lpt0_rpts0s_id = i;
            far_Lpt0_found     = true;
        }
    }

    for (int i = 0; i < pts_far_resample_right_count; i++) {
        if (far_angle_new_right[i] == 0) continue;
        int im1    = clip(i - (int)round(ANGLEDIST / RESAMPLEDIST), 0, pts_far_resample_right_count - 1);
        int ip1    = clip(i + (int)round(ANGLEDIST / RESAMPLEDIST), 0, pts_far_resample_right_count - 1);
        float conf = fabs(far_angle_right[i]) - (fabs(far_angle_right[im1]) + fabs(far_angle_right[ip1])) / 2;

        if (far_Lpt1_found == false && (66. / 180. * PI32) < conf && conf < 140. / 180. * PI32 && i < 0.7 / RESAMPLEDIST) {
            far_Lpt1_rpts1s_id = i;
            far_Lpt1_found     = true;
        }
    }
}
