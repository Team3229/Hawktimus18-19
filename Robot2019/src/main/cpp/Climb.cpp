// Author: Team 3229 Programming Subteam

#include "Climb.h"

Climb::Climb() 
{
    comp = new frc::Compressor(COMP_ID);
    comp->SetClosedLoopControl(true);
    timer.Reset();
}

Climb::~Climb() 
{
    delete comp;
}

void Climb::MoveFront() //toggle front climb
{
    if (m_frontToggle == true)
    {
        m_frontToggle = false;
        //extend
        frontRight.Set(true);
        frontLeft.Set(true);        
    }
    else
    {
        m_frontToggle = true;
        //retract
        frontRight.Set(false);
        frontLeft.Set(false);
    }
}

void Climb::MoveBack()  //toggle back climb
{
    if (m_backToggle == true)
    {
        m_backToggle = false;
        //extend
        backRight.Set(true);
        backLeft.Set(true);
    }
    else
    {
        m_backToggle = true;
        //retract
        backRight.Set(false);
        backLeft.Set(false);
    }
}