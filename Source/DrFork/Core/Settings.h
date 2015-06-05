#pragma once

class Settings;
static Settings* SettingsReference = nullptr;

const static float DefaultSpeed = 1.1f;
const static int DefaultVirusCount = 8;

class DRFORK_API Settings
{
public:
	float Speed;
	int VirusCount;

	static Settings* Get(){ if (SettingsReference == nullptr) SettingsReference = new Settings(); return SettingsReference; };
	void IncreaseComplexity();
	void Reset();

	Settings();
	~Settings();
};
