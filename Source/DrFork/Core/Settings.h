#pragma once

class Settings;
static Settings* SettingsReference = nullptr;

const static float DefaultSpeed = 0.9f;
const static int DefaultVirusCount = 10;

class DRFORK_API Settings
{
	float Speed;
	int VirusCount;
public:
	float GetSpeed() const { return Speed; };
	int GetVirusCount() const { return VirusCount; };

	static Settings* Get(){ if (SettingsReference == nullptr) SettingsReference = new Settings(); return SettingsReference; };
	void IncreaseComplexity();
	float GetUnControlledSpeed() const;
	void Reset(int SpeedMultyply, int VirusMultyply);

	Settings();
};
