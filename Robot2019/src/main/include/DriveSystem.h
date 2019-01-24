// Author: Team 3229 Programming Subteam

#include "Debug.h"

#include <iostream>
#include <memory>
#include <Math.h>
#include "ctre/Phoenix.h"
#include <Drive/DifferentialDrive.h>
#include <GenericHID.h>
#include "WPILib.h"
#include <WPI_TalonSRX.h>
#include "AHRS.h"

class DriveSystem
{
public:
    DriveSystem();
    ~DriveSystem();
    void Drive(double& Y, double& X, double& Z);
    void Stop();
    void ChangeSpeed(int choice);
    double TestGyro();

private:
    //TalonSRX's
	WPI_TalonSRX * leftLead; //Front left, leader
	WPI_TalonSRX * rightLead; //Front right, leader
	WPI_TalonSRX * leftFollower; //Back left, follower
	WPI_TalonSRX * rightFollower; //Back right, follower

	frc::MecanumDrive * driveTrain; //Drivetrain
    AHRS * navX; //navX drive

    //Constants for ports and unique id
	const int LEFT_LEAD_ID = 1;
	const int LEFT_FOLLOWER_ID = 2;
	const int RIGHT_LEAD_ID = 3;
	const int RIGHT_FOLLOWER_ID = 4;

    //Changable powers
	const float MAX_OUTPUT = 0.7;
	const float LOW_OUTPUT = 0.4;
	const float HIGH_OUTPUT = 1.0;

};