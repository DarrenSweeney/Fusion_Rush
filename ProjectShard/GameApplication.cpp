#include "GameApplication.h"

irrklang::ISoundEngine* GameApplication::engine;

GameApplication::GameApplication()
{
	engine = irrklang::createIrrKlangDevice();
	testPlayArea = new TestPlayArea();
}

GameApplication::~GameApplication()
{
	engine->drop();
	delete testPlayArea;
}

void GameApplication::Init()
{
	testPlayArea->InitalizeScene();
}

void GameApplication::Update()
{
	testPlayArea->UpdateScene();
}

void GameApplication::Render(Camera &camera)
{
	testPlayArea->RenderScene(camera);
}

irrklang::ISoundEngine* GameApplication::GetSoundEngine()
{
	return engine;
}