// Author: Team 3229 Programming Subteam

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

	CameraServer::GetInstance()->StartAutomaticCapture(0);
}