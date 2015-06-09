#include "DrFork.h"
#include "Settings.h"

Settings::Settings()
{
	Speed = DefaultSpeed;
	VirusCount = DefaultVirusCount;
}

void Settings::IncreaseComplexity()
{
	Speed *= 0.5f;
	
	int minIncreaseVirusCount = 2;
	if (VirusCount * 0.1f > minIncreaseVirusCount)
		minIncreaseVirusCount = VirusCount * 0.1f;

	VirusCount += minIncreaseVirusCount;
}

void Settings::Reset()
{
	Speed = DefaultSpeed;
	VirusCount = DefaultVirusCount;
}

Settings::~Settings()
{
}
