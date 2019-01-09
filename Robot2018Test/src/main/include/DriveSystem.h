/*
 * File:			ArcadeDrive.h
 * Author:			Hayden Mann
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * Defines the class and necessary includes for the ArcadeDrive.cpp file.  The ArcadeDrive class defines
 * all methods and instance variables necessary for driving the robot in either TeleOp or Autonomous modes,
 * using arcade drive.
 */

#ifndef SRC_DRIVESYSTEM_H_
#define SRC_DRIVESYSTEM_H_

//Standard library includes
#include <iostream>
#include <memory>
#include <string>

//FRC library includes
#include <Timer.h>
#include <GenericHID.h>
#include <ADXRS450_Gyro.h>
#include <Drive/DifferentialDrive.h>
#include "ctre/Phoenix.h"

class DriveSystem
{
public:
	enum MotorSpeed {Low, Normal, High};

	DriveSystem();
	~DriveSystem();
	void ResetHeading(); //Resets the gyro
	void Stop(); //Stops driving the talons.
	void Drive(double& Y, double& X); //Drive the robot forward given the current coordinates from the xbox controller
	void DriveStraight(bool direction); //Used for driving the robot straight during autonomous
	void DriveTurn (double angle); //Used for driving the robot at an angle during autonomous.
	void TestGyro();
	void ChangeSpeed(MotorSpeed change); //Used to change the robot speed during TeleOp

	const float SMOOTH_TIME = 0.4; //Sets time in seconds the motors take to get from neutral to full power

private:
	//TalonSRX's
	WPI_TalonSRX * leftLead; //Front left, leader
	WPI_TalonSRX * rightLead; //Front right, leader
	WPI_TalonSRX * leftFollower; //Back left, follower
	WPI_TalonSRX * rightFollower; //Back right, follower

	frc::DifferentialDrive * diffDrive; //Drivetrain
	frc::ADXRS450_Gyro * gyro; //Instantiate gyro and initialize its port
	frc::Timer driveTime{};

	//Constants for ports and unique id
	const unsigned int LEFT_LEAD_ID = 1;
	const unsigned int LEFT_FOLLOWER_ID = 2;
	const unsigned int RIGHT_LEAD_ID = 3;
	const unsigned int RIGHT_FOLLOWER_ID = 4;

	//Constants for driving
	const float SAFETY_TIMEOUT = 2.0;
	const float AUTO_POWER = 1.0; //Multiplier of max output for autonomous //Was:.9

	//Changable powers
	const float MAX_OUTPUT = 0.7; //Was 0.6
	const float LOW_OUTPUT = 0.4; //Lower output for TeleOp
	const float HIGH_OUTPUT = 1.0;

	//Turn powers for turning in autonomous
	const float TURN_POWER_Y = 0.0;
	const float LEFT_TURN_POWER_X = -0.63;
	const float RIGHT_TURN_POWER_X = 0.61; //Was:0.67
	const float STRAIGHT_ADJUST = 0.4;

};

#endif /* SRC_DRIVESYSTEM_H_ */
