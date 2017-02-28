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
#include "..\Renderer\SpriteRenderer.h"
#include "GhostRacer.h"
#include "../GameSparksInfo.h"
#include <fstream>

class RacingScene
{
private:
	Shader *sceneObjects;
	Sound soundEffect;
	Sound raceSoundtrack;
	Model *raceTrack;
	Model *barrier;
	Model *building;
	Model *block;
	RacingTrack racingTrack;
	Skybox skybox;
	Texture *barUI, *arrowUI;
	Texture *currentTimeUI, *bestTimeUI, *guageSpeedUI, *guageArrowUI, *speedBoxUI;
	Shader *UI_Shader;
	SpriteRenderer *spriteRenderer;
	float raceProgress, ghostRaceProgress;
	Text *textRenderer;
	bool renderGameplayUI;
	GhostRacer ghostRacer;
	std::ifstream bestTimeFile;
	float finishedRaceTime;

public:
	RacingScene();
	~RacingScene();

	PlayerShip player;
	bool finishedRace;
	float currentTime, bestTime;
	bool startSoundTrack, stopSoundTrack;

	void InitalizeScene(GLsizei screenWidth, GLsizei screenHeight, int raceTrackSeed);
	void ResetScene();
	void UpdateScene(float deltaTime);
	void RenderScene(GLsizei screenWidth, GLsizei screenHeight);
	void SetPlayerMovement(bool move);
	void SetRenderUIState(bool renderUI);
};

#endif