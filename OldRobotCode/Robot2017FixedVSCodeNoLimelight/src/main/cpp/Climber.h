#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_

#include <iostream>
#include <memory>
#include <string>

#define CLIMBER_POWER 1.0
#define CLIMBER_PWM 4

#include <frc/Spark.h>

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
};

#endif /* SRC_CLIMBER_H_ */
