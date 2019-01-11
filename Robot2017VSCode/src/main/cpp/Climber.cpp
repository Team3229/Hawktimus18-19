#include <Climber.h>

Climber::Climber()
{
	myClimber = new frc::Spark(CLIMBER_PWM);
}

void Climber::Stop()
{
	myClimber->StopMotor();
}

void Climber::Climb()
{
	//Climb
	std::cout << "Climb()" << std::endl;
	myClimber->Set(CLIMBER_POWER);
}
