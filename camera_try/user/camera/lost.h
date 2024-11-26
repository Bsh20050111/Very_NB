/*
 * lost.h
 *
 *  Created on: 2024年11月25日
 *      Author: A
 */

#ifndef USER_CAMERA_LOST_H_
#define USER_CAMERA_LOST_H_

enum lost_type_e {
  LOST_NONE,  //未丢线
  LOST_YES,   //丢线
};
extern enum lost_type_e lost_type;

void CheckLost(void);

#endif /* USER_CAMERA_LOST_H_ */
