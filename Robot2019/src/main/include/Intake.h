// Author: Team 3229 Programming Subteam

#ifndef INTAKE_H
#define INTAKE_H

#include "Debug.h"

#include <iostream>
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
#include "ctre/phoenix/motorcontrol/can/VictorSPX.h"
#include "ctre/phoenix/motorcontrol/ControlMode.h"

class Intake
{
public:
    Intake();
    ~Intake();
    void RunWheels(bool inOrOut); // run intake wheels
    void MoveIntake(bool upOrDown); // pivot intake on motor
    void StopWheels();
    void StopIntakePivot();

private:
    VictorSPX * intakeWheels; // Motor for wheels on intake
    VictorSPX * intakePivot; // Motor for pivot on intake
   
    //Setting intake ports
    const int WHEEL_PORT = 7; // 7 or 8
    const int PIVOT_PORT = 6; // 6
    
    //Setting intake wheel speed
    const float WHEEL_POWER = 1.0;
    const float PIVOT_POWER = 0.2;
    const float PIVOT_HOLD_POWER = -0.1; 
    const float WHEEL_HOLD_POWER = 0.1;

};

#endif // INTAKE_H