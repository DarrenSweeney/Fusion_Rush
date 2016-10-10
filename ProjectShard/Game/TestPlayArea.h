#ifndef TEST_PLAY_AREA_H
#define TEST_PLAY_AREA_H

#include "..\Renderer\Shader.h"
#include "..\Renderer\Primitives.h"
#include "..\Math\Matrix4x4.h"
#include "Camera.h"
#include "..\Renderer\Texture.h"
#include "..\Renderer\Text.h"
#include "..\Renderer\DebugDrawManager.h"
#include "..\Core\ResourceManager.h"
#include "..\Renderer\Model.h"
#include "..\Audio\Sound.h"
#include "Player.h"

class TestPlayArea
{
private:
	Primitives primitives;
	Texture *floorTexture;
	Texture *groundTexture;
	Text testText;
	Shader *sceneObjects;
	Sound sound;
	Player player;
	Model *raceTrack;
	Model *barrier;
	Model *building;

public:
	TestPlayArea();
	~TestPlayArea();

	void InitalizeScene();
	void UpdateScene(float deltaTime);
	void RenderScene(GLsizei screenWidth, GLsizei screenHeight);
};

#endif