// Author: Team 3229 Programming Subteam

#include <iostream>
#include "WPILib.h"
#include <Timer.h>

class Climb
{
public:
    Climb();
    ~Climb();
    void MoveFront();
    void MoveBack();

private:
    // Solenoids
    frc::Solenoid * frontLeft;               
    frc::Solenoid * frontRight;
    frc::Solenoid * backLeft;
    frc::Solenoid * backRight;

    // Compressor(s)
    frc::Compressor placeholder{0};

    frc::Timer actuatorTimer{};

    // ports
    const int FRONT_LEFT_ID = 0;
    const int FRONT_RIGHT_ID = 1;
    const int BACK_LEFT_ID = 2;
    const int BACK_RIGHT_ID = 3;

};
