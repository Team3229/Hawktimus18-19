/*
 * File:			Robot.h
 * Author:			Hayden Mann
 * Last Modified:	02/02/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * This file contains the necessary includes that are needed to execute the code written in Robot.cpp.  It does NOT define the class itself.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

//Standard library includes
#include <iostream>
#include <string>

//Includes from the frc namespace
#include <IterativeRobot.h>
#include <XboxController.h>
#include <Timer.h> //For wait function
#include <AnalogInput.h>
#include <ADXRS450_Gyro.h>

//Includes from programmer-defined files.
#include "Climber.h"
#include "Autonomous.h"
#include "Camera.h"
#include "CubeDelivery.h"
#include "DriveSystem.h"

#endif /* SRC_ROBOT_H_ */
