// Author: Team 3229 Programming Subteam

#ifndef CLIMB_H
#define CLIMB_H

#include "Debug.h"

#include <iostream>
#include "frc/WPILib.h"
#include <frc/DoubleSolenoid.h>

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
    frc::DoubleSolenoid * front;

    frc::DoubleSolenoid * back;

    // Compressor(s)
    frc::Compressor * comp;

    // ports
    const int FRONT_FORWARD_ID = 0;
    const int FRONT_REVERSE_ID = 1;
    
    const int BACK_FORWARD_ID = 2;
    const int BACK_REVERSE_ID = 3;

    const int COMP_ID = 0;
    bool m_pressureSwitch = false;

};

#endif // CLIMB_H