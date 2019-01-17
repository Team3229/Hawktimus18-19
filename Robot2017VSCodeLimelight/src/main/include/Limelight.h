#ifndef Limelight_H
#define Limelight_H

#include "ArcadeDrive.h"

#include <iostream>
#include "WPILib.h"
#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"


class Limelight
{
private:
    float m_targetPercent; // % of screen filled by current target
    float m_validObject; // yes/no is there a target on screen

    // drive train
    ArcadeDrive visionChasis{};

public:
	Limelight();
    void GetValues();
    void FaceTarget();
    bool IsTargeting();

    float m_xOffset; // x angle offset from target
	float m_yOffset; // y
    const float ANGLE_RANGE = 0.5;

};

#endif // Limelight_H