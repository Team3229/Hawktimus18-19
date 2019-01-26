// Author: Team 3229 Programming Subteam

#include "Climb.h"

Climb::Climb() 
{
    comp = new frc::Compressor(COMP_ID);
    comp->SetClosedLoopControl(true);
}

Climb::~Climb() 
{
    delete comp;
}

void Climb::MoveFront(bool direction) //toggle front climb
{
    if (direction == true)
    {
        //extend climb
        frontRight.Set(true);
        frontLeft.Set(true);
    }        
    else 
    {
        //retract climb
        frontRight.Set(false);
        frontLeft.Set(false);
    }
}

void Climb::MoveBack(bool direction)  //toggle back climb
{
    if (direction == true)
    {
        // extend climb
        backRight.Set(true);
        backLeft.Set(true);      
    }
    else
    {
        // retract climb
        backRight.Set(false);
        backLeft.Set(false);      
    }
}