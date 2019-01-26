// Author: Team 3229 Programming Subteam

#include "Lift.h"

//Uses 1 VictorSPX motor

Lift::Lift()
{
    liftMotor = new WPI_VictorSPX(LIFT_PORT);
    liftMotor->SetSafetyEnabled(false);
    liftMotor->ClearStickyFaults(0);
}

Lift::~Lift()
{
    delete liftMotor;
}

void Lift::MoveLift(bool direction)
{
    if (direction == true)
        liftMotor->Set(LIFT_POWER); //Lifts the lift up
    else 
        liftMotor->Set(-LIFT_POWER); //Lifts the lift down
}

void Lift::StopLift()
{
    liftMotor->Set(HOLD_POWER); //stops lift
}
