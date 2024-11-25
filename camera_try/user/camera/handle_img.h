/*
 * handle_img.h
 *
 *  Created on: 2024Äê10ÔÂ7ÈÕ
 *      Author: A
 */

#ifndef USER_CAMERA_HANDLE_IMG_H_
#define USER_CAMERA_HANDLE_IMG_H_

void GetImgBin_Average(uint8_t img_gray[], float *threshold);
void SearchLineAdaptive_Left(uint8_t img_gray[], int32_t block_size, int32_t down_value, int32_t h, int32_t w, int32_t pts[][2], int32_t* line_num);
void SearchLineAdaptive_Right(uint8_t img_gray[], int32_t block_size, int32_t down_value, int32_t h, int32_t w, int32_t pts[][2], int32_t* line_num);
void GetLinesFilter(float pts_in[][2], int32_t pts_in_count, float pts_out[][2], int32_t kernelsize);
void GetLinesResample(float pts_in[][2], int32_t num1, float pts_out[][2], int32_t* num2, float dist);
void local_angle_points(float pts_in[][2], int num, float angle_out[], int dist);
void nms_angle(float angle_in[], int num, float angle_out[], int kernel);
void GetMidLine_Left(float pts_left[][2], int32_t pts_left_count, float mid_left[][2], int32_t approx_num, float dist);
void GetMidLine_Right(float pts_right[][2], int32_t pts_right_count, float mid_right[][2], int32_t approx_num, float dist);
int is_curve(float angle[], int n, float threshold) ;



#endif /* USER_CAMERA_HANDLE_IMG_H_ */
