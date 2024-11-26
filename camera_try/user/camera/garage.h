/*
 * garage.h
 *
 *  Created on: 2024��10��12��
 *      Author: A
 */

#ifndef USER_CAMERA_GARAGE_H_
#define USER_CAMERA_GARAGE_H_

enum garage_type_e {
  GARAGE_NONE, // �ǳ���ģʽ
  GARAGE_FOUND,
  OUT_STOP,
};
extern enum garage_type_e garage_type;

float calculate_vector_angle(float x1, float y1, float x2, float y2);
void CheckGarage(void);
void RunGarage(void);



#endif /* USER_CAMERA_GARAGE_H_ */
