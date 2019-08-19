#include "soundSystem.h"

soundSystem::soundSystem()
{
	engine = irrklang::createIrrKlangDevice();
	soundVolume = 0.0f;
	engine->setSoundVolume(soundVolume);
}


soundSystem::~soundSystem()
{
	engine->drop();
}

void soundSystem::playSound(const char* fileName,bool _repeat)
{
	engine->play2D(fileName, _repeat);
	//engine->isCurrentlyPlaying;
	//engine->update();
}

void soundSystem::incVolume()
{
	soundVolume += 0.1f;
	engine->setSoundVolume(soundVolume);
}

void soundSystem::decVolume()
{
	soundVolume -= 0.1f;
	engine->setSoundVolume(soundVolume);
}
