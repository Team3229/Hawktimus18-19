// Author: Team 3229 Programming Subteam

#ifndef LIMELIGHT_H
#define LIMELIGHT_H

#include "DriveSystem.h"
#include "Debug.h"

#include <iostream>
#include "frc/WPILib.h"
#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

class Limelight
{
public:
    Limelight(DriveSystem * chassis);
    ~Limelight();
    void GetValues();
    bool IsTargeting();
    void SeekTarget();  

private:
    DriveSystem * visionChassis;
   
    float m_validObject; // yes/no is there a target on screen "tv"
    float m_xOffset; // x angle offset from target "tx"
	float m_yOffset; // y "ty"
    float m_targetDistance; // % of screen filled by current target "ta"
    
    //threshholds and desires
    const float ANGLE_RANGE = 2.0;
    const float DESIRED_ANGLE = 0.0;
    const float DESIRED_DISTANCE = 0.41; // 5'
    const float DISTANCE_THRESH = 0.05;

    // drive powers
    double m_stillPow = 0.0;
    double m_frdAdjPow = 1.0;
    double m_bckAdjPow = -1.0;
    double m_leftAdjPow = -1.0;
    double m_rightAdjPow = 1.0;

};

#endif // LIMELIGHT_H