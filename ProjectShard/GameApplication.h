#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include <irrKlang\irrKlang.h>
#include "TestPlayArea.h"

class GameApplication
{
private:
	TestPlayArea *testPlayArea;

public:
	static irrklang::ISoundEngine* engine;

	GameApplication();
	~GameApplication();
	void Init();
	void Update();
	void Render(Camera &camera);
	static irrklang::ISoundEngine* GetSoundEngine();
};

#endif