#ifndef Limelight_H
#define Limelight_H

#include "frc/smartdashboard/Smartdashboard.h"
#include <iostream>
#include "WPILib.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

class Limelight
{
private:
    std::shared_ptr<nt::NetworkTableInstance> inst;
	std::shared_ptr<nt::NetworkTable> table;

    nt::NetworkTableEntry validObject;
	nt::NetworkTableEntry xOffSet;
	nt::NetworkTableEntry yOffSet;
	nt::NetworkTableEntry targetArea;
	nt::NetworkTableEntry skew;
	nt::NetworkTableEntry latency;
	nt::NetworkTableEntry ledMode;
	nt::NetworkTableEntry pipeline;
	nt::NetworkTableEntry cammode;

    double LED_MODE = 3;
	double m_camMode = 0;
	double m_angle;

public:
    Limelight();
    void GetInstance();
    double GetOffsetAngle();
    bool IsTargeting();

};

#endif // Limelight_H