// Author: Team 3229 Programming Subteam

#ifndef INTAKE_H
#define INTAKE_H

#include <iostream>
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

class Intake
{
public:
    Intake();
    ~Intake();
    void RunWheels(bool direction); // run intake wheels
    void MoveIntake(bool direction); // pivot intake on motor
    void StopWheels();
    void StopIntakePivot();

private:
    WPI_VictorSPX * intakeWheels; // Motor for wheels on intake
    WPI_VictorSPX * intakePivot; // Motor for pivot on intake
   
    //Setting intake ports
    const int WHEEL_PORT = 7; // 7 or 8
    const int PIVOT_PORT = 6; // 6
    
    //Setting intake wheel speed
    const float WHEEL_POWER = 1.0;
    const float PIVOT_POWER = 1.0;
    const float HOLD_POWER = 0.3;

};

#endif // INTAKE_H