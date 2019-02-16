/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Author: Team 3229 Programming Subteam

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() 
{
  /*
  m_chooser.SetDefaultOption("With Gyro (Field Oriented)", kDriveNameDefault);
  m_chooser.AddOption("Without Gyro (Robot Oriented)", kDriveNameCustom);
  */
  frc::SmartDashboard::PutString("Drive Mode", m_driveSelected);
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() 
{
  chassis.ResetGyro();
  debug("Sandstorm starting...\n");
}

void Robot::AutonomousPeriodic() 
{
  TeleopPeriodic(); // run teleop during sandstorm period
}

void Robot::TeleopInit() 
{
  //Needs to be removed before comp:
  chassis.ResetGyro();
  debug("TeleOp starting...\n");
}

void Robot::TeleopPeriodic()
{    
  // Puts drive mode on Dashboard
  frc::SmartDashboard::PutString("Drive Mode", m_driveSelected);

  //Update controller axis values
  d1_leftY = xbox1.GetY(frc::GenericHID::kLeftHand);
  d1_leftX = xbox1.GetX(frc::GenericHID::kLeftHand);
  d1_rightX = xbox1.GetX(frc::GenericHID::kRightHand);
  
  d2_leftY = xbox2.GetY(frc::GenericHID::kLeftHand);
  d2_rightY = xbox2.GetY(frc::GenericHID::kRightHand);

  // DRIVE
  debug("Gyro angle: " << chassis.TestGyro() << "\n");
  if(abs(d1_leftX) > DEAD_BAND || abs(d1_leftY) > DEAD_BAND || abs(d1_rightX) > DEAD_BAND )
	{
    if (m_driveWithGyro == true)
      chassis.Drive(d1_leftY, d1_leftX, d1_rightX); // drives robot with mecanum chassis + gyro
    else
      chassis.DriveWithoutGyro(d1_leftY, d1_leftX, d1_rightX); // drives mecanum without gyro
	}
	else
  {
    if (m_usingVision == false)
      chassis.Stop(); // stops driving
  }
  
  // swap robot and field orient with button
  if (xbox1.GetTriggerAxis(frc::GenericHID::kRightHand) > DEAD_BAND)
  {
    SwitchDriveMode();
    frc::Wait(0.5);
  }

  // speed changer
  if (xbox1.GetAButton())
    chassis.ChangeSpeed(2); // normal speed

  if (xbox1.GetBButton())
    chassis.ChangeSpeed(1); // slow speed

  if (xbox1.GetXButton())
    chassis.ChangeSpeed(3); // fast

  // PNEUMATICS
  // climber
  air.ControlComp();
  if (xbox1.GetBumper(frc::GenericHID::kRightHand))
    air.MoveFrontClimb(); // toggle front climbing poles

  if (xbox1.GetBumper(frc::GenericHID::kLeftHand))
    air.MoveBackClimb(); // toggle back climbing poles

  // INTAKE OPERATION
  // wheels
  if (xbox2.GetTriggerAxis(frc::GenericHID::kLeftHand) > DEAD_BAND)
    intake.RunWheels(true); // wheels in
  else if (xbox2.GetTriggerAxis(frc::GenericHID::kRightHand) > DEAD_BAND)
    intake.RunWheels(false); // wheels out
  else 
    intake.StopWheels();

  // pivoting the intake
  if (abs(d2_leftY) > DEAD_BAND)
  {
    if (d2_leftY < 0)
      intake.MoveIntake(true); // pivot intake up
    else
      intake.MoveIntake(false); // pivot intake down
  }
  else 
    intake.StopIntakePivot(); // holds intake in place


  // LIMELIGHT VISION TRACKING
  // robot will stop moving when target is in desired range/orientation
  visionSystem.GetValues();
  if (xbox1.GetYButton())
  {
    m_usingVision = true;
    visionSystem.SeekTarget(); 
  }
  else
    m_usingVision = false;

  // LIFT OPERATION
  if (abs(d2_rightY) > DEAD_BAND)
  {
    if (d2_rightY < 0)
      lift.MoveLift(true); // moves lift up
    else
      lift.MoveLift(false); // moves lift down
  }
  else 
    lift.StopLift(); // holds lift in place

}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
