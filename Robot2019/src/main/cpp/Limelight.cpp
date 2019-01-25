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
}

void Limelight::TestValues()
{
    std::cout << "X offset: " << m_xOffset << std::endl;
    std::cout << "Y offset: " << m_yOffset << std::endl;
    std::cout << "Distance variable: " << m_targetDistance << std::endl;
    if (IsTargeting() == true)
        std::cout << "Object found?: YES" << std::endl;
    else
        std::cout << "Object found?: NO" << std::endl; 
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
    GetValues();
    if (abs(m_xOffset) < ANGLE_RANGE)
    {
        //chasis.Stop(); // within desired range = stop
        if (abs(m_targetDistance - DESIRED_DISTANCE) < DISTANCE_THRESH) 
            visionChassis->Stop(); // inside desired zone
        else if (m_targetDistance < DESIRED_DISTANCE)
            visionChassis->Drive(m_leftAdjPow, m_stillPow, m_stillPow); // forward
        else if (m_targetDistance > DESIRED_DISTANCE)              
            visionChassis->Drive(m_rightAdjPow, m_stillPow, m_stillPow); // back
    }
    else if (m_xOffset > DESIRED_ANGLE)
        visionChassis->Drive(m_stillPow, m_rightAdjPow, m_stillPow); // right turn
    else if (m_xOffset < DESIRED_ANGLE)
        visionChassis->Drive(m_stillPow, m_leftAdjPow, m_stillPow); // left turn

}