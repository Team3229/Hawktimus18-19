// Author: Team 3229 Programming Subteam

#ifndef LIFT_H
#define LIFT_H

#include "Debug.h"

#include <iostream>
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
#include "ctre/phoenix/motorcontrol/can/VictorSPX.h"
#include "ctre/phoenix/motorcontrol/ControlMode.h"

class Lift
{
public:
    Lift();
    ~Lift();
    void MoveLift(bool direction); //Moves lift up and down
    void StopLift(); //Stops lift
    void SetLiftPosition();
                                
private:
    VictorSPX * liftMotor;

    // port
    const int LIFT_PORT = 5;

    // power constants
    const float LIFT_POWER = 1.0;
    const float HOLD_POWER = 0.3;

    const int DESIRED_POSITION = 1;

};

#endif // LIFT_H