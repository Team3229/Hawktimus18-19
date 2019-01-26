// Author: Team 3229 Programming Subteam

#include "Intake.h"

Intake::Intake()
{
    intakeWheels = new WPI_VictorSPX(WHEEL_PORT); //Setting intake wheel port
    intakePivot = new WPI_VictorSPX(PIVOT_PORT); //Setting intake pivot port
    intakeWheels->SetSafetyEnabled(false); 
	intakePivot->SetSafetyEnabled(false);
    intakeWheels->ClearStickyFaults(0);
	intakePivot->ClearStickyFaults(0); 
} 

Intake::~Intake()
{
    delete intakeWheels;
    delete intakePivot;
}

void Intake::RunWheels(bool direction)
{
    if (direction == true)
    {
        intakeWheels->Set(WHEEL_POWER); //Spins Intake wheels in
        //std::cout << intakeWheels->Get() << std::endl;
    }      
    else
    {
        intakeWheels->Set(-WHEEL_POWER); //Spins Intake wheels out
        //std::cout << intakeWheels->Get() << std::endl;
    }
}

void Intake::StopWheels()
{
    intakeWheels->StopMotor(); //stops wheels 
}

void Intake::MoveIntake(bool direction)
{
    if (direction == true)
       intakePivot->Set(PIVOT_POWER); //Points Intake up
    else
       intakePivot->Set(-PIVOT_POWER); //Points Inatake down
    
}
void Intake::StopIntakePivot()
{
    intakePivot->Set(HOLD_POWER);//Stops pivot
}
