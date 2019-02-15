// Author: Team 3229 Programming Subteam

#include "Limelight.h"

// Connect to 10.32.29.11:5801 for control panel
// Connect to 10.32.29.11:5800 for direct camera output

Limelight::Limelight(DriveSystem * chassis)
{
    // Pasted from documentation
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    double targetOffsetAngle_Horizontal = table->GetNumber("tx", 0);
    double targetOffsetAngle_Vertical = table->GetNumber("ty", 0);
    double targetArea = table->GetNumber("ta", 0);
    double targetSkew = table->GetNumber("ts", 0);

    // Set constants
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
	m_xOffset = table->GetNumber("tx", 0);
    m_yOffset = table->GetNumber("ty", 0);
    m_targetDistance = table->GetNumber("ta", 0);
    m_validObject = table->GetNumber("tv", 0);
    m_skew = table->GetNumber("ts", 0);

    debug("X offset: " << m_xOffset << "\n");
    debug("Y offset: " << m_yOffset << "\n");
    debug("Skew angle: " << m_skew << "\n");
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
    //Replace distance setting with skew adjustment
    /*
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
    */
   if (abs(m_xOffset) < ANGLE_RANGE)
        visionChassis->Stop(); // in angle range
    else if (m_xOffset > DESIRED_ANGLE)
        visionChassis->DriveWithoutGyro(m_stillPow, m_stillPow, m_rightAdjPow); // right turn
    else if (m_xOffset < DESIRED_ANGLE)
        visionChassis->DriveWithoutGyro(m_stillPow, m_stillPow, m_leftAdjPow); // left turn
}