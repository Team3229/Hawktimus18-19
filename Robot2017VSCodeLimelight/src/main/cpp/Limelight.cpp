#include "Limelight.h"

// connect to limelight.local:5801

Limelight::Limelight()
{
    // pasted from documentation
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    double targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0);
    double targetOffsetAngle_Vertical = table->GetNumber("ty",0.0);
    double targetArea = table->GetNumber("ta",0.0);
    double targetSkew = table->GetNumber("ts",0.0);

    //set constants
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 0);
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", 0);

}

void Limelight::GetValues()
{
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	m_xOffset = table->GetNumber("tx",0.0);
    m_yOffset = table->GetNumber("ty",0.0);
    m_targetDistance = table->GetNumber("ta",0.0);
    m_validObject = table->GetNumber("tv",0.0);

    //test
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

void Limelight::FaceTarget()
{
    /*GetValues();
    if (IsTargeting() == false)
    {
        visionChasis.Drive(0.0, -0.6);
    }
    else
    {
        visionChasis.Stop();
    }*/
}