// Author: Team 3229 Programming Subteam

#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <memory>
#include <string>

//frc includes
#include <frc/GenericHID.h>
#include "frc/WPILib.h"
#include <cameraserver/CameraServer.h>
#include <cscore_oo.h>
#include "frc/smartdashboard/Smartdashboard.h"

class Camera
{
public:
	Camera();

private:
	cs::VideoSource camera;

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

#endif // CAMERA_H