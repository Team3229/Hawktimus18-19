// Author: Team 3229 Programming Subteam

#include "Limelight.h"

// connect to limelight.local:5801

Limelight::Limelight(DriveSystem * chassis)
{
    // pasted from documentation
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    double targetOffsetAngle_Horizontal = table->GetNumber("tx",m_stillPow);
    double targetOffsetAngle_Vertical = table->GetNumber("ty",m_stillPow);
    double targetArea = table->GetNumber("ta",m_stillPow);
    double targetSkew = table->GetNumber("ts",m_stillPow);

    //set constants
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 0);
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", 0);

    visionChassis = chassis;

}

Limelight::~Limelight()
{
    delete visionChassis;
}

void Limelight::GetValues()
{
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	m_xOffset = table->GetNumber("tx",m_stillPow);
    m_yOffset = table->GetNumber("ty",m_stillPow);
    m_targetDistance = table->GetNumber("ta",m_stillPow);
    m_validObject = table->GetNumber("tv",m_stillPow);
    
    debug("X offset: " << m_xOffset << "\n");
    debug("Y offset: " << m_yOffset << "\n");
    debug("Distance variable: " << m_targetDistance << "\n");
    if (IsTargeting() == true)
        debug("Object found?: YES" << "\n");
    else
        debug("Object found?: NO" << "\n"); 
}

bool Limelight::IsTargeting() 
{
	if(m_validObject > 0)
		return true;
	else
		return false;
}

void Limelight::SeekTarget()
{
    if (abs(m_xOffset) < ANGLE_RANGE)
    {
        if (abs(m_targetDistance - DESIRED_DISTANCE) < DISTANCE_THRESH) 
            visionChassis->Stop(); // inside desired zone
        else if (m_targetDistance < DESIRED_DISTANCE)
            visionChassis->DriveWithoutGyro(m_frdAdjPow, m_stillPow, m_stillPow); // forward
        else if (m_targetDistance > DESIRED_DISTANCE)              
            visionChassis->DriveWithoutGyro(m_bckAdjPow, m_stillPow, m_stillPow); // back
    }
    else if (m_xOffset > DESIRED_ANGLE)
        visionChassis->DriveWithoutGyro(m_stillPow, m_stillPow, m_rightAdjPow); // right turn
    else if (m_xOffset < DESIRED_ANGLE)
        visionChassis->DriveWithoutGyro(m_stillPow, m_stillPow, m_leftAdjPow); // left turn

}