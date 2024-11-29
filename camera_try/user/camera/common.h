/*
 * common.h
 *
 *  Created on: 2024��10��7��
 *      Author: A
 */

#ifndef USER_CAMERA_COMMON_H_
#define USER_CAMERA_COMMON_H_

#define IMAGE_H               (MT9V03X_H)
#define IMAGE_W               (MT9V03X_W-2)//��ȥ2����Ϊ������ͷ���ұߴ��ںڱߵ���Ѳ�߳�����
#define BEGINH_L              (85)
#define BEGINH_L_curvature    (88)
#define BEGINH_R              (85)
#define BEGINH_R_curvature    (88)
#define BEGINW_L              (-8)
#define BEGINW_R              (-8)
#define PT_MAXLEN             (95)
#define GET_PIX_1C(IMG, H, W) (IMG[(H) * MT9V03X_W + (W)]) // ��ȡ���ص��ֵ
#define SELFADAPT_KERNELSIZE  (7)                          // Ѳ������˴�С
#define FILTER_KERNELSIZE     (7)                          // �˲��˴�С
#define SELFADAPT_OFFSET      (8)                          // ��Ӧ�Կ��С
#define PIXPERMETER           (48.0f)                      //͸�ӱ仯���ͼ��1m��Ӧ������ֵ
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
