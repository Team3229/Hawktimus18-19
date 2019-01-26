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

// Comment or un-comment out the line below to disable/enable console output
#define USE_DEBUG

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString(
  //     "Auto Selector", kAutoNameDefault);
  debug("Auto selected: " << m_autoSelected << std::endl);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
  debug("Sandstorm starting..." << std::endl);
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
  TeleopPeriodic(); // run teleop during sandstorm period
}

void Robot::TeleopInit() 
{
  debug("TeleOp starting..." << std::endl);
}

void Robot::TeleopPeriodic() 
{
  //Update controller axis values
  d1_leftY = xbox1.GetY(frc::GenericHID::kLeftHand);
  d1_leftX = xbox1.GetX(frc::GenericHID::kLeftHand);
  d1_rightX = xbox1.GetX(frc::GenericHID::kRightHand);
  
  d2_leftY = xbox2.GetY(frc::GenericHID::kLeftHand);
  d2_rightY = xbox2.GetY(frc::GenericHID::kRightHand);

  //Drive robot
  debug("Gyro angle: " << chassis.TestGyro() << std::endl);
  if(abs(d1_leftX) > DEAD_BAND || abs(d1_leftY) > DEAD_BAND || abs(d1_rightX) > DEAD_BAND)
	{
		chassis.Drive(d1_leftY, d1_leftX, d1_rightX); // drives robot with mecanum chassis
	}
	else
	{
		chassis.Stop(); // stops driving
	}
  
  // speed changer
  if (xbox1.GetAButton())
  {
    chassis.ChangeSpeed(2); // normal speed
    debug("Normal speed" << std::endl);
  }

  if (xbox1.GetBButton())
  {
    chassis.ChangeSpeed(1); // slow speed
    debug("Slow speed" << std::endl);
  }

  if (xbox1.GetXButton())
  {
    chassis.ChangeSpeed(3); // fast
    debug("Fast speed" << std::endl);
  }

  // pneumatic climb
  if (xbox1.GetBumper(frc::GenericHID::kRightHand))
    climber.MoveFront(true); // extend front climbing poles

  if (xbox1.GetTriggerAxis(frc::GenericHID::kRightHand) > DEAD_BAND)
    climber.MoveFront(false); // retract climbing poles

  if (xbox1.GetBumper(frc::GenericHID::kLeftHand))
    climber.MoveBack(true); // extend back climbing poles

  if (xbox1.GetTriggerAxis(frc::GenericHID::kLeftHand) > DEAD_BAND)
    climber.MoveBack(false); // retract back poles

  // intake operation
  // wheels
  if (xbox2.GetBumper(frc::GenericHID::kRightHand))
    intake.RunWheels(true); // wheels in

  if (xbox2.GetBumper(frc::GenericHID::kLeftHand))
    intake.RunWheels(false); // wheels out
    
  // pivoting the intake
  if (abs(d2_leftY) > DEAD_BAND)
  {
    if (d2_leftY > 0)
      intake.MoveIntake(true); // pivot intake up
    else
      intake.MoveIntake(false); // pivot intake down
  }
  else 
    intake.StopIntakePivot(); // holds intake in place


  // limelight vision
  debug(visionSystem.TestValues() << std::endl);
  if (xbox1.GetBackButton())
    visionSystem.SeekTarget();

  // lift operation
  if (abs(d2_rightY) > DEAD_BAND)
  {
    if (d2_rightY > 0)
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
