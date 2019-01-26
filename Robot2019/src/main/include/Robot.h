/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Author: Team 3229 Programming Subteam

#pragma once

#include <string>

#include <frc/IterativeRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

// our needed includes
#include <frc/XboxController.h>
#include <Math.h>

// subsystem includes
#include "DriveSystem.h"
#include "Camera.h"
#include "Limelight.h"
#include "Lift.h"
#include "Intake.h"
#include "Climb.h"
#include "Debug.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kDriveNameDefault = "With Gyro";
  const std::string kDriveNameCustom = "Without Gyro";
  std::string m_driveSelected;

  // constants
  const int XBOX_USB_DRIVER_1 = 0;
  const int XBOX_USB_DRIVER_2 = 1;
  const float DEAD_BAND = 0.1;

  // controller variable
  double d1_leftY, d1_leftX, d1_rightX, d2_leftY, d2_rightY;
  bool m_driveWithGyro = true;

  // objects of subsystems
  DriveSystem chassis{};

  Limelight visionSystem{&chassis};

  Lift lift{};

  Intake intake{};

  Climb climber{};
  
  frc::XboxController xbox1 {XBOX_USB_DRIVER_1}; //Chassis driver
  frc::XboxController xbox2 {XBOX_USB_DRIVER_2}; //Manipulation driver

};
