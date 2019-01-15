/*
 * File:			Robot.cpp
 * Author:			Neil Anderson
 * Version:			1.0
 * Last Modified:	01/17/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * Contains the default class for the Robot where First will run all of its required methods.
 */

#include <Robot.h>

class Robot : public frc::IterativeRobot
{
private:
	frc::LiveWindow* lw = frc::LiveWindow::GetInstance();

	//Instantiate XBOX Controller
	frc::XboxController xbox{XBOX_USB_PORT};

	//Instantiate Climber
	Climber climberMotor{};

	//Instantiate Autonomous mode
	Autonomous autoMode{};

	//Instantiate Chasis (drive train)
	ArcadeDrive chasis{};

public:

	//Runs once on first boot of Robot
	void RobotInit()
	{
		std::cout << "RobotInit()" << std::endl;

		//Display the Autonomous Selection Options on Driver Station
		autoMode.AutoSelectInit();
	}

	//Runs once when Autonomous starts
	void AutonomousInit() override //Override - Adds virtuality to the base class and will override any function with the same name, streamlining our method to the top of the method hierarchy.
	{
		std::cout << "AutonomousInit()" << std::endl;

		//Get the Autonomous Selection from the Driver Station
		autoMode.DoAutonomousInit();
	}

	//Runs continually during Autonomous
	void AutonomousPeriodic()
	{
		std::cout << "AutonomousPeriodic()" << std::endl;

		//While autonomous movements are not done (because it is re-entrant)
		autoMode.DoAutonomousPeriodic(&chasis);
	}

	//Runs once Teleop starts
	void TeleopInit()
	{
		std::cout << "TeleopInit()" << std::endl;
	}

	//Runs continually during Teleop
	void TeleopPeriodic()
	{
		double Y, X; //An x and y coordinate.
		//std::cout << "TeleopPeriodic()" << std::endl;

		//Drive (left hand joystick on the controller)
		//Get both the x and y coordinates from the left joystick.
		Y = xbox.GetY(frc::GenericHID::kLeftHand);
		X = xbox.GetX(frc::GenericHID::kLeftHand);
		if((abs(Y) > DEAD_BAND) || (abs(X) > DEAD_BAND)) //As long as the absolute value of the coordinate is not in the deadband.
		{
			//Driver joystick input.
			chasis.Drive(Y, X); //Call drive, passing the given coordinate.
		}
		else
		{
			chasis.Stop(); //No joystick input, stop moving.
		}

		//Climber (right hand "bumper" button)
		if (xbox.GetBumper(frc::GenericHID::kRightHand)) //Map the right hand "bumper" (trigger) button to the climber PWM.
		{
			climberMotor.Climb(); //button pressed
		}
		else
		{
			climberMotor.Stop(); //button released
		}
		frc::Wait(0.05);
	}

	//Test mode
	void TestPeriodic()
	{
		std::cout << "TestPeriodic()" << std::endl;

		//Removed "lw->Run()".  Error message stated that it was deprecated and no longer necessary.
	}

};

START_ROBOT_CLASS(Robot);
