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
    float m_xOffset;
	float m_yOffset;
    float m_targetPercent;
    float m_validObject;

public:
	Limelight();
    void GetValues();
    void FaceTarget();
    bool IsTargeting();

};

#endif // Limelight_H