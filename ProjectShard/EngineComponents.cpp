#include "EngineComponents.h"

irrklang::ISoundEngine* EngineComponents::engine;

EngineComponents::EngineComponents()
{
	engine = irrklang::createIrrKlangDevice();
}

EngineComponents::~EngineComponents()
{
	engine->drop();
}

irrklang::ISoundEngine* EngineComponents::GetSoundEngine()
{
	return engine;
}