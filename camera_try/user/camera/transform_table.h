/*
 * transform_table.h
 *
 *  Created on: 2024Äê10ÔÂ7ÈÕ
 *      Author: A
 */

#ifndef USER_CAMERA_TRANSFORM_TABLE_H_
#define USER_CAMERA_TRANSFORM_TABLE_H_

extern  const float InverseMapH[90][140] ;
extern  const float InverseMapW[90][140] ;
void transform(float X, float Y, int* x, int* y);



#endif /* USER_CAMERA_TRANSFORM_TABLE_H_ */
