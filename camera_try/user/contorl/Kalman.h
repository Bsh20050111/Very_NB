/*
 * Kalman.h
 *
 *  Created on: 2024Äê11ÔÂ24ÈÕ
 *      Author: lenovo
 */

#ifndef CODE_KALMAN_H_
#define CODE_KALMAN_H_

void kalman_init(KalmanFilter *kf, float initial_estimate, float initial_error, float process_noise, float measurement_noise);
void kalman_update(KalmanFilter *kf, float measurement);


#endif /* CODE_KALMAN_H_ */
