// Author: Team 3229 Programming Subteam

#include "Intake.h"

Intake::Intake()
{
    intakeWheels = new WPI_VictorSPX(WHEEL_PORT); //Setting intake wheel port
    intakePivot = new WPI_VictorSPX(PIVOT_PORT); //Setting intake pivot port
} 

Intake::~Intake()
{
    delete intakeWheels;
    delete intakePivot;
}

void Intake::RunWheels(bool direction)
{
    if(direction == true)
        intakeWheels->Set(ControlMode::PercentOutput, WHEEL_POWER);//Spins Intake wheels in
    else
        intakeWheels->Set(ControlMode::PercentOutput, -WHEEL_POWER); //Spins Intake wheels out
}

void Intake::StopWheels()
{
    intakeWheels->Set(ControlMode::PercentOutput, 0);//stops wheels 
}

void Intake::MoveIntake(bool direction)
{
    if(direction == true)
       intakePivot->Set(ControlMode::PercentOutput, PIVOT_POWER);//Points Intake up
    else
       intakePivot->Set(ControlMode::PercentOutput, -PIVOT_POWER); //Points Inatake down
    
}
void Intake::StopIntakePivot()
{
    intakePivot->Set(ControlMode::PercentOutput, HOLD_POWER);//Stops pivot
}
