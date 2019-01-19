#ifndef Limelight_H
#define Limelight_H

#include "ArcadeDrive.h"
#include <XboxController.h>

#include <iostream>
#include "WPILib.h"
#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"


class Limelight
{
private:
    ArcadeDrive * m_visionChasis;
    frc::XboxController * m_visionXbox;
   
    float m_validObject; // yes/no is there a target on screen "tv"
    float m_xOffset; // x angle offset from target "tx"
	float m_yOffset; // y "ty"
    float m_targetDistance; // % of screen filled by current target "ta"
    const float ANGLE_RANGE = 2.0;
    const float DESIRED_DISTANCE = 0.6; // not 3'
    const float DISTANCE_THRESH = 0.05;

public:
	Limelight(ArcadeDrive * chasis, frc::XboxController * xbox);
    void GetValues();
    void FaceTarget();
    bool IsTargeting();
    void SeekTarget();

};

#endif // Limelight_H