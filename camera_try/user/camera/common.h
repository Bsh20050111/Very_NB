/*
 * common.h
 *
 *  Created on: 2024年10月7日
 *      Author: A
 */

#ifndef USER_CAMERA_COMMON_H_
#define USER_CAMERA_COMMON_H_

#define IMAGE_H               (MT9V03X_H)
#define IMAGE_W               (MT9V03X_W-2)//减去2是因为该摄像头最右边存在黑边导致巡线出问题
#define BEGINH_L              (85)
#define BEGINH_L_curvature    (88)
#define BEGINH_R              (85)
#define BEGINH_R_curvature    (88)
#define BEGINW_L              (-8)
#define BEGINW_R              (-8)
#define PT_MAXLEN             (95)
#define GET_PIX_1C(IMG, H, W) (IMG[(H) * MT9V03X_W + (W)]) // 获取像素点的值
#define SELFADAPT_KERNELSIZE  (7)                          // 巡线区域核大小
#define FILTER_KERNELSIZE     (7)                          // 滤波核大小
#define SELFADAPT_OFFSET      (8)                          // 适应性块大小
#define PIXPERMETER           (48.0f)                      //透视变化后的图像1m对应的像素值
#define PIXPERMETER_ACROSS    (50.0f)
#define PIXPERMETER_ACROSS_BARRIER    (10.0f)
#define RESAMPLEDIST          (0.02f)
#define ANGLEDIST             (0.1f)
#define ANGLEDIST_barrier     (0.06f)
#define ROADWIDTH             (0.40f)
#define FRAMENONE             (1)
#define FRAMETOLEFT           (5)
#define FRAMETORIGHT          (5)
#define PIXEL_PER_METER       (100)

#define PI32                  (3.1415926535898f)

int32_t limit(int32_t x, int32_t low, int32_t up);
int clip(int x, int low, int up);
float fclip(float x, float low, float up);
float Q_sqrt(float number);



#endif /* USER_CAMERA_COMMON_H_ */
