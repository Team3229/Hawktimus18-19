// Author: Team 3229 Programming Subteam

#include "DriveSystem.h"

DriveSystem::DriveSystem()
{
    //Instantiate motor controllers
	leftLead = new WPI_TalonSRX(LEFT_LEAD_ID);
	rightLead = new WPI_TalonSRX(RIGHT_LEAD_ID);
	leftFollower = new WPI_TalonSRX(LEFT_FOLLOWER_ID);
	rightFollower = new WPI_TalonSRX(RIGHT_FOLLOWER_ID);

    //Set followers
	leftFollower->Follow(*leftLead);
	rightFollower->Follow(*rightLead);

	//Instantiate DriveTrain
	driveTrain = new frc::MecanumDrive(*leftLead, *leftFollower, *rightLead, *rightFollower);

    //Reset the controllers
	leftLead->Set(ControlMode::PercentOutput, 0);
	rightLead->Set(ControlMode::PercentOutput, 0);
	leftFollower->Set(ControlMode::PercentOutput, 0);
	leftFollower->Set(ControlMode::PercentOutput, 0);

    //Clears sticky faults
	leftLead->ClearStickyFaults(0);
	rightLead->ClearStickyFaults(0);
	leftFollower->ClearStickyFaults(0);
	rightFollower->ClearStickyFaults(0);

    //navX stuff
    navX = new AHRS(SPI::Port::kMXP);
}

DriveSystem::~DriveSystem()
{
    delete leftLead;
	delete rightLead;
	delete leftFollower;
	delete rightFollower;
	delete driveTrain;
	delete navX;
}

void DriveSystem::Drive(double& Y, double& X, double& Z)
{
    //Drive function
    driveTrain->MecanumDrive_Cartesian(X, Y, Z, navX->GetAngle()); //Optional 4th parameter for gyro input
}

void DriveSystem::Stop()
{
    driveTrain->MecanumDrive_Cartesian(0, 0, 0);
}

void DriveSystem::ChangeSpeed(int choice)
{
    if (choice == 1)
        driveTrain->SetMaxOutput(LOW_OUTPUT);
    else if (choice == 2)
        driveTrain->SetMaxOutput(MAX_OUTPUT);
    else if (choice == 3)
        driveTrain->SetMaxOutput(HIGH_OUTPUT);
}

double DriveSystem::TestGyro()
{
    return navX->GetAngle();
}