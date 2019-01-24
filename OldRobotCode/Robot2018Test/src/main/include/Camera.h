/*
 * File:		Camera.h
 * Author:		Programming Subteam
 * Team:		Hawktimus Prime - 3229
 *
 * File Description:
 * Header file for Camera.cpp
 */

#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

#include <iostream>
#include <memory>
#include <string>

//frc includes
#include <GenericHID.h>
#include <math.h>
#include <Servo.h>
#include <CameraServer.h>
#include <cscore_oo.h>

class Camera
{
public:
	Camera();

private:
	cs::VideoSource camera;
	cs::VideoSource camera2;

	// Constants for Camera Settings
	const int FPS = 10;
	const int BRIGHTNESS = 40;

	// Constants for Pan/Tilt Servos
	const int PAN_SERVO_PWM = 3;
	const int TILT_SERVO_PWM = 4;
	const float INITIAL_PAN = 0.2;
	const float INITIAL_TILT = 0.5;
	const float PANTILT_RATE = 0.05;

};

#endif /* SRC_CAMERA_H_ */
