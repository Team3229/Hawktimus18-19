// Author: Team 3229 Programming Subteam

#include "Climb.h"

Climb::Climb()
{
    frontLeft = new frc::Solenoid(FRONT_LEFT_ID);        
    frontRight = new frc::Solenoid(FRONT_RIGHT_ID);       
    backLeft = new frc::Solenoid(BACK_LEFT_ID);         
    backRight = new frc::Solenoid(BACK_RIGHT_ID);
}

Climb::~Climb()
{
    delete frontLeft;
    delete frontRight;
    delete backLeft;
    delete backRight;
}

void Climb::MoveFront() //toggle front climb
{
    bool toggleDirection = true;
    if (toggleDirection == true)
    {
        toggleDirection = false;
        //extend
    }
    else
    {
        toggleDirection = true;
        //retract
    }
}

void Climb::MoveBack()  //toggle back climb
{
    bool toggleDirection = true;
    if (toggleDirection == true)
    {
        toggleDirection = false;
        //extend
    }
    else
    {
        toggleDirection = true;
        //retract
    }

}