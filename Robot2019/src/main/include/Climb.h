// Author: Team 3229 Programming Subteam

#ifndef CLIMB_H
#define CLIMB_H

#include "Debug.h"

#include <iostream>
#include "frc/WPILib.h"
#include <frc/Timer.h>

class Climb
{
public:
    Climb();
    ~Climb();
    void MoveFront(bool direction);
    void MoveBack(bool direction);
    void ControlComp();

private:
    // Solenoids
    frc::Solenoid frontLeft {FRONT_LEFT_ID};               
    frc::Solenoid frontRight {FRONT_RIGHT_ID};
    frc::Solenoid backLeft {BACK_LEFT_ID};
    frc::Solenoid backRight {BACK_RIGHT_ID};

    // Compressor(s)
    frc::Compressor * comp;

    frc::Timer timer{}; // not used

    // ports
    const int FRONT_LEFT_ID = 0;
    const int FRONT_RIGHT_ID = 1;
    const int BACK_LEFT_ID = 2;
    const int BACK_RIGHT_ID = 3;

    const int COMP_ID = 0;
    bool m_pressureSwitch = false;

};

#endif // CLIMB_H