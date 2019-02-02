// Author: Team 3229 Programming Subteam

#include "Intake.h"

Intake::Intake()
{
    intakeWheels = new VictorSPX(WHEEL_PORT); //Setting intake wheel port
    intakePivot = new VictorSPX(PIVOT_PORT); //Setting intake pivot port
    intakeWheels->ClearStickyFaults(0);
	intakePivot->ClearStickyFaults(0); 
} 

Intake::~Intake()
{
    delete intakeWheels;
    delete intakePivot;
}

void Intake::StopWheels()
{
    intakeWheels->Set(ControlMode::PercentOutput, 0); //stops wheels 
}

void Intake::MoveIntake(bool upOrDown)
{
    if (upOrDown == true)
    {
        intakePivot->Set(ControlMode::PercentOutput, PIVOT_POWER); //Points Intake up
        debug("Intake up\n");
    }
    else
    {
        intakePivot->Set(ControlMode::PercentOutput, -PIVOT_POWER); //Points Inatake down
        debug("Intake down\n");
    }
}

void Intake::RunWheels(bool inOrOut)
{
    if (inOrOut == true)
    {
        intakeWheels->Set(ControlMode::PercentOutput, WHEEL_POWER); //Spin wheels in
        debug("Wheels in\n");
    }
    else
    {
        intakeWheels->Set(ControlMode::PercentOutput, -WHEEL_POWER); //Spin wheels out
        debug("Wheels out\n");
    }
}

void Intake::StopIntakePivot()
{
    intakePivot->Set(ControlMode::PercentOutput, HOLD_POWER);//Stops pivot
}
