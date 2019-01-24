/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/IterativeRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

// our needed includes
#include <XboxController.h>
#include <Timer.h>
#include <Math.h>

// subsystem includes
#include "DriveSystem.h"
#include "Camera.h"
#include "Limelight.h"
#include "Lift.h"
#include "Intake.h"
#include "Climb.h"
#include "Debug.h"

class Robot : public frc::IterativeRobot {
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
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  // constants
  const XBOX_USB_DRIVER_1 = 0;
  const XBOX_USB_DRIVER_2 = 1;
  const DEAD_BAND = 0.1;

  // controller variable
  double d1_leftY, d1_leftX, d1_rightX, d2_leftY, d2_rightY;

  // objects of subsystems
  DriveSystem chassis{};
  
  frc::XboxController xbox1 {XBOX_USB_DRIVER_1}; //Chassis driver
  frc::XboxController xbox2 {XBOX_USB_DRIVER_2}; //Manipulation driver


};
