#pragma once
#include <iostream>
#include <stdio.h>
#include <thread>
#include "irrKlang.h"
class soundSystem
{
private:
	irrklang::ISoundEngine* engine;
	float soundVolume;
public:
	soundSystem();
	~soundSystem();
	void playSound(const char* fileName, bool _repeat);
	void incVolume();
	void decVolume();
};

