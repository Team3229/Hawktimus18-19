/*
 * File:		Autonomous.cpp
 * Author:		Programming Subteam
 * Team:		Hawktimus Prime - 3229
 *
 * File Description:
 * Contains the code to be executed for autonomous mode.
 */

#include "Autonomous.h"

Autonomous::Autonomous(DriveSystem * chasis, CubeDelivery * cube)
{
	positionChooser = new frc::SendableChooser<int>();
	targetChooser = new frc::SendableChooser<int>();
	delayChooser = new frc::SendableChooser<int>();
	driveTrain = chasis;
	gettinPoints = cube;
	scaleColor = '\0'; //Initialized so it wouldn't have a random value on declaration
	switchColor = '\0';
}

Autonomous::~Autonomous()
{
	delete positionChooser;
	delete targetChooser;
	delete delayChooser;
}

void Autonomous::AutoInit(std::string colors)
{
	switchColor = colors[0]; //Get the color of the switch
	scaleColor = colors[1]; //get the4 color of the scale
	ReadStation(); //Setup commands moved to robot init
	autoTimer.Reset();
	movement = 0;
	autodone = false;
}

void Autonomous::AutoPeriodic()
{
	if (useDelay)
	{
		frc::Wait(5);
		useDelay = false;
	}

	//For best results, use a fully charged battery
	while (!autodone)
	{
		/*std::cout << "Command: " << autocommand[position][target][movement].command << std::endl;
		std::cout << "Data: " << autocommand[position][target][movement].data << std::endl;
		std::cout << "Position: " << autocommand[position] << std::endl;
		std::cout << "Target: " << autocommand[position][target] << std::endl << std::endl;
		std::cout << "Movement: " << movement << std::endl;
		std::cout << "Auto timer: " << autoTimer.Get() << std::endl;*/

		switch (autocommand[position][target][movement].command)
		{
		case drive:
			if (autoTimer.Get() == 0) {
				driveTrain->ResetHeading();
				timeLimit = (autocommand[position][target][movement].data/DRIVE_FT_SEC) + (driveTrain->SMOOTH_TIME / 2);
				autoTimer.Start();
			}
			if (autoTimer.Get() < timeLimit) {
				driveTrain->DriveStraight(FORWARD);
			}
			else {
				driveTrain->Stop();
				autoTimer.Stop();
				autoTimer.Reset();
				movement++;
			}
			break;

		case reverse:
			if (autoTimer.Get() == 0) {
				driveTrain->ResetHeading();
				timeLimit = (autocommand[position][target][movement].data/DRIVE_FT_SEC) + (driveTrain->SMOOTH_TIME / 2);
				autoTimer.Start();
			}
			if (autoTimer.Get() < timeLimit) {
				driveTrain->DriveStraight(REVERSE);
			}
			else {
				driveTrain->Stop();
				autoTimer.Stop();
				autoTimer.Reset();
				movement++;
			}
			break;

		case turn:
			if (autoTimer.Get() == 0) {
				driveTrain->ResetHeading();
				autoTimer.Start();
			}
			if (autoTimer.Get() < TURN_TIMEOUT) {
				driveTrain->DriveTurn(autocommand[position][target][movement].data);
			}
			else {
				driveTrain->Stop();
				autoTimer.Stop();
				autoTimer.Reset();
				movement++;
			}
			break;

		case lift:
			if (autoTimer.Get() == 0) {
				timeLimit = autocommand[position][target][movement].data/LIFT_FT_SEC;
				autoTimer.Start();
			}
			if (autoTimer.Get() < timeLimit) {
				gettinPoints->Lift(CubeDelivery::LiftDirection::Up);
			}
			else {
				gettinPoints->StopLift();
				autoTimer.Stop();
				autoTimer.Reset();
				movement++;
			}
			break;

		case lower:
			if (autoTimer.Get() == 0) {
				timeLimit = autocommand[position][target][movement].data/LIFT_FT_SEC;
				autoTimer.Start();
			}
			if (autoTimer.Get() < timeLimit) {
				gettinPoints->Lift(CubeDelivery::LiftDirection::Down);
			}
			else {
				gettinPoints->StopLift();
				autoTimer.Stop();
				autoTimer.Reset();
				movement++;
			}
			break;

		case push:
			if (autoTimer.Get() == 0) {
				autoTimer.Start();
			}
			if (autoTimer.Get() < PUSH_TIME) {
				gettinPoints->PushCube();
			}
			else {
				gettinPoints->StopConveyor();
				autoTimer.Stop();
				autoTimer.Reset();
				movement++;
			}
			break;

		case power:
			speedChange = autocommand[position][target][movement].data;
			if (speedChange == LOW_POWER)
				driveTrain->ChangeSpeed(DriveSystem::MotorSpeed::Low); //Puts robot in low power mode
			else if (speedChange == HIGH_POWER)
				driveTrain->ChangeSpeed(DriveSystem::MotorSpeed::High); //Puts robot in high power mode
			else if (speedChange == NORMAL_POWER)
				driveTrain->ChangeSpeed(DriveSystem::MotorSpeed::Normal); //Puts robot in normal power mode

			movement++;
			break;

		case done:
			autodone = true;
			break;
		}
	}
}

void Autonomous::AddOptions()
{
	//Function called in constructor to set up dashboard options
	int Center = 0; //3 variables for 3 options from chooser
	int Left = 1;
	int Right = 2;
	positionChooser->AddDefault("Center", Center); //Center will be selected by default
	positionChooser->AddObject("Left", Left); //Other 2 are other options under it
	positionChooser->AddObject("Right", Right);
	frc::SmartDashboard::PutData("Starting Position", positionChooser); //Labels the dropdown box.

	int baseline = 1;
	int exchange = 2; //5 variables for target chooser
	int theSwitch = 3;
	int scale = 4;
	targetChooser->AddDefault("Baseline",baseline); //Default option
	targetChooser->AddObject("Exchange", exchange); //Adds the other 4 target options to the chooser
	targetChooser->AddObject("Switch", theSwitch);
	targetChooser->AddObject("Scale", scale);
	frc::SmartDashboard::PutData("Target", targetChooser); //Labels the dropdown box.

	int No = 0; //Default is no, the 2 options for making the robot wait
	int Yes = 1;
	delayChooser->AddDefault("No", No);
	delayChooser->AddObject("Yes", Yes);
	frc::SmartDashboard::PutData("Delay?", delayChooser); //Labels the dropdown box.
}

//Reads values from the smart dashboard.
void Autonomous::ReadStation()
{
	//std::cout << "TChooser: " << targetChooser->GetSelected() << std::endl;
	//std::cout << "PChooser: " << positionChooser->GetSelected() << std::endl;

	int targetChoice = targetChooser->GetSelected();
	int positionChoice = positionChooser->GetSelected();

	if(targetChoice == 1)
		target = baseline;
	else if(targetChoice == 2)
		target = exchange;
	else if(targetChoice == 3)
	{
		if(switchColor == 'R')
			target = rightswitch;
		else
			target = leftswitch;
	}
	else if(targetChoice == 4)
	{
		if(scaleColor == 'R')
			target = rightscale;
		else
			target = leftscale;
	}

	if(positionChoice == 0)
		position = center;
	else if(positionChoice == 1)
		position = left;
	else if(positionChoice == 2)
		position = right;

	//Decide delay
	if(delayChooser->GetSelected() == 0)
		useDelay = false;
	else
		useDelay = true;
}

void Autonomous::SetupAutoCommands()
{
	//std::cout << "SetupAutoCommands()" << std::endl;

	// start = left, target = baseline
	autocommand[left][baseline][M1].command = lift;
	autocommand[left][baseline][M1].data = START_LIFT_DISTANCE;
	autocommand[left][baseline][M2].command = drive;
	autocommand[left][baseline][M2].data = 8.0;
	autocommand[left][baseline][M3].command = done;

	// start = center, target = baseline
	autocommand[center][baseline][M1].command = lift;
	autocommand[center][baseline][M1].data = START_LIFT_DISTANCE;
	autocommand[center][baseline][M2].command = drive;
	autocommand[center][baseline][M2].data = 8.0;
	autocommand[center][baseline][M3].command = done;

	// start = right, target = baseline
	autocommand[right][baseline][M1].command = lift;
	autocommand[right][baseline][M1].data = START_LIFT_DISTANCE;
	autocommand[right][baseline][M2].command = drive;
	autocommand[right][baseline][M2].data = 8.0;
	autocommand[right][baseline][M3].command = done;

	// start = left, target = exchange
	autocommand[left][exchange][M1].command = lift;
	autocommand[left][exchange][M1].data = START_LIFT_DISTANCE;
	autocommand[left][exchange][M2].command = drive;
	autocommand[left][exchange][M2].data = 8.5;
	autocommand[left][exchange][M3].command = reverse;
	autocommand[left][exchange][M3].data = 5.5;
	autocommand[left][exchange][M4].command = turn;
	autocommand[left][exchange][M4].data = 90;
	autocommand[left][exchange][M5].command = drive;
	autocommand[left][exchange][M5].data = 5.0;
	autocommand[left][exchange][M6].command = turn;
	autocommand[left][exchange][M6].data = 90;
	autocommand[left][exchange][M7].command = drive;
	autocommand[left][exchange][M7].data = 1.0;
	autocommand[left][exchange][M8].command = push;
	autocommand[left][exchange][M9].command = done;

	//start = center, target = exchange
	autocommand[center][exchange][M1].command = lift;
	autocommand[center][exchange][M1].data = START_LIFT_DISTANCE;
	autocommand[center][exchange][M2].command = drive;
	autocommand[center][exchange][M2].data = 8.5;
	autocommand[center][exchange][M3].command = reverse;
	autocommand[center][exchange][M3].data = 5.5;
	autocommand[center][exchange][M4].command = turn;
	autocommand[center][exchange][M4].data = -90;
	autocommand[center][exchange][M5].command = drive;
	autocommand[center][exchange][M5].data = 3.0;
	autocommand[center][exchange][M6].command = turn;
	autocommand[center][exchange][M6].data = -90;
	autocommand[center][exchange][M7].command = drive;
	autocommand[center][exchange][M7].data = 4.8;
	autocommand[center][exchange][M8].command = push;
	autocommand[center][exchange][M9].command = done;

	//start = right, target = exchange
	autocommand[right][exchange][M1].command = lift;
	autocommand[right][exchange][M1].data = START_LIFT_DISTANCE;
	autocommand[right][exchange][M2].command = drive;
	autocommand[right][exchange][M2].data = 8.5;
	autocommand[right][exchange][M3].command = reverse;
	autocommand[right][exchange][M3].data = 5.5;
	autocommand[right][exchange][M4].command = turn;
	autocommand[right][exchange][M4].data = -90;
	autocommand[right][exchange][M5].command = drive;
	autocommand[right][exchange][M5].data = 15.0;
	autocommand[right][exchange][M6].command = turn;
	autocommand[right][exchange][M6].data = -90;
	autocommand[right][exchange][M7].command = drive;
	autocommand[right][exchange][M7].data = 3.0;
	autocommand[right][exchange][M8].command = push;
	autocommand[right][exchange][M9].command = done;

	// start = left, target = left switch ADD SLOW
	autocommand[left][leftswitch][M1].command = lift;
	autocommand[left][leftswitch][M1].data = START_LIFT_DISTANCE;
	autocommand[left][leftswitch][M2].command = drive;
	autocommand[left][leftswitch][M2].data = 14.5;
	autocommand[left][leftswitch][M3].command = turn;
	autocommand[left][leftswitch][M3].data = 90;
	autocommand[left][leftswitch][M4].command = power;
	autocommand[left][leftswitch][M4].data = LOW_POWER;
	autocommand[left][leftswitch][M5].command = drive;
	autocommand[left][leftswitch][M5].data = 7.0;
	autocommand[left][leftswitch][M6].command = lift;
	autocommand[left][leftswitch][M6].data = 2.0;
	autocommand[left][leftswitch][M7].command = push;
	autocommand[left][leftswitch][M8].command = done;

	// start = left, target = right switch JUST BASELINE
	autocommand[left][rightswitch][M1].command = lift;
	autocommand[left][rightswitch][M1].data = START_LIFT_DISTANCE;
	autocommand[left][rightswitch][M2].command = drive;
	autocommand[left][rightswitch][M2].data = 8.0;
	autocommand[left][rightswitch][M3].command = done;
	//old one:
	/*autocommand[left][rightswitch][M1].command = lift;
	autocommand[left][rightswitch][M1].data = START_LIFT_DISTANCE;
	autocommand[left][rightswitch][M2].command = drive;
	autocommand[left][rightswitch][M2].data = 21.0;
	autocommand[left][rightswitch][M3].command = turn;
	autocommand[left][rightswitch][M3].data = 90;
	autocommand[left][rightswitch][M4].command = drive;
	autocommand[left][rightswitch][M4].data = 15.5;
	autocommand[left][rightswitch][M5].command = turn;
	autocommand[left][rightswitch][M5].data = 90;
	autocommand[left][rightswitch][M6].command = lift;
	autocommand[left][rightswitch][M6].data = 2.5;
	autocommand[left][rightswitch][M7].command = push;
	autocommand[left][rightswitch][M8].command = lower;
	autocommand[left][rightswitch][M8].data = 2.5;
	autocommand[left][rightswitch][M9].command = done;*/

	// start = right, target = right switch ADD SLOW
	autocommand[right][rightswitch][M1].command = lift;
	autocommand[right][rightswitch][M1].data = START_LIFT_DISTANCE;
	autocommand[right][rightswitch][M2].command = drive;
	autocommand[right][rightswitch][M2].data = 14.5;
	autocommand[right][rightswitch][M3].command = turn;
	autocommand[right][rightswitch][M3].data = -90;
	autocommand[right][rightswitch][M4].command = power;
	autocommand[right][rightswitch][M4].data = LOW_POWER;
	autocommand[right][rightswitch][M5].command = drive;
	autocommand[right][rightswitch][M5].data = 7.0;
	autocommand[right][rightswitch][M6].command = lift;
	autocommand[right][rightswitch][M6].data = 2.0;
	autocommand[right][rightswitch][M7].command = push;
	autocommand[right][rightswitch][M8].command = done;

	// start = right, target = left switch JUST BASELINE
	autocommand[right][leftswitch][M1].command = lift;
	autocommand[right][leftswitch][M1].data = START_LIFT_DISTANCE;
	autocommand[right][leftswitch][M2].command = drive;
	autocommand[right][leftswitch][M2].data = 8.0;
	autocommand[right][leftswitch][M3].command = done;
	//old one:
	/*autocommand[right][leftswitch][M1].command = lift;
	autocommand[right][leftswitch][M1].data = START_LIFT_DISTANCE;
	autocommand[right][leftswitch][M2].command = drive;
	autocommand[right][leftswitch][M2].data = 20.0;
	autocommand[right][leftswitch][M3].command = turn;
	autocommand[right][leftswitch][M3].data = -90;
	autocommand[right][leftswitch][M4].command = drive;
	autocommand[right][leftswitch][M4].data = 15.0;
	autocommand[right][leftswitch][M5].command = turn;
	autocommand[right][leftswitch][M5].data = -90;
	autocommand[right][leftswitch][M6].command = drive;
	autocommand[right][leftswitch][M6].data = 1.5;
	autocommand[right][leftswitch][M7].command = lift;
	autocommand[right][leftswitch][M7].data = 2.5;
	autocommand[right][leftswitch][M8].command = push;
	autocommand[right][leftswitch][M9].command = lower;
	autocommand[right][leftswitch][M9].data = 2.5;
	autocommand[right][leftswitch][M10].command = done;*/

	// start = center, target = left switch
	autocommand[center][leftswitch][M1].command = lift;
	autocommand[center][leftswitch][M1].data = START_LIFT_DISTANCE;
	autocommand[center][leftswitch][M2].command = drive;
	autocommand[center][leftswitch][M2].data = 4.0;
	autocommand[center][leftswitch][M3].command = turn;
	autocommand[center][leftswitch][M3].data = -90;
	autocommand[center][leftswitch][M4].command = drive;
	autocommand[center][leftswitch][M4].data = 6.5;
	autocommand[center][leftswitch][M5].command = turn;
	autocommand[center][leftswitch][M5].data = 90;
	autocommand[center][leftswitch][M6].command = power;
	autocommand[center][leftswitch][M6].data = LOW_POWER;
	autocommand[center][leftswitch][M7].command = drive;
	autocommand[center][leftswitch][M7].data = 20.0; //Massive because slow
	autocommand[center][leftswitch][M8].command = lift;
	autocommand[center][leftswitch][M8].data = 2.5;
	autocommand[center][leftswitch][M9].command = push;
	autocommand[center][leftswitch][M10].command = done;

	// start = center, target = right switch
	autocommand[center][rightswitch][M1].command = lift;
	autocommand[center][rightswitch][M1].data = START_LIFT_DISTANCE;
	autocommand[center][rightswitch][M2].command = drive;
	autocommand[center][rightswitch][M2].data = 4.0;
	autocommand[center][rightswitch][M3].command = turn;
	autocommand[center][rightswitch][M3].data = 90;
	autocommand[center][rightswitch][M4].command = drive;
	autocommand[center][rightswitch][M4].data = 2.75;
	autocommand[center][rightswitch][M5].command = turn;
	autocommand[center][rightswitch][M5].data = -90;
	autocommand[center][rightswitch][M6].command = power;
	autocommand[center][rightswitch][M6].data = LOW_POWER;
	autocommand[center][rightswitch][M7].command = drive;
	autocommand[center][rightswitch][M7].data = 20.0; //Massive because slow
	autocommand[center][rightswitch][M8].command = lift;
	autocommand[center][rightswitch][M8].data = 2.5;
	autocommand[center][rightswitch][M9].command = push;
	autocommand[center][rightswitch][M10].command = done;

	// start = center, target = left scale GO FOR BASLINE BECAUSE CENTER SWITCH IS BAD
	autocommand[center][leftscale][M1].command = lift;
	autocommand[center][leftscale][M1].data = START_LIFT_DISTANCE;
	autocommand[center][leftscale][M2].command = drive;
	autocommand[center][leftscale][M2].data = 8.0;
	autocommand[center][leftscale][M3].command = done;

	// start = center, target = right scale GO FOR BASLINE BECAUSE CENTER SWITCH IS BAD
	autocommand[center][rightscale][M1].command = lift;
	autocommand[center][rightscale][M1].data = START_LIFT_DISTANCE;
	autocommand[center][rightscale][M2].command = drive;
	autocommand[center][rightscale][M2].data = 8.0;
	autocommand[center][rightscale][M3].command = done;

	//start = left, target = left scale
	autocommand[left][leftscale][M1].command = lift;
	autocommand[left][leftscale][M1].data = START_LIFT_DISTANCE;
	autocommand[left][leftscale][M2].command = drive;
	autocommand[left][leftscale][M2].data = 30.0;
	autocommand[left][leftscale][M3].command = turn;
	autocommand[left][leftscale][M3].data = 70;
	autocommand[left][leftscale][M4].command = lift;
	autocommand[left][leftscale][M4].data = 5.7;
	autocommand[left][leftscale][M5].command = push;
	autocommand[left][leftscale][M6].command = lower;
	autocommand[left][leftscale][M6].data = 5.7;
	autocommand[left][leftscale][M7].command = done;

	//start = left, target = right scale NOT DOING GO FOR BASELINE
	autocommand[left][rightscale][M1].command = lift;
	autocommand[left][rightscale][M1].data = START_LIFT_DISTANCE;
	autocommand[left][rightscale][M2].command = drive;
	autocommand[left][rightscale][M2].data = 8.0;
	autocommand[left][rightscale][M3].command = done;

	//start = right, target = right scale
	autocommand[right][rightscale][M1].command = lift;
	autocommand[right][rightscale][M1].data = START_LIFT_DISTANCE;
	autocommand[right][rightscale][M2].command = drive;
	autocommand[right][rightscale][M2].data = 30.0;
	autocommand[right][rightscale][M3].command = turn;
	autocommand[right][rightscale][M3].data = -70;
	autocommand[right][rightscale][M4].command = lift;
	autocommand[right][rightscale][M4].data = 5.7;
	autocommand[right][rightscale][M5].command = push;
	autocommand[right][rightscale][M6].command = lower;
	autocommand[right][rightscale][M6].data = 5.7;
	autocommand[right][rightscale][M7].command = done;

	//start = right, target = left scale NOT DOING GO FOR BASELINE
	autocommand[right][leftscale][M1].command = lift;
	autocommand[right][leftscale][M1].data = START_LIFT_DISTANCE;
	autocommand[right][leftscale][M2].command = drive;
	autocommand[right][leftscale][M2].data = 8.0;
	autocommand[right][leftscale][M3].command = done;
}
