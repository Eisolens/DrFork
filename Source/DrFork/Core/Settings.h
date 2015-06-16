#pragma once

class Settings;
static Settings* SettingsReference = nullptr;

const static float DefaultSpeed = 0.9f;
const static int DefaultVirusCount = 4;

class DRFORK_API Settings
{
public:
	float Speed;
	int VirusCount;

	static Settings* Get(){ if (SettingsReference == nullptr) SettingsReference = new Settings(); return SettingsReference; };
	void IncreaseComplexity();
	float GetUnControlledSpeed(){ return Speed * 0.7f; };
	void Reset();

	Settings();
	~Settings();
};
