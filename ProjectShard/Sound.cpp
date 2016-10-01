#include "Sound.h"

Sound::Sound()
{
	soundEngine = EngineComponents::GetSoundEngine();
}

Sound::~Sound()
{
	soundEngine = NULL;
}

void Sound::Play2D(const char *soundFileName, 
	bool playLooped,
	bool startPaused,
	bool track,
	irrklang::E_STREAM_MODE streamMode,
	bool enableSoundEffects)
{
	soundEngine->play2D(soundFileName, playLooped, startPaused, track, streamMode, enableSoundEffects);
}

void Sound::Play3D(const char* soundFileName, irrklang::vec3df pos,
	bool playLooped,
	bool startPaused,
	bool track,
	irrklang::E_STREAM_MODE streamMode,
	bool enableSoundEffects)
{
	soundEngine->play3D(soundFileName, pos, playLooped, startPaused, track, streamMode, enableSoundEffects);
}