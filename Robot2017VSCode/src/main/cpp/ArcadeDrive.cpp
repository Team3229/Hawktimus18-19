#include <ArcadeDrive.h>

ArcadeDrive::ArcadeDrive()
{
	//Initialize the gyro sensitivity
	gyro.SetSensitivity(GYRO_GAIN);

	//Set the safety timer on the motor system
	myDriveTrain.SetExpiration(SAFETY_TIMEOUT);
}


void ArcadeDrive::ResetHeading()
{
	//Reset the gyro so zero angle is straight ahead
	gyro.Reset();
}

void ArcadeDrive::Stop()
{
	myDriveTrain.ArcadeDrive(0, 0);
	frc::Wait(0.05);
}


void ArcadeDrive::Drive (double Y, double X)
{
	//Apply smothing curve to acceleration
	Y = (pow(MAX_POWER, Y) * Y);

	//Flip the Y value because of the RobotDrive.Drive function
	//is opposite of the XBoxController
	Y = -Y;

	//Enforce a max power/speed
	if(abs(Y) > MAX_POWER) //If the absolute value of y is greater than the max power we are allowing the Sparks to have (0.8)...
	{
		if (Y < 0) //Test to see if Y is negative (moving forwards, first two quadrants)
		{
			Y = 0 - MAX_POWER; //Make sure y is less than the max power and that it is negative (we are moving forward)
		}
		else //Otherwise we are moving backwards (third and fourth quadrants)
		{
			Y = MAX_POWER; //Make sure that y is less than the max power, postive because we are moving backwards.
		}
	}

	if(abs(X) > MAX_POWER) //Make sure the absolute value of x is not greater than the max power
	{
		if (X < 0) //If we are moving left (second and third quadrants).
		{
			X = 0 - MAX_POWER; //Make sure x is at the max power and that it is negative (we are moving left)
		}
		else //If we are moving right (first and fourth quadrants)
		{
			X = MAX_POWER; //Make sure that x is at the max power and that it is positive (we are moving right)
		}
	}

	//Drive
	myDriveTrain.ArcadeDrive(Y, -X, false);  //Drive the robot forward, passing in the correct values for the speed to each PWM.  X and Y have been enforced.
}

//Drives Straight only in autonomous
void ArcadeDrive::DriveStraight()
{
	double X = 0;
	double heading = 0;

	//Check if robot has veered right or left
	heading = gyro.GetAngle();
	if (heading > 180)
	{
		heading = heading - 360;
	}

	//Adjust X value to compensate for any heading discrepency.
	X = heading * COMP_RATIO;

	myDriveTrain.ArcadeDrive(AUTO_POWER, X);
}

//Turns the specified angle (in positive of negative degrees from zero) only in autonomous.
void ArcadeDrive::DriveTurn (int angle)
{
	double X = 0; //Signals the drive angle
	double heading = 0; //Holds the current angle
	int max_iterations = 20; //Basically a "time-out" counter
	int i = 0; //Counts iterations
	bool angle_achieved = false;

	//Adjust X value to compensate to change heading, set the angle.
	if (angle > 0) //Right turn
	{
		X = TURN_POWER;
	}
	else // Left Turn
	{
		X = 0 - TURN_POWER;
	}

	//Repeat until turn angle is achieved (max 20 iterations)
	while((! angle_achieved) && (i < max_iterations))
	{
		myDriveTrain.ArcadeDrive(AUTO_POWER, X); //Drive forward at a power of 0.6 and a turn of either -30 or 30 degrees
		frc::Wait(0.025);

		//Check if robot has achieved desired angle
		heading = gyro.GetAngle(); //Find the angle the robot is curretly at.
		if(heading > 180)
		{
			heading = heading - 360; //If robot becomes overcompensated, find the terminal angle for the current angle and turn there.
		}

		if (angle < 0)
		{
			if(heading <= angle)
			{
				angle_achieved = true;
			}
		}
		else
		{
			if(heading >= angle)
			{
				angle_achieved = true;
			}
		}

		i++; //Increase the iteration
	}
}
