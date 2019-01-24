/*
 * File:		Autonomous.h
 * Author:		Programming Subteam
 * Team:		Hawktimus Prime - 3229
 *
 * File Description:
 * Defines the class for autonomous mode that will be instantiated to drive the robot without a human interface.
 */

#ifndef SRC_AUTONOMOUS_H
#define SRC_AUTONOMOUS_H

//Standard Includes
#include <iostream>
#include <string>

//FRC-Defined includes
#include <Timer.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <AnalogInput.h>

//Programmer-Defined Includes
#include "DriveSystem.h"
#include "CubeDelivery.h"

class Autonomous
{
private:

	DriveSystem * driveTrain;
	CubeDelivery * gettinPoints;
	frc::Timer autoTimer{};

	double timeLimit = 0.0;
	double speedChange = 0.0;
	char switchColor; //Color of the switch
	char scaleColor; //color of scale

	//Constants
	const static int POSITION_SIZE = 3;
	const static int TARGET_SIZE = 6;
	const static int MOVEMENT_SIZE = 10;
	const bool FORWARD = true;
	const bool REVERSE = false;
	const float PUSH_TIME = 0.5; //Time to push the cube

	const float DRIVE_FT_SEC = 9.1; //Noraml speed feet/second //Old:5.5
	const float LIFT_FT_SEC = 1.51;
	const float TURN_TIMEOUT = 2.5;

	//Changing powers NOT ACTUAL VALUES
	const float LOW_POWER = 0.0;
	const float NORMAL_POWER = 1.0;
	const float HIGH_POWER = 2.0;

	//Constants for initial lift
	const float START_LIFT_DISTANCE = 1.0;

	//Choosing bois
	frc::SendableChooser<int> * positionChooser; //Receiving from the smart dashboard
	frc::SendableChooser<int> * targetChooser;
	frc::SendableChooser<int> * delayChooser;

	enum positions {left, center, right};
	enum targets {baseline, exchange, leftswitch, rightswitch, leftscale, rightscale};
	enum movements {M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11};
	enum commands {drive, reverse, turn, lift, lower, push, power, done};

	struct cmd {
		commands command;
		double data; 	/* feet or degrees */
	};

	cmd autocommand [POSITION_SIZE] /* position */ [TARGET_SIZE] /* target */ [MOVEMENT_SIZE]; /* movement */

	bool useDelay = false; //Delay our auto?
	int movement = 0; //What movement are we on?
	targets target = baseline;
	positions position = center;

public:
	Autonomous(DriveSystem * chasis, CubeDelivery * cube);
	~Autonomous();
	void AutoInit(std::string colors);
	void ReadStation();
	void AutoPeriodic();
	void AddOptions();
	void SetupAutoCommands();

	bool autodone = false; //Is movement done?
};

#endif /*SRC_AUTONOMOUS_H*/
