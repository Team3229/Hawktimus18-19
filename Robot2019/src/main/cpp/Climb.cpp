// Author: Team 3229 Programming Subteam

#include "Climb.h"

Climb::Climb() 
{
    comp = new frc::Compressor(COMP_ID);
    comp->SetClosedLoopControl(true);

    front.ClearAllPCMStickyFaults();
    back.ClearAllPCMStickyFaults();
    front.Set(frc::DoubleSolenoid::Value::kOff);
    back.Set(frc::DoubleSolenoid::Value::kOff);
}

Climb::~Climb() 
{
    comp->SetClosedLoopControl(false);
    delete comp;
}

void Climb::ControlComp()
{
    m_pressureSwitch = comp->GetPressureSwitchValue();
    debug("Enabled: " << m_pressureSwitch << "\n");
    if (m_pressureSwitch == true)
        comp->SetClosedLoopControl(false);
    else 
        comp->SetClosedLoopControl(true);
}

void Climb::MoveFront(bool direction) //toggle front climb
{
    if (direction == true)
    {
        //extend front climb
        front.Set(frc::DoubleSolenoid::Value::kForward);
        debug("Extending front poles\n");
    }        
    else 
    {
        //retract front climb
        front.Set(frc::DoubleSolenoid::Value::kReverse);
        debug("Retracting front poles\n");
    }
}

void Climb::MoveBack(bool direction)  //toggle back climb
{
    if (direction == true)
    {
        // extend climb
        debug("Extending back poles\n");
    }
    else
    {
        // retract climb
        debug("Retracting back poles\n");
    }
}