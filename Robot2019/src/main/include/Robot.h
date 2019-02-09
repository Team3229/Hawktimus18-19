/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Author: Team 3229 Programming Subteam

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

// Our needed includes
#include <frc/XboxController.h>
#include <Math.h>

// Subsystem includes
#include "DriveSystem.h"
#include "Camera.h"
#include "Limelight.h"
#include "Lift.h"
#include "Intake.h"
#include "Pneumatics.h"
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
  // SmartDashboard setup
  frc::SendableChooser<std::string> m_chooser;
  const std::string kDriveNameDefault = "With Gyro";
  const std::string kDriveNameCustom = "Without Gyro";
  std::string m_driveSelected;

  // Constants
  const int XBOX_USB_DRIVER_1 = 0;
  const int XBOX_USB_DRIVER_2 = 1;
  const float DEAD_BAND = 0.1;

  // Controller variables
  double d1_leftY, d1_leftX, d1_rightX, d2_leftY, d2_rightY;
  bool m_driveWithGyro = true;

  // Objects of subsystems
  DriveSystem chassis{};

  Limelight visionSystem{&chassis};

  Lift lift{};

  Intake intake{};

  Pneumatics air{};
  
  frc::XboxController xbox1 {XBOX_USB_DRIVER_1}; //Chassis driver
  frc::XboxController xbox2 {XBOX_USB_DRIVER_2}; //Manipulation driver

  Camera driveCam{};

  // SmartDashobard updater
  void GetDriveMode()
  {
    m_driveSelected = m_chooser.GetSelected();
    debug("Drive mode selected: " << m_driveSelected << "\n");
    if (m_driveSelected == "With Gyro")
      m_driveWithGyro = true;
    else 
      m_driveWithGyro = false;
  }
};
