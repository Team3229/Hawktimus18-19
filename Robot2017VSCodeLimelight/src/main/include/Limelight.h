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
    float m_validObject; // yes/no is there a target on screen "tv"

    // drive train
    ArcadeDrive visionChasis{};

public:
	Limelight();
    void GetValues();
    void FaceTarget();
    bool IsTargeting();

    float m_xOffset; // x angle offset from target "tx"
	float m_yOffset; // y "ty"
    float m_targetDistance; // % of screen filled by current target "ta"
    const float ANGLE_RANGE = 2.0;
    const float DESIRED_DISTANCE = 0.87; // 3'
    const float DISTANCE_THRESH = 0.1;

};

#endif // Limelight_H