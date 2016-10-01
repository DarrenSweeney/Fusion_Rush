#ifndef ENGINE_COMPONENTS_H
#define ENGINE_COMPONENTS_H

#include <irrKlang\irrKlang.h>

class EngineComponents
{
private:
	static irrklang::ISoundEngine* engine;

public:
	EngineComponents();
	~EngineComponents();

	static irrklang::ISoundEngine* GetSoundEngine();
};

#endif
