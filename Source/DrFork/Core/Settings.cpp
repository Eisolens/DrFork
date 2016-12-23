#include "DrFork.h"
#include "Settings.h"

Settings::Settings()
{
	Speed = DefaultSpeed;
	VirusCount = DefaultVirusCount;
}

void Settings::IncreaseComplexity()
{
	Speed *= 0.9f;
	
	int minIncreaseVirusCount = 3;
	if (VirusCount * 0.1f > minIncreaseVirusCount)
		minIncreaseVirusCount = VirusCount * 0.1f;

	VirusCount += minIncreaseVirusCount;
}

void Settings::Reset(int SpeedMultyply, int VirusMultyply)
{
	if (SpeedMultyply < 1) SpeedMultyply = 1;
	if (VirusMultyply < 1) VirusMultyply = 1;

	Speed = DefaultSpeed / static_cast<float>(SpeedMultyply);
	VirusCount = DefaultVirusCount * VirusMultyply;
}
float Settings::GetUnControlledSpeed() const
{ 
	const float UnControlledSpeed = Speed * 0.7f;
	const float MinimumuncontrolledSpeed = 0.9f / 5.f;

	if (UnControlledSpeed < MinimumuncontrolledSpeed)
	{
		return MinimumuncontrolledSpeed;
	}
	else
	{
		return UnControlledSpeed;
	}
};