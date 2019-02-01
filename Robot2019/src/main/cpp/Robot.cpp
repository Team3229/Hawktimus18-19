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

void Robot::RobotInit() {
  m_chooser.SetDefaultOption("With Gyro (Field Oriented)", kDriveNameDefault);
  m_chooser.AddOption("Without Gyro (Robot Oriented)", kDriveNameCustom);
  frc::SmartDashboard::PutData("Drive Mode", &m_chooser);
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() 
{
  GetDriveMode(); // gets drive mode from SmartDashboard
  debug("Sandstorm starting...\n");
}

void Robot::AutonomousPeriodic() 
{
  TeleopPeriodic(); // run teleop during sandstorm period
}

void Robot::TeleopInit() 
{
  chassis.ResetGyro();
  debug("TeleOp starting...\n");
}

void Robot::TeleopPeriodic() 
{
  //Update driving mode from SmartDashboard
  GetDriveMode();
    
  //Update controller axis values
  d1_leftY = xbox1.GetY(frc::GenericHID::kLeftHand);
  d1_leftX = xbox1.GetX(frc::GenericHID::kLeftHand);
  d1_rightX = xbox1.GetX(frc::GenericHID::kRightHand);
  
  d2_leftY = xbox2.GetY(frc::GenericHID::kLeftHand);
  d2_rightY = xbox2.GetY(frc::GenericHID::kRightHand);

  //Drive robot
  debug("Gyro angle: " << chassis.TestGyro() << "\n");
  if(abs(d1_leftX) > DEAD_BAND || abs(d1_leftY) > DEAD_BAND || abs(d1_rightX) > DEAD_BAND )
	{
    if (m_driveWithGyro == true)
      chassis.Drive(d1_leftY, d1_leftX, d1_rightX); // drives robot with mecanum chassis
    else
      chassis.DriveWithoutGyro(d1_leftY, d1_leftX, d1_rightX); // drives mecanum without gyro
	}
	else
		chassis.Stop(); // stops driving
  
  // speed changer
  if (xbox1.GetAButton())
  {
    chassis.ChangeSpeed(2); // normal speed
    debug("Normal speed\n");
  }

  if (xbox1.GetBButton())
  {
    chassis.ChangeSpeed(1); // slow speed
    debug("Slow speed\n");
  }

  if (xbox1.GetXButton())
  {
    chassis.ChangeSpeed(3); // fast
    debug("Fast speed\n");
  }

  // pneumatic climb
  climber.ControlComp();
  if (xbox1.GetBumper(frc::GenericHID::kRightHand))
  {
    climber.MoveFront(true); // extend front climbing poles
    debug("Extending front poles\n");
  }

  if (xbox1.GetTriggerAxis(frc::GenericHID::kRightHand) > DEAD_BAND)
  {
    climber.MoveFront(false); // retract climbing poles
    debug("Retracting back poles\n");
  }

  if (xbox1.GetBumper(frc::GenericHID::kLeftHand))
  {
    climber.MoveBack(true); // extend back climbing poles
    debug("Extending back poles\n");
  }

  if (xbox1.GetTriggerAxis(frc::GenericHID::kLeftHand) > DEAD_BAND)
  {
    climber.MoveBack(false); // retract back poles
    debug("Retracting back poles\n");
  }

  // intake operation
  // wheels
  if (xbox2.GetBumper(frc::GenericHID::kRightHand))
  {
    intake.RunWheels(true); // wheels in
    debug("Wheels in\n");
  }
  else if (xbox2.GetBumper(frc::GenericHID::kLeftHand))
  {
    intake.RunWheels(false); // wheels out
    debug("Wheels out\n");
  }
  else 
    intake.StopWheels();

  // pivoting the intake
  if (abs(d2_leftY) > DEAD_BAND)
  {
    if (d2_leftY > 0)
    {
      intake.MoveIntake(true); // pivot intake up
      debug("Intake up\n");
    }
    else
    {
      intake.MoveIntake(false); // pivot intake down
      debug("Intake down\n");
    }
  }
  else 
    intake.StopIntakePivot(); // holds intake in place


  // limelight vision
  if (xbox1.GetYButton())
  {
    visionSystem.TestValues(); // console out, debug handled in limelight file
    visionSystem.SeekTarget();
  }

  // lift operation
  if (abs(d2_rightY) > DEAD_BAND)
  {
    if (d2_rightY > 0)
    {
      lift.MoveLift(true); // moves lift up
      debug("Lift up\n");
    }
    else
    {
      lift.MoveLift(false); // moves lift down
      debug("Lift down\n");
    }
  }
  else 
    lift.StopLift(); // holds lift in place

}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
