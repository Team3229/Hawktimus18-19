// Author: Team 3229 Programming Subteam

#include "Lift.h"

//Uses 1 VictorSPX motor

Lift::Lift()
{
    liftMotor = new VictorSPX(LIFT_PORT);
    liftMotor->ClearStickyFaults(0);

    // moving to desired location test
    liftMotor->SetSelectedSensorPosition(0, 0, 0);
}

Lift::~Lift()
{
    delete liftMotor;
}

void Lift::MoveLift(bool direction)
{
    if (limitSwitch.Get() == false) // Limit switch not pressed in
    {
        if (direction == true)
        {
            liftMotor->Set(ControlMode::PercentOutput, LIFT_POWER); //Lifts the lift up
            debug("Lift up\n");
        }
        else 
        {
            liftMotor->Set(ControlMode::PercentOutput, -LIFT_POWER); //Moves the lift down
            debug("Lift down\n");
        }
    }
    else
        StopLift(); // Limit switch pressed, max height reached
}

void Lift::StopLift()
{
    liftMotor->Set(ControlMode::PercentOutput, HOLD_POWER); //stops lift
}

void Lift::SetLiftPosition()
{
    debug("Raw sensor units: " << liftMotor->GetSelectedSensorPosition(0) << "\n");
    if (liftMotor->GetSelectedSensorPosition(0) > DESIRED_POSITION)
        MoveLift(true); // lift up
    else if (liftMotor->GetSelectedSensorPosition(0) < DESIRED_POSITION)
        MoveLift(false); // lift down
    else
        StopLift();
}