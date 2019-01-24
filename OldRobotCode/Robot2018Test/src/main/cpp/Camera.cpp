/*
 * File:		Camera.cpp
 * Author:		Programming Subteam
 * Team:		Hawktimus Prime - 3229
 *
 * File Description:
 * Controls the camera on the driver station.
 */

#include "Camera.h"
using namespace frc;

Camera::Camera()
{
	//Make resolution low to reduce bandwidth and rio cpu %
	//1st camera settings
	//cs::AxisCamera camera = CameraServer::GetInstance()->AddAxisCamera("axis-camera.local");
	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
	camera.SetResolution(160, 120);
	camera.SetFPS(FPS);
	camera.SetWhiteBalanceAuto();
	camera.SetExposureAuto();
	camera.SetBrightness(BRIGHTNESS);

	//2nd camera here
	//cs::AxisCamera camera2 = CameraServer::GetInstance()->AddAxisCamera("axis-camera.local");
	cs::UsbCamera camera2 = CameraServer::GetInstance()->StartAutomaticCapture();
	camera2.SetResolution(160, 120);
	camera2.SetFPS(FPS);
	camera2.SetWhiteBalanceAuto();
	camera2.SetExposureAuto();
	camera2.SetBrightness(BRIGHTNESS);

	CameraServer::GetInstance()->StartAutomaticCapture(0);
	CameraServer::GetInstance()->StartAutomaticCapture(1);
}
