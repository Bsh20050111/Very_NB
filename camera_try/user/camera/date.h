/*
 * date.h
 *
 *  Created on: 2024年10月6日
 *      Author: A
 */

#ifndef USER_CAMERA_DATE_H_
#define USER_CAMERA_DATE_H_

#include "headfile.h"

typedef enum track_type_e {
    TRACK_LEFT = 0,
    TRACK_RIGHT,
} track_type_e;

extern uint8_t (*Img_Gray)[MT9V03X_W];
//未逆透视前边线数组
extern int32_t pts_left[PT_MAXLEN][2];
extern int32_t pts_right[PT_MAXLEN][2];
extern int32_t pts_left_count;
extern int32_t pts_right_count;
extern int32_t pts_left_curvature[PT_MAXLEN][2];
extern int32_t pts_right_curvature[PT_MAXLEN][2];
extern int32_t pts_left_count_curvature;
extern int32_t pts_right_count_curvature;
extern int32_t pts_far_left[PT_MAXLEN][2];
extern int32_t pts_far_right[PT_MAXLEN][2];
extern int32_t pts_far_left_count;
extern int32_t pts_far_right_count;
extern int32_t mid_s_count;
//逆透视后边线数组
extern float pts_inv_l[PT_MAXLEN][2];
extern float pts_inv_r[PT_MAXLEN][2];
extern int32_t pts_inv_l_count;
extern int32_t pts_inv_r_count;
extern float pts_far_inv_l[PT_MAXLEN][2];
extern float pts_far_inv_r[PT_MAXLEN][2];
extern int32_t pts_far_inv_l_count;
extern int32_t pts_far_inv_r_count;
//滤波后边线数组
extern float pts_filter_l[PT_MAXLEN][2];
extern float pts_filter_r[PT_MAXLEN][2];
extern int32_t pts_filter_l_count;
extern int32_t pts_filter_r_count;
extern float pts_far_filter_l[PT_MAXLEN][2];
extern float pts_far_filter_r[PT_MAXLEN][2];
extern int32_t pts_far_filter_l_count;
extern int32_t pts_far_filter_r_count;

//重采样后边线数组
extern float pts_resample_left[PT_MAXLEN][2];
extern float pts_resample_right[PT_MAXLEN][2];
extern int32_t pts_resample_left_count;
extern int32_t pts_resample_right_count;
extern float pts_far_resample_left[PT_MAXLEN][2];
extern float pts_far_resample_right[PT_MAXLEN][2];
extern int32_t pts_far_resample_left_count;
extern int32_t pts_far_resample_right_count;

extern float mid_left[PT_MAXLEN][2];
extern float mid_right[PT_MAXLEN][2];
extern float mid_s[PT_MAXLEN][2];
extern float mid_left_barrier[PT_MAXLEN][2];
extern float mid_right_barrier[PT_MAXLEN][2];

extern int32_t mid_left_count;
extern int32_t mid_right_count;
extern int32_t mid_left_barrier_count;
extern int32_t mid_right_barrier_count;


extern float angle_new_left[PT_MAXLEN];
extern float angle_new_right[PT_MAXLEN];
extern float angle_new_left_barrier[PT_MAXLEN];
extern float angle_new_right_barrier[PT_MAXLEN];
extern int angle_new_left_num;
extern int angle_new_right_num;
extern int angle_new_left_num_barrier;
extern int angle_new_right_num_barrier;
extern float far_angle_new_left[PT_MAXLEN];
extern float far_angle_new_right[PT_MAXLEN];
extern int far_angle_new_left_num;
extern int far_angle_new_right_num;

extern uint8_t mt9v03x_image_copy[MT9V03X_H][MT9V03X_W];

extern float angle_left[PT_MAXLEN];
extern float angle_right[PT_MAXLEN];
extern float angle_left_barrier[PT_MAXLEN];
extern float angle_right_barrier[PT_MAXLEN];
extern int angle_left_num;
extern int angle_right_num;
extern int angle_left_barrier_num;
extern int angle_right_barrier_num;
extern float far_angle_left[PT_MAXLEN];
extern float far_angle_right[PT_MAXLEN];
extern int far_angle_left_num;
extern int far_angle_right_num;

extern int Lpt0_rpts0s_id;
extern int Lpt1_rpts1s_id;
extern bool Lpt0_found;
extern bool Lpt1_found;
extern int Lpt1[2];
extern int Lpt0[2];
extern int far_Lpt1[2];
extern int far_Lpt0[2];

extern int Lpt_in0_rpts0s_id;
extern int Lpt_in1_rpts1s_id;
extern int Lpt0_rpts0s_id_barrier;
extern int Lpt1_rpts1s_id_barrier;
extern bool Lpt_in0_found;
extern bool Lpt_in1_found;
extern bool Lpt0_found_barrier;
extern bool Lpt1_found_barrier;
extern int Lpt_in1[2];
extern int Lpt_in0[2];

extern bool is_straight0;
extern bool is_straight1;
extern bool is_far_straight0;
extern bool is_far_straight1;
extern bool Lpt0_found_barrier_in;
extern bool Lpt1_found_barrier_in;
extern int Lpt0_found_barrier_in_id;
extern int Lpt1_found_barrier_in_id;
extern int32_t Lpt0_found_count;
extern int32_t Lpt1_found_count;

extern bool is_turn0_l;
extern bool is_turn1_l;
extern bool is_turn0_r;
extern bool is_turn1_r;

extern float rptsn[PT_MAXLEN][2];
extern int32_t rptsn_num;
extern float aim_distance;
extern float aim_judge_far;

extern track_type_e track_type;
extern float FIX_BINTHRESHOLD;
extern int begin_flag;


#endif /* USER_CAMERA_DATE_H_ */
