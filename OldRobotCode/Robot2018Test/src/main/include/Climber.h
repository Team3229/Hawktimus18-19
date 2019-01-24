/*
 * File:		Climber.h
 * Author:		Programming Subteam
 * Team:		Hawktimus Prime - 3229
 *
 * File Description:
 * Header file for Climber.cpp
 */

#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_

#include <iostream>
#include <memory>
#include <string>
#include <Spark.h>

class Climber
{
public:
	Climber();
	void Stop();
	void Climb();

	~Climber()
	{
		delete myClimber;
	}

private:
	frc::Spark * myClimber;

	const double CLIMBER_POWER = -1.0; //More effective going backwards
	const int CLIMBER_PWM = 1;
};

#endif /* SRC_CLIMBER_H_ */
