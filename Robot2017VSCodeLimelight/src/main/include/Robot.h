/*
 * File:			Robot.h
 * Author:			Neil Anderson
 * Version:			1.0
 * Last Modified:	01/16/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * This file defines all necessary macro constants for the Robot.cpp file as well as includes all necessary external libraries.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

//Standard library includes
#include <iostream>
#include <string>

//Includes from the frc namespace
#include <IterativeRobot.h>
#include <XboxController.h>
#include <Spark.h>
#include <LiveWindow/LiveWindow.h>
#include <Timer.h> //For wait function
#include "WPILib.h"

//Includes from programmer-defined files.
#include "Climber.h"
#include "ArcadeDrive.h"
#include "Autonomous.h"
#include "Limelight.h"

#define XBOX_USB_PORT 0 //Defines the port for the XBox controller
#define DEAD_BAND 0.1 //Sets the dead band for the XBox controller.

#endif /* SRC_ROBOT_H_ */
