/*
 * File:			Robot.cpp
 * Author(s):		Hayden Mann
 * Last Modified:	02/02/18
 * Team:			Hawktimus Prime - 3229
 *
 * File Description:
 * Contains the default class for running the robot through the roboRIO for the 2018 build season
 *
 * Connect to robot: roborio-3229-FRC.local
 */

#include "Robot.h"

class Robot : public frc::IterativeRobot
{
private:
	//Constants for controller
	const float DEAD_BAND_LEFT = 0.1;
	const float DEAD_BAND_RIGHT = 0.1;
	const int XBOX_USB_PORT = 0; //Current Driver 1 port
	const float START_LOCK_TIME = 1.5; //Time that the lift will lock climbing
	//const int DRIVER2_XBOX_USB_PORT = 1;

	//Timer for resetting lift
	frc::Timer resetTimer{};

	//Instantiate XBOX Controller
	frc::XboxController xbox{XBOX_USB_PORT};

	//Driver 2 controller
	//XboxController driver2Xbox{DRIVER2_XBOX_USB_PORT};

	//Instantiate Climber and it's timer
	Climber climberMotor{};

	//Instantiate Chasis (drive train)
	DriveSystem chasis{};

	//Instantiate object to control conveyor and lift system.
	CubeDelivery gettinPoints{};

	//Instantiate Autonomous mode
    Autonomous autoMode{&chasis, &gettinPoints};

	//Instantiate camera
	Camera driveCam{};

public:

	//Runs once on first boot of Robot
	void RobotInit()
	{
		//std::cout << "RobotInit()" << std::endl;
		autoMode.AddOptions();
		autoMode.SetupAutoCommands();
	}

	//Runs once when Autonomous starts
	void AutonomousInit() override //Override - overrides the base class's autonomous given an object with polymorphic behaviors
	{
		//std::cout << "AutonomousInit()" << std::endl;
		chasis.ChangeSpeed(DriveSystem::MotorSpeed::Normal);
		//Get the Autonomous Selection from the Driver Station, pass in Game string for random colors.
		autoMode.AutoInit(frc::DriverStation::GetInstance().GetGameSpecificMessage());
	}

	//Runs continually during Autonomous
	void AutonomousPeriodic()
	{
		//std::cout << "AutonomousPeriodic()" << std::endl;
		while (!autoMode.autodone)
		{
			autoMode.AutoPeriodic();
		}
		//While autonomous movements are not done (because it is re-entrant)
	}

	//Runs once Teleop starts
	void TeleopInit()
	{
		autoMode.autodone = true;
		//std::cout << "TeleopInit()" << std::endl;
		chasis.ChangeSpeed(DriveSystem::MotorSpeed::Normal);
	}

	//Runs continually during Teleop
	void TeleopPeriodic()
	{
		double leftY, leftX, rightY; //An x and y coordinate.
		//std::cout << "TeleopPeriodic()" << std::endl;

		//Drive (left hand joystick on the controller)
		//Get both the x and y coordinates from the left joystick.
		leftY = xbox.GetY(frc::GenericHID::kLeftHand);
		leftX = xbox.GetX(frc::GenericHID::kLeftHand);
		if(abs(leftX) > DEAD_BAND_LEFT || abs(leftY) > DEAD_BAND_LEFT)
		{
			chasis.Drive(leftY, leftX);
		}
		else
		{
			chasis.Stop();
		}

		//Climber (right hand "Y" button)
		if (xbox.GetYButton()) //Map the right hand "bumper" (trigger) button to the climber PWM, button is pressed.
		{
			climberMotor.Climb(); //Climbs
		}
		else
		{
			climberMotor.Stop(); //button released
		}

		//Map right joystick for the conveyor
		rightY = xbox.GetRawAxis(5);
		if (abs(rightY) > DEAD_BAND_RIGHT)
		{
			if (rightY < DEAD_BAND_RIGHT)
			{
				gettinPoints.Lift(CubeDelivery::LiftDirection::Up); //Move the lift system up
			}
			else
			{
				gettinPoints.Lift(CubeDelivery::LiftDirection::Down); //Move the lift system down
			}
		}
		else
		{
			gettinPoints.StopLift();
		}

		//Map the left and right bumper to the climbers
		if(xbox.GetBumper(frc::GenericHID::kRightHand)) //Right bumper
		{
			gettinPoints.Conveyor(CubeDelivery::ConveyorDirection::Out); //Push cube out
		}
		else if(xbox.GetBumper(frc::GenericHID::kLeftHand)) //Left bumper
		{
			gettinPoints.Conveyor(CubeDelivery::ConveyorDirection::In); //Succ cube in
		}
		else
		{
			gettinPoints.StopConveyor();
		}

		//2 buttons to switch between high and low power
		if (xbox.GetAButton()) //A button
		{
			//Sets normal speed
			chasis.ChangeSpeed(DriveSystem::MotorSpeed::Normal);
		}
		if (xbox.GetBButton()) //B button
		{
			//Sets the lower power mode
			chasis.ChangeSpeed(DriveSystem::MotorSpeed::Low);
		}
		if (xbox.GetXButton()) //X button
		{
			//Sets high power mode
			chasis.ChangeSpeed(DriveSystem::MotorSpeed::High);
		}
		frc::Wait(0.05);
	}

	//Test mode
	void TestPeriodic()
	{
		//std::cout << "TestPeriodic()" << std::endl;
	}
};

START_ROBOT_CLASS(Robot);
