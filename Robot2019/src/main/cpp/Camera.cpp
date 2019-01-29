// Author: Team 3229 Programming Subteam

#include "Camera.h"

using namespace frc;

Camera::Camera()
{
	//Make resolution low to reduce bandwidth and rio cpu %
	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
	camera.SetResolution(640, 480); // length x height
	camera.SetFPS(FPS);
	camera.SetWhiteBalanceAuto();
	camera.SetExposureAuto();
	camera.SetBrightness(BRIGHTNESS);

	CameraServer::GetInstance()->StartAutomaticCapture(0);
}