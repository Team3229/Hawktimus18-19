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

    //victor testing
    intakeWheels->ConfigPeakOutputForward(1);
    intakeWheels->ConfigPeakOutputReverse(-1);
} 

Intake::~Intake()
{
    delete intakeWheels;
    delete intakePivot;
}

void Intake::StopWheels()
{
    intakeWheels->StopMotor(); //stops wheels 
}

void Intake::MoveIntake(bool upOrDown)
{
    if (upOrDown == true)
       intakePivot->Set(PIVOT_POWER); //Points Intake up
    else
       intakePivot->Set(-PIVOT_POWER); //Points Inatake down
    
}

void Intake::RunWheels(bool inOrOut)
{
    if (inOrOut == true)
        intakeWheels->Set(WHEEL_POWER); //Spin wheels in
    else
        intakeWheels->Set(-WHEEL_POWER); //Spin wheels out
}

void Intake::StopIntakePivot()
{
    intakePivot->Set(HOLD_POWER);//Stops pivot
}
