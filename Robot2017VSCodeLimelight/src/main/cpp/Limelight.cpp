#include "Limelight.h"

// connect to limelight.local:5801

Limelight::Limelight()
{
	std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    double targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0);
    double targetOffsetAngle_Vertical = table->GetNumber("ty",0.0);
    double targetArea = table->GetNumber("ta",0.0);
    double targetSkew = table->GetNumber("ts",0.0);

    // set constants
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", LED_MODE);
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("stream", m_camMode);
}

void Limelight::GetInstance()
{
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("<variablename>",0.0);

    //read values from NetworkTables
	validObject = table->GetEntry("tv");
	xOffSet = table->GetEntry("tx");
	yOffSet = table->GetEntry("ty");
	ledMode = table->GetEntry("ledMode");
	pipeline = table->GetEntry("pipeline");
	cammode = table->GetEntry("camMode");

    //frc::SmartDashboard::PutNumber("validObject", validObject.GetDouble(-1));
	//frc::SmartDashboard::PutNumber("HorizOffset", xOffSet.GetDouble(0));

    // testing variables
    std::cout << IsTargeting();
    m_angle = GetOffsetAngle();

}

double Limelight::GetOffsetAngle()
{
    std::cout << xOffSet.GetDouble(0) << std::endl;
    return xOffSet.GetDouble(0);
}

bool Limelight::IsTargeting() {
	if(validObject.GetDouble(-1) > 0)
		return true;
	else
		return false;
}