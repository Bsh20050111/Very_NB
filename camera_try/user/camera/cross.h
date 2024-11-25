/*
 * cross.h
 *
 *  Created on: 2024��10��12��
 *      Author: A
 */

#ifndef USER_CAMERA_CROSS_H_
#define USER_CAMERA_CROSS_H_

enum cross_type_e {
  CROSS_NONE,  // ��ʮ��ģʽ
  CROSS_BEGIN, // �ҵ���������L�ǵ�
  CROSS_IN, // ����L�ǵ�ܽ���������ʮ���ڲ�(��ʱ�л�Զ�߿���)
};

extern enum cross_type_e cross_type;
extern int32_t Both_Boder_None_Cross;
extern int far_Lpt0_rpts0s_id, far_Lpt1_rpts1s_id;
extern float cross_open;

void CheckCross(void);
void RunCross(void);
void cross_farline(void);

#endif /* USER_CAMERA_CROSS_H_ */
