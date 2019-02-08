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
    frc::DigitalInput topSwitch {TOP_DIO};
    frc::DigitalInput bottomSwitch {BOTTOM_DIO};

    // port
    const int LIFT_PORT = 5;
    const int TOP_DIO = 0;
    const int BOTTOM_DIO = 1;

    // power constants
    const float LIFT_POWER = 0.8;
    const float HOLD_POWER = 0.1;

    const int DESIRED_POSITION = 1;

};

#endif // LIFT_H