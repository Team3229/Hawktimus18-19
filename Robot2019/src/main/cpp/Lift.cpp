// Author: Team 3229 Programming Subteam

#include "Lift.h"

//Uses 1 VictorSPX motor

Lift::Lift()
{
    liftMotor = new WPI_VictorSPX(LIFT_PORT);
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
    }
    else 
    {
        liftMotor->Set(ControlMode::PercentOutput, -LIFT_POWER); //Lifts the lift down
    }
}

void Lift::StopLift()
{
    liftMotor->Set(ControlMode::PercentOutput, HOLD_POWER); //stops lift
}



