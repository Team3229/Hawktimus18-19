// Author: Team 3229 Programming Subteam

#include "Pneumatics.h"

Pneumatics::Pneumatics() 
{
    comp = new frc::Compressor(COMP_ID);
    comp->SetClosedLoopControl(true);

    frontClimb = new frc::DoubleSolenoid(FRONT_FORWARD_ID, FRONT_REVERSE_ID);
    backClimb = new frc::DoubleSolenoid(BACK_FORWARD_ID, BACK_REVERSE_ID);

    ejector = new frc::Solenoid(EJECTOR_ID);

    frontClimb->ClearAllPCMStickyFaults();
    backClimb->ClearAllPCMStickyFaults();
    ejector->ClearAllPCMStickyFaults();
    frontClimb->Set(frc::DoubleSolenoid::Value::kReverse);
    backClimb->Set(frc::DoubleSolenoid::Value::kReverse);
}

Pneumatics::~Pneumatics() 
{
    comp->SetClosedLoopControl(false);
    delete comp;
    delete frontClimb;
    delete backClimb;
    delete ejector;
}

void Pneumatics::ControlComp()
{
    m_pressureSwitch = comp->GetPressureSwitchValue();
    debug("Enabled: " << m_pressureSwitch << "\n");
    if (m_pressureSwitch == true)
        comp->SetClosedLoopControl(false);
    else 
        comp->SetClosedLoopControl(true);
}

void Pneumatics::MoveFrontClimb() 
{
    // Toggle front climbers
    if (m_frontToggle == true)
    {
        //extend front
        frontClimb->Set(frc::DoubleSolenoid::Value::kForward);
        debug("Extending front poles\n");
        m_frontToggle = false;
    }        
    else 
    {
        //retract front
        frontClimb->Set(frc::DoubleSolenoid::Value::kReverse);
        debug("Retracting front poles\n");
        m_frontToggle = true;
    }
    debug("Front solenoid value: " << frontClimb->Get() << "\n");
    frc::Wait(0.5);
}

void Pneumatics::MoveBackClimb()  
{
    // Toggle back climbers
    if (m_backToggle == true)
    {
        // extend back
        backClimb->Set(frc::DoubleSolenoid::Value::kForward);
        debug("Extending back poles\n");
        m_backToggle = false;
    }
    else
    {
        // retract back
        backClimb->Set(frc::DoubleSolenoid::Value::kReverse);
        debug("Retracting back poles\n");
        m_backToggle = true;
    }
    debug("Back solenoid value: " << backClimb->Get() << "\n");
    frc::Wait(0.5);
}

void Pneumatics::EjectBackPanel()
{
    debug("Ejecting back panel...\n");
    ejector->Set(true); // Ejects rear intake 
    frc::Wait(2.0);
}