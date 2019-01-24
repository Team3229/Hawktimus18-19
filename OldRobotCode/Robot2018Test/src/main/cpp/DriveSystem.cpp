/*
 * File:			ArcadeDrive.cpp
 * Author:			Hayden Mann
 * Last Modified:	02/03/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * Contains the code for arcade drive and talons.
 *
 * Connect to robot: roborio-3229-FRC.local
 */

#include "DriveSystem.h"

DriveSystem::DriveSystem()
{
	//Initialize the gyro and reset to zero
	gyro = new frc::ADXRS450_Gyro{frc::SPI::kOnboardCS0};
	gyro->Calibrate();
	gyro->Reset();

	//Instantiate motor controllers
	leftLead = new WPI_TalonSRX(LEFT_LEAD_ID);
	rightLead = new WPI_TalonSRX(RIGHT_LEAD_ID);
	leftFollower = new WPI_TalonSRX(LEFT_FOLLOWER_ID);
	rightFollower = new WPI_TalonSRX(RIGHT_FOLLOWER_ID);

	//Reset the controllers
	leftLead->Set(ControlMode::PercentOutput, 0);
	rightLead->Set(ControlMode::PercentOutput, 0);
	leftFollower->Set(ControlMode::PercentOutput, 0);
	leftFollower->Set(ControlMode::PercentOutput, 0);

	//Sets smoothing curve to talons
	leftLead->ConfigOpenloopRamp(SMOOTH_TIME, 0); //passes in seconds from neutral to full and timeout in miliseconds
	rightLead->ConfigOpenloopRamp(SMOOTH_TIME, 0);
	leftFollower->ConfigOpenloopRamp(SMOOTH_TIME, 0);
	rightFollower->ConfigOpenloopRamp(SMOOTH_TIME, 0);

	//Clears sticky faults
	leftLead->ClearStickyFaults(0);
	rightLead->ClearStickyFaults(0);
	leftFollower->ClearStickyFaults(0);
	rightFollower->ClearStickyFaults(0);

	//Set followers
	leftFollower->Follow(*leftLead);
	rightFollower->Follow(*rightLead);

	//Instantiate DriveTrain
	diffDrive = new frc::DifferentialDrive(*leftLead, *rightLead);

	//Implement drive train safety
	diffDrive->SetExpiration(SAFETY_TIMEOUT); //Set safety timer
	diffDrive->SetSafetyEnabled(false); //added 3/18 turns off safety check
	diffDrive->SetMaxOutput(MAX_OUTPUT); //Sets motor max power

}

DriveSystem::~DriveSystem()
{
	delete leftLead;
	delete rightLead;
	delete leftFollower;
	delete rightFollower;
	delete diffDrive;
	delete gyro;
}

void DriveSystem::ResetHeading()
{
	//Reset the gyro so zero angle is straight ahead
	gyro->Reset();
}

void DriveSystem::Stop()
{
	diffDrive->ArcadeDrive(0, 0);
}

void DriveSystem::Drive (double& Y, double& X)
{
	//Flip the Y value because of the RobotDrive.Drive function is opposite of the XBoxController
	Y = -Y;

	//std::cout << "diffDrive Y: " << Y << " X: " << X << std::endl; //puts in console our x and y
	diffDrive->ArcadeDrive(Y, X);
}

/*Drives the robot straight and checks each iteration to make sure it is still straight, direction is false for
 * backwards.  For direction, true is forwards, false is backwards*/
void DriveSystem::DriveStraight(bool direction)
{
	double gyroAngle = 0.0; //Holds the current angle of the gyro
	double adjust = 0.0; //Holds the angle the robot will use to adjust
	double power = 0.0;

	// Set power to motor based on direction (forward or reverse)
	if (direction)
		power = AUTO_POWER;
	else
		power = -AUTO_POWER;

	// Check the current heading
	gyroAngle = gyro->GetAngle();
	if (gyroAngle > 180)
		gyroAngle = gyroAngle - 360;

	// Adjust heading if necessary
	if(gyroAngle < 0) //current robot angle is negative
		adjust = STRAIGHT_ADJUST; //move right, we are moving left
	else if(gyroAngle > 0) //current robot angle is positive
		adjust = -STRAIGHT_ADJUST; //move left, we are moving right
	else if(gyroAngle == 0) //We don't need to correct
		adjust = 0.0;

	// Drive the next segment
	//std::cout << "DriveStraight Gyro angle:" << gyroAngle << "power:" << power << "adjust:" << adjust << std::endl;
	diffDrive->ArcadeDrive(power, adjust);
}

//Turns the specified angle (in positive of negative degrees from zero) only in autonomous.
void DriveSystem::DriveTurn (double angle)
{
	double gyroAngle = 0.0;
	double turnpowerY = 0.0;
	double turnpowerX = 0.0;

	// Check the current heading
	gyroAngle = gyro->GetAngle();
	if(gyroAngle > 180)
		gyroAngle = gyroAngle - 360;

	// Check if we have reached the desired angle
	if ((angle < 0) && (gyroAngle <= angle))
	{
		turnpowerY = 0.0;
		turnpowerX = 0.0;
	}
	else if ((angle > 0) && (gyroAngle >= angle))
	{
		turnpowerY = 0.0;
		turnpowerX = 0.0;
	}
	// if not, keep turning
	else
	{
		//For turning in place
		turnpowerY = TURN_POWER_Y;

		// Which way are we turning
		if (angle < 0)
			turnpowerX = LEFT_TURN_POWER_X;
		else
			turnpowerX = RIGHT_TURN_POWER_X;
	}
	// Turn
	//std::cout << "DriveTurn Gyro angle:" << gyroAngle << "Angle:" << angle << "Yturn:" << turnpowerY << "XTurn:" << turnpowerX << std::endl;
	diffDrive->ArcadeDrive(turnpowerY, turnpowerX);
}

void DriveSystem::ChangeSpeed(MotorSpeed change)
{
	//Currently used only during TeleOp
	if (change == MotorSpeed::Normal)
	{
		diffDrive->SetMaxOutput(MAX_OUTPUT); //Sets motors to max output
		//std::cout << "Robot set to max power at " << MAX_OUTPUT << std::endl;
	}
	else if (change == MotorSpeed::Low)
	{
		diffDrive->SetMaxOutput(LOW_OUTPUT); //Sets motors to lower output
		//std::cout << "Robot set to lower power at " << LOW_OUTPUT << std::endl;
	}
	else if (change == MotorSpeed::High) //Autonomus for scales
	{
		diffDrive->SetMaxOutput(HIGH_OUTPUT);
		//std::cout << "Robot set to max power at " << HIGH_OUTPUT << std::endl;
	}
}

void DriveSystem::TestGyro()
{
	double angle = gyro->GetAngle();
	std::cout << "Gyro angle: " << angle << std::endl;
}
