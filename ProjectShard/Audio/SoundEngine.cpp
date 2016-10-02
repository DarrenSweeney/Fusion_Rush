#include "SoundEngine.h"

irrklang::ISoundEngine* SoundEngine::engine;

SoundEngine::SoundEngine()
{
	engine = irrklang::createIrrKlangDevice();
}

SoundEngine::~SoundEngine()
{
	engine->drop();
}

irrklang::ISoundEngine* SoundEngine::GetSoundEngine()
{
	return engine;
}