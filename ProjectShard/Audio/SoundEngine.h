#ifndef ENGINE_COMPONENTS_H
#define ENGINE_COMPONENTS_H

#include <irrKlang\irrKlang.h>

class SoundEngine
{
private:
	static irrklang::ISoundEngine* engine;

public:
	SoundEngine();
	~SoundEngine();

	static irrklang::ISoundEngine* GetSoundEngine();
};

#endif
