// Author: Team 3229 Programming Subteam

#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include <iostream>
#include <memory>
#include <Math.h>
#include "Debug.h"

//Phoenix 
#include "ctre/Phoenix.h"			//add vendor library
#include "ctre/phoenix/motorcontrol/can/TalonSRX.h" // new file WPI_TalonSRX is depricated

//FRC
#include <frc/GenericHID.h>
#include "frc/WPILib.h"
#include <frc/SpeedController.h>

//navX
#include "AHRS.h"				//add vendor library

class DriveSystem
{
public:
    DriveSystem();
    ~DriveSystem();
    void Drive(double& Y, double& X, double& Z);
	void DriveWithoutGyro(double& Y, double& X, double& Z);
    void Stop();
    void ChangeSpeed(int choice);
    double TestGyro();
	void ResetGyro();

private:
    //TalonSRX's
	WPI_TalonSRX * leftLead; //Front left, leader
	WPI_TalonSRX * rightLead; //Front right, leader
	WPI_TalonSRX * leftFollower; //Back left, follower
	WPI_TalonSRX * rightFollower; //Back right, follower

	frc::MecanumDrive * driveTrain; //Drivetrain

    AHRS * navxGyro; //navX drive

    //Constants for ports and unique id
	const int LEFT_LEAD_ID = 1;
	const int LEFT_FOLLOWER_ID = 2;
	const int RIGHT_LEAD_ID = 3;
	const int RIGHT_FOLLOWER_ID = 4;

    //Changable powers
	const float MAX_OUTPUT = 0.7;
	const float LOW_OUTPUT = 0.4;
	const float HIGH_OUTPUT = 1.0;

	const float SMOOTH_TIME = 0.4;
	const float SAFETY_TIMEOUT = 2.0;

};

#endif // DRIVESYSTEM_H