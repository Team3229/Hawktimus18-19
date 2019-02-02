// Author: Team 3229 Programming Subteam

#include "Lift.h"

//Uses 1 VictorSPX motor

Lift::Lift()
{
    liftMotor = new VictorSPX(LIFT_PORT);
    liftMotor->ClearStickyFaults(0);
}

Lift::~Lift()
{
    delete liftMotor;
}

void Lift::MoveLift(bool direction)
{
    if (direction == true)
    {
        liftMotor->Set(ControlMode::PercentOutput, LIFT_POWER); //Lifts the lift up
        debug("Lift up\n");
    }
    else 
    {
        liftMotor->Set(ControlMode::PercentOutput, -LIFT_POWER); //Lifts the lift down
        debug("Lift down\n");
    }
}

void Lift::StopLift()
{
    liftMotor->Set(ControlMode::PercentOutput, HOLD_POWER); //stops lift
}
