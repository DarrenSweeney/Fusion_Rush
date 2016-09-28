#ifndef SOUND_H
#define SOUND_H

#include <irrKlang\irrKlang.h>
#include "GameApplication.h"

#include "Sound.h"

class Sound
{
public:
	irrklang::ISoundEngine* soundEngine;

	Sound();
	~Sound();

	void Play2D(const char *soundFileName,
		bool playLooped = false,
		bool startPaused = false,
		bool track = false,
		irrklang::E_STREAM_MODE streamMode = irrklang::ESM_AUTO_DETECT,
		bool enableSoundEffects = false);

	void Play3D(const char* soundFileName, irrklang::vec3df pos,
		bool playLooped = false,
		bool startPaused = false,
		bool track = false,
		irrklang::E_STREAM_MODE streamMode = irrklang::ESM_AUTO_DETECT,
		bool enableSoundEffects = false);
};

#endif
