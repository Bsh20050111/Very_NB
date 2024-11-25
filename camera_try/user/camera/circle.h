/*
 * circle.h
 *
 *  Created on: 2024��10��12��
 *      Author: A
 */

#ifndef USER_CAMERA_CIRCLE_H_
#define USER_CAMERA_CIRCLE_H_

enum circle_type_e {
  CIRCLE_NONE, // ��Բ��ģʽ
  CIRCLE_LEFT_BEGIN,
  CIRCLE_RIGHT_BEGIN, // Բ����ʼ��ʶ�𵽵���L�ǵ���һ�೤ֱ����
  CIRCLE_LEFT_IN,
  CIRCLE_RIGHT_IN, // Բ�����룬���ߵ�һ��ֱ����һ��Բ����λ�á�
  CIRCLE_LEFT_RUNNING,
  CIRCLE_RIGHT_RUNNING, // Բ���ڲ���
  CIRCLE_LEFT_OUT,
  CIRCLE_RIGHT_OUT, // ׼����Բ������ʶ�𵽳�������L�ǵ㡣
  CIRCLE_LEFT_END,
  CIRCLE_RIGHT_END // Բ�����������ٴ��ߵ�����ֱ����λ�á�
};

extern enum circle_type_e circle_type;

void CheckCircle(void);
void RunCircle(void);


#endif /* USER_CAMERA_CIRCLE_H_ */
