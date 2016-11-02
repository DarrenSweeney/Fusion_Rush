#ifndef TEST_PLAY_AREA_H
#define TEST_PLAY_AREA_H

#include "..\Renderer\Shader.h"
#include "..\Math\Matrix4x4.h"
#include "..\Renderer\Texture.h"
#include "..\Renderer\Text.h"
#include "..\Renderer\DebugDrawManager.h"
#include "..\Core\ResourceManager.h"
#include "..\Renderer\Model.h"
#include "..\Audio\Sound.h"
#include "Player.h"
#include "RacingTrack.h"
#include "..\Renderer\Skybox.h"
#include "TrackBlock.h"

class TestPlayArea
{
private:
	Shader *sceneObjects;
	Sound sound;
	// TODO(Darren): Rename this to player.
	Player player;
	Model *raceTrack;
	Model *barrier;
	Model *building;
	Model *block;
	RacingTrack racingTrack;
	Skybox skybox;

public:
	TestPlayArea();
	~TestPlayArea();

	void InitalizeScene();
	void UpdateScene(float deltaTime);
	void RenderScene(GLsizei screenWidth, GLsizei screenHeight);
};

#endif