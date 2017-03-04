#include "SoundEngine.h"

irrklang::ISoundEngine* SoundEngine::engine;

SoundEngine::SoundEngine()
{
	engine = irrklang::createIrrKlangDevice();
}

SoundEngine::~SoundEngine()
{
	if(engine != NULL)
		engine->drop();
}

irrklang::ISoundEngine* SoundEngine::GetSoundEngine()
{
	return engine;
}