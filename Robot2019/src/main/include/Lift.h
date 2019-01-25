// Author: Team 3229 Programming Subteam

#include <iostream>
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

class Lift
{
public:
    Lift();
    ~Lift();
    void MoveLift(bool direction); //Moves lift up and down
    void StopLift(); //Stops lift
                                
private:
    WPI_VictorSPX * liftMotor;

    // port
    const int LIFT_PORT = 3;

    // power constants
    const float LIFT_POWER = 1.0;
    const float HOLD_POWER = 0.2;

};