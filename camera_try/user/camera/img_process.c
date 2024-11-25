/*
 * img_process.c
 *
 *  Created on: 2024年10月7日
 *      Author: A
 */
#include "headfile.h"


void img_processing() {

    //
    int w1 = IMAGE_W / 2 - BEGINW_R, h1 = BEGINH_L;
    pts_left_count = sizeof(pts_left) / sizeof(pts_left[0]);
    for (; w1 > 0; w1--) {
        if (GET_PIX_1C(mt9v03x_image_copy[0], h1, w1 - 1) < FIX_BINTHRESHOLD)
            break;
    }

    if (GET_PIX_1C(mt9v03x_image_copy[0], h1, w1) >= FIX_BINTHRESHOLD){
        SearchLineAdaptive_Left(mt9v03x_image_copy[0], SELFADAPT_KERNELSIZE, SELFADAPT_OFFSET, h1, w1, pts_left, &pts_left_count);
    }
    else pts_left_count = 0;
    //算曲率
    int w1_curvature = IMAGE_W / 2 - BEGINW_R, h1_curvature = BEGINH_L_curvature;
    pts_left_count_curvature = sizeof(pts_left_curvature) / sizeof(pts_left_curvature[0]);
    for (; w1_curvature > 0; w1_curvature--) {
        if (GET_PIX_1C(mt9v03x_image_copy[0], h1_curvature, w1_curvature - 1) < FIX_BINTHRESHOLD)
            break;
    }

    if (GET_PIX_1C(mt9v03x_image_copy[0], h1_curvature, w1_curvature) >= FIX_BINTHRESHOLD){
        SearchLineAdaptive_Left(mt9v03x_image_copy[0], SELFADAPT_KERNELSIZE, SELFADAPT_OFFSET, h1_curvature, w1_curvature, pts_left_curvature, &pts_left_count_curvature);
    }
    else pts_left_count_curvature = 0;



    int w2 = IMAGE_W / 2 + BEGINW_L, h2 = BEGINH_R;
    pts_right_count = sizeof(pts_right) / sizeof(pts_right[0]);
    for (; w2 < IMAGE_W - 1; w2++) {
        if (GET_PIX_1C(mt9v03x_image_copy[0], h2, w2 + 1) < FIX_BINTHRESHOLD)
            break;
    }

    if (GET_PIX_1C(mt9v03x_image_copy[0], h2, w2) >= FIX_BINTHRESHOLD){
        SearchLineAdaptive_Right(mt9v03x_image_copy[0], SELFADAPT_KERNELSIZE, SELFADAPT_OFFSET, h2, w2, pts_right, &pts_right_count);
    }
    else pts_right_count = 0;
    //算曲率
    int w2_curvature = IMAGE_W / 2 + BEGINW_L, h2_curvature = BEGINH_R_curvature;
    pts_right_count_curvature = sizeof(pts_right_curvature) / sizeof(pts_right_curvature[0]);
    for (; w2_curvature < IMAGE_W - 1; w2_curvature++) {
        if (GET_PIX_1C(mt9v03x_image_copy[0], h2_curvature, w2_curvature + 1) < FIX_BINTHRESHOLD)
            break;
    }

    if (GET_PIX_1C(mt9v03x_image_copy[0], h2_curvature, w2_curvature) >= FIX_BINTHRESHOLD){
        SearchLineAdaptive_Right(mt9v03x_image_copy[0], SELFADAPT_KERNELSIZE, SELFADAPT_OFFSET, h2_curvature, w2_curvature, pts_right_curvature, &pts_right_count_curvature);
    }
    else pts_right_count_curvature = 0;

    //透视变换
    for (int i = 0; i < pts_left_count; i++) {
        pts_inv_l[i][1] = fclip(InverseMapW[pts_left[i][0]][pts_left[i][1]],0,IMAGE_W);
        pts_inv_l[i][0] = fclip(InverseMapH[pts_left[i][0]][pts_left[i][1]],0,IMAGE_H);
    }
    pts_inv_l_count = pts_left_count;

    for (int i = 0; i < pts_right_count; i++) {
        pts_inv_r[i][1] = fclip(InverseMapW[pts_right[i][0]][pts_right[i][1]],0,IMAGE_W);
        pts_inv_r[i][0] = fclip(InverseMapH[pts_right[i][0]][pts_right[i][1]],0,IMAGE_H);
    }
    pts_inv_r_count = pts_right_count;

    // 边线滤波
    GetLinesFilter(pts_inv_l, pts_inv_l_count, pts_filter_l, (int) round(FILTER_KERNELSIZE));
    pts_filter_l_count = pts_inv_l_count;
    GetLinesFilter(pts_inv_r, pts_inv_r_count, pts_filter_r, (int) round(FILTER_KERNELSIZE));
    pts_filter_r_count = pts_inv_r_count;

    // 边线等距采样
    pts_resample_left_count = sizeof(pts_resample_left) / sizeof(pts_resample_left[0]);
    GetLinesResample(pts_filter_l, pts_filter_l_count, pts_resample_left, &pts_resample_left_count, RESAMPLEDIST * PIXPERMETER);
    pts_resample_right_count = sizeof(pts_resample_right) / sizeof(pts_resample_right[0]);
    GetLinesResample(pts_filter_r, pts_filter_r_count, pts_resample_right, &pts_resample_right_count, RESAMPLEDIST * PIXPERMETER);

    int valid_points_count = 0;

    for (int i = 0; i < pts_resample_left_count; i++) {
        int x = pts_resample_left[i][1];
        int y = pts_resample_left[i][0];

        if (y < IMAGE_H-3 && x > 3 && x < IMAGE_W-3 && y>=3 ) {
            pts_resample_left[valid_points_count][0] = pts_resample_left[i][0];
            pts_resample_left[valid_points_count][1] = pts_resample_left[i][1];
            valid_points_count++;
        }
    }
    pts_resample_left_count = valid_points_count;
    valid_points_count = 0;

    for (int i = 0; i < pts_resample_right_count; i++) {
        int x = pts_resample_right[i][1];
        int y = pts_resample_right[i][0];

        if (y <= IMAGE_H-3 && x >= 3 && x <= IMAGE_W-3 && y>=3) {
            pts_resample_right[valid_points_count][0] = pts_resample_right[i][0];
            pts_resample_right[valid_points_count][1] = pts_resample_right[i][1];
            valid_points_count++;
        }
    }


    pts_resample_right_count = valid_points_count;

    // 大距离边线角度变化率
    local_angle_points(pts_resample_left, pts_resample_left_count, angle_left, (int) round(ANGLEDIST / RESAMPLEDIST));
    angle_left_num = pts_resample_left_count;
    local_angle_points(pts_resample_right, pts_resample_right_count, angle_right, (int) round(ANGLEDIST / RESAMPLEDIST));
    angle_right_num = pts_resample_right_count;

    // 小距离边线角度变化率
    local_angle_points(pts_resample_left, pts_resample_left_count, angle_left_barrier, (int) round(ANGLEDIST_barrier / RESAMPLEDIST));
    angle_left_barrier_num = pts_resample_left_count;
    local_angle_points(pts_resample_right, pts_resample_right_count, angle_right_barrier, (int) round(ANGLEDIST_barrier / RESAMPLEDIST));
    angle_right_barrier_num = pts_resample_right_count;

    // 大距离角度变化率非极大值抑制
    nms_angle(angle_left, angle_left_num, angle_new_left, (int) round(ANGLEDIST / RESAMPLEDIST) * 2 + 1);
    angle_new_left_num = angle_left_num;
    nms_angle(angle_right, angle_right_num, angle_new_right, (int) round(ANGLEDIST / RESAMPLEDIST) * 2 + 1);
    angle_new_right_num = angle_right_num;

    // 小距离角度变化率非极大值抑制
    nms_angle(angle_left_barrier, angle_left_barrier_num, angle_new_left_barrier, (int) round(ANGLEDIST_barrier / RESAMPLEDIST) * 2 + 1);
    angle_new_left_num_barrier = angle_left_barrier_num;
    nms_angle(angle_right_barrier, angle_right_barrier_num, angle_new_right_barrier, (int) round(ANGLEDIST_barrier / RESAMPLEDIST) * 2 + 1);
    angle_new_right_num_barrier = angle_right_barrier_num;

    // 左右中线跟踪
    GetMidLine_Left(pts_resample_left, pts_resample_left_count, mid_left, (int) round(ANGLEDIST / RESAMPLEDIST), PIXPERMETER_ACROSS * ROADWIDTH / 2);
    mid_left_count = pts_resample_left_count;
    GetMidLine_Right(pts_resample_right, pts_resample_right_count, mid_right, (int) round(ANGLEDIST / RESAMPLEDIST), PIXPERMETER_ACROSS * ROADWIDTH / 2);
    mid_right_count = pts_resample_right_count;

    // 左右中线跟踪(避障专属)
    GetMidLine_Left(pts_resample_left, pts_resample_left_count, mid_left_barrier, (int) round(ANGLEDIST / RESAMPLEDIST), PIXPERMETER_ACROSS_BARRIER * ROADWIDTH / 2);
    mid_left_barrier_count = pts_resample_left_count;
    GetMidLine_Right(pts_resample_right, pts_resample_right_count, mid_right_barrier, (int) round(ANGLEDIST / RESAMPLEDIST), PIXPERMETER_ACROSS_BARRIER * ROADWIDTH / 2);
    mid_right_barrier_count = pts_resample_right_count;


}



