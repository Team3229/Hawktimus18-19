// Author: Team 3229 Programming Subteam

#include "Climb.h"

Climb::Climb() 
{
    comp = new frc::Compressor(COMP_ID);
    comp->SetClosedLoopControl(true);

    front = new frc::DoubleSolenoid(FRONT_FORWARD_ID, FRONT_REVERSE_ID);
    back = new frc::DoubleSolenoid(BACK_FORWARD_ID, BACK_REVERSE_ID);

    front->ClearAllPCMStickyFaults();
    back->ClearAllPCMStickyFaults();
    front->Set(frc::DoubleSolenoid::Value::kReverse);
    back->Set(frc::DoubleSolenoid::Value::kReverse);
}

Climb::~Climb() 
{
    comp->SetClosedLoopControl(false);
    delete comp;
    delete front;
    delete back;
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
        front->Set(frc::DoubleSolenoid::Value::kForward);
        debug("Extending front poles\n");
    }        
    else 
    {
        //retract front climb
        front->Set(frc::DoubleSolenoid::Value::kReverse);
        debug("Retracting front poles\n");
    }
    debug("Front solenoid value: " << front->Get() << "\n");
}

void Climb::MoveBack(bool direction)  //toggle back climb
{
    if (direction == true)
    {
        // extend climb
        back->Set(frc::DoubleSolenoid::Value::kForward);
        debug("Extending back poles\n");
    }
    else
    {
        // retract climb
        back->Set(frc::DoubleSolenoid::Value::kReverse);
        debug("Retracting back poles\n");
    }
    debug("Back solenoid value: " << back->Get() << "\n");
}