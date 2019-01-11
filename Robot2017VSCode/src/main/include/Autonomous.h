/*
 * File:			Autonomous.h
 * Author:			Neil Anderson
 * Version:			1.0
 * Last Modified:	01/16/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * This file defines all necessary methods prototype for the autonomous class, which drives the robot in autonomous mode.
 * */

#ifndef SRC_AUTONOMOUS_H_
#define SRC_AUTONOMOUS_H_

//Standard library includes
#include <iostream>
#include <memory>
#include <string>

//FRC library includes
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Time.h>

//Includes from programmer defined classes.
#include <ArcadeDrive.h>

//Constants for Autonomous
#define CENTER_TIMER 4.0
#define MOVEMENT1_TIMER 1.3
#define LEFT_TURN 30
#define RIGHT_TURN -30
#define MOVEMENT3_TIMER 3.25

//Class "outline" and method prototypes
class Autonomous
{
public:
	Autonomous();
	void AutoSelectInit();
	void DoAutonomousInit();
	void DoAutonomousPeriodic(ArcadeDrive * chasis);
};

#endif /* SRC_AUTONOMOUS_H_ */
