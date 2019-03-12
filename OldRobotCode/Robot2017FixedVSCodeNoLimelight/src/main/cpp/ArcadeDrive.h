#ifndef SRC_ARCADEDRIVE_H_
#define SRC_ARCADEDRIVE_H_

//Standard library includes
#include <iostream>
#include <memory>
#include <string>

//Constants for driving.
#define SAFETY_TIMEOUT 0.500
#define MAX_POWER 0.8
#define AUTO_POWER 0.60
#define GYRO_GAIN 0.259
#define COMP_RATIO 0.1111
#define TURN_POWER 0.47

//Constants for port numbers and PWMs
#define GYRO_SPI_PORT 0

//FRC library includes
#include <frc/Timer.h>
#include <frc/GenericHID.h>
#include <math.h>
#include <frc/RobotDrive.h>
#include <frc/AnalogGyro.h>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/Spark.h>
#include <frc/SpeedControllerGroup.h>

class ArcadeDrive
{
public:
	ArcadeDrive();
	void ResetHeading();
	void Stop();
	void Drive(double Y, double X);
	void DriveStraight();
	void DriveTurn (int angle);

private:
	const int LEFT_FRONT_PORT = 2;
	const int LEFT_BACK_PORT = 0;
	const int RIGHT_FRONT_PORT = 3;
	const int RIGHT_BACK_PORT = 1;

	frc::Spark leftFront{LEFT_FRONT_PORT};
	frc::Spark leftBack{LEFT_BACK_PORT};
	frc::Spark rightFront{RIGHT_FRONT_PORT};
	frc::Spark rightBack{RIGHT_BACK_PORT};

	frc::SpeedControllerGroup rightWheels {rightFront, rightBack};
	frc::SpeedControllerGroup leftWheels {leftFront, leftBack};

	frc::DifferentialDrive myDriveTrain {leftWheels, rightWheels};
	frc::AnalogGyro gyro { GYRO_SPI_PORT };

};

#endif /* SRC_ARCADEDRIVE_H_ */
