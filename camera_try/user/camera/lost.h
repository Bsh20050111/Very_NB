/*
 * lost.h
 *
 *  Created on: 2024��11��25��
 *      Author: A
 */

#ifndef USER_CAMERA_LOST_H_
#define USER_CAMERA_LOST_H_

enum lost_type_e {
  LOST_NONE,  //δ����
  LOST_YES,   //����
};
extern enum lost_type_e lost_type;

void CheckLost(void);

#endif /* USER_CAMERA_LOST_H_ */
