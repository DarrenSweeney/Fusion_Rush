#include "RacingScene.h"

RacingScene::RacingScene()
	: renderGameplayUI(false), bestTime(0.000f), finishedRace(false)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

	sceneObjects = g_resourceMgr.GetShader(SID("EnviromentObject"));
	sceneObjects->Use();
	glUniform1i(glGetUniformLocation(sceneObjects->Program, "diffuseTexture"), 0);

	barUI = g_resourceMgr.GetTexture(SID("Race_Bar_UI"));
	arrowUI = g_resourceMgr.GetTexture(SID("Arrow_UI"));
	currentTimeUI = g_resourceMgr.GetTexture(SID("Current_Time_UI"));
	bestTimeUI = g_resourceMgr.GetTexture(SID("Best_Time_UI"));
	guageSpeedUI = g_resourceMgr.GetTexture(SID("Gauge_Speed_UI"));
	guageArrowUI = g_resourceMgr.GetTexture(SID("Gauge_Arrow_UI"));
	speedBoxUI = g_resourceMgr.GetTexture(SID("Speed_Box_UI"));
	UI_Shader = g_resourceMgr.GetShader(SID("UI_Shader"));
	raceTrack = g_resourceMgr.GetModel(SID("RaceTrack"));
	barrier = g_resourceMgr.GetModel(SID("Barrier"));
	building = g_resourceMgr.GetModel(SID("Building"));
	block = g_resourceMgr.GetModel(SID("Block"));

	spriteRenderer = new SpriteRenderer();
	// TODO(Darren): May have to refactor Text class.
	textRenderer = new Text();

	ghostRacer.ReadRecordedPositions();
}

RacingScene::~RacingScene()
{
	delete barUI;
	delete arrowUI;
	delete currentTimeUI;
	delete bestTimeUI;
	delete guageSpeedUI;
	delete UI_Shader;
	delete sceneObjects;
	delete raceTrack;
	delete building;
	delete block;
	delete spriteRenderer;
	delete textRenderer;
}

void RacingScene::ResetScene()
{
	ghostRacer.RestGhostRacer(); 
	currentTime = 0.0f;
}

void RacingScene::InitalizeScene(GLsizei screenWidth, GLsizei screenHeight, int raceTrackSeed)
{
	racingTrack.Init(raceTrackSeed);
	g_debugDrawMgr.Init();

	// TODO(Darren): May refactor so i'm not loading font more than once.
	textRenderer->Load("Resources/Fonts/arial.ttf");

	bestTimeFile.open("Race_Record.txt");
	bestTimeFile >> bestTime;
	bestTimeFile.close();
}

void RacingScene::UpdateScene(float deltaTime)
{
	if (startSoundTrack)
	{
		raceSoundtrack.Play2D("Resources/Music/Test_Speed_Frekas.wav");
		startSoundTrack = false;
	}

	if (stopSoundTrack)
	{
		raceSoundtrack.soundEngine->stopAllSounds();
		stopSoundTrack = false;
	}

	racingTrack.Update(deltaTime);
	player.Update(deltaTime, currentTime);
	ghostRacer.Update(currentTime);

	if (player.position.z > racingTrack.startRacePosition.z)
		player.linearVelocity.z *= -1;
	
	raceProgress = (racingTrack.finishRacePosition - racingTrack.startRacePosition).Magnitude();
	raceProgress = ((player.position.z * -1.0f) / raceProgress) * 100.0f;
	// Divide by 100.0f to fit in the range [0.0f - 1.0f] for interpolation.
	raceProgress /= 100.0f;

	ghostRaceProgress = (racingTrack.finishRacePosition - racingTrack.startRacePosition).Magnitude();
	ghostRaceProgress = ((ghostRacer.position.z * -1.0f) / ghostRaceProgress) * 100.0f;
	ghostRaceProgress /= 100.0f;

	if (racingTrack.ObstacleCollision(player.boundingBox) && !player.shipDestroyed)
	{
		player.shipDestroyed = true;
		player.linearVelocity = Vector3();
		soundEffect.Play2D("Resources/Sounds/Gameplay/Ship_Destroyed.wav");
	}

	if (player.position.z < racingTrack.finishRacePosition.z && !finishedRace)
	{
		finishedRace = true;
		finishedRaceTime = currentTime;
		soundEffect.Play2D("Resources/Sounds/Gameplay/FinishRace.wav");

		GameSparksInfo::logRaceTimeEvent = true;
		/*
			Taking out the decimal point in the float point number because game sparks
			doesn't support floating point numbers in leaderboard entries [*Sad_Face*]
			Conver back later, the exponent will always be 10^3 (1000)
		*/
		int numberToLog = currentTime * pow(10, 3);
		GameSparksInfo::logEventFinishTime = numberToLog;
		GameSparksInfo::InitGS();
	}

	if (finishedRace)
	{
		player.FinishedAnimation(deltaTime, racingTrack.finishRacePosition);

		// Check if the player beat their record and if so write a new ghost racer data to disk
		if (finishedRaceTime < bestTime || bestTime == 0.0f)
		{
			player.WriteRecordedGhostData(finishedRaceTime);
			ghostRacer.ReadRecordedPositions();
		}
	}

	if (racingTrack.BarrierCollision(player.boundingBox, player.position) && !player.shipDestroyed)
	{
		player.linearVelocity.x *= -1.0f;

		soundEffect.Play2D("Resources/Sounds/Gameplay/barrier_hit.wav");
	}

	if (player.shipSpawned)
	{
		ResetScene();
		player.shipSpawned = false;
	}

	currentTime += deltaTime;
}

void RacingScene::RenderScene(GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = player.camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = player.camera.GetViewMatrix();
	Matrix4 model = Matrix4();
	Matrix4 translate = Matrix4();
	Matrix4 scale = Matrix4();

	Matrix4 UI_projection = Matrix4();
	UI_projection = UI_projection.orthographicProjection(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);

	Vector2 startPos = Vector2(35.0f, 40.0f + (screenHeight - 100.0f));
	Vector2 endPos = Vector2(35.0f, 40.0f);
	Vector2 arrowPos = arrowPos.Lerp(startPos, endPos, raceProgress);
	Vector2 ghostArrowPos = arrowPos.Lerp(startPos, endPos, ghostRaceProgress);

	// Render gameplay assets
	glDisable(GL_BLEND);
	glDisable(GL_STENCIL_TEST);

	skybox.Render(player.camera, screenWidth, screenHeight);
	player.Render(screenWidth, screenHeight);
	racingTrack.RenderSceneObjects(player.camera, screenWidth, screenHeight);

	// Render the track floor and barriers
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);
	glClear(GL_STENCIL_BUFFER_BIT);
	racingTrack.RenderTrack(player.camera, screenWidth, screenHeight);

	// Render reflections
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDepthMask(GL_TRUE);
	player.Reflection(screenWidth, screenHeight);
	ghostRacer.Render(screenWidth, screenHeight, player.camera);
	racingTrack.RenderTrackReflection(player.camera, screenWidth, screenHeight);
	glDisable(GL_STENCIL_TEST);

	// Render UI
	if (renderGameplayUI)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		UI_Shader->Use();
		glUniformMatrix4fv(glGetUniformLocation(UI_Shader->Program, "projection"), 1, GL_FALSE, &UI_projection.data[0]);
		spriteRenderer->Render(*arrowUI, *UI_Shader, arrowPos, Vector2(15.0f, 15.0f), 0.0f, Vector3(1.0f, 0.0f, 0.0f));
		spriteRenderer->Render(*arrowUI, *UI_Shader, ghostArrowPos, Vector2(15.0f, 15.0f), 0.0f, Vector3(1.0f, 0.0f, 1.0f));
		spriteRenderer->Render(*barUI, *UI_Shader, Vector2(40.0f, 50.0f), Vector2(50.0f, screenHeight - 100.0f));
		spriteRenderer->Render(*guageSpeedUI, *UI_Shader, Vector2(screenWidth - 300.0f, screenHeight - 240.0f), Vector2(300.0f, 300.0f));
		spriteRenderer->Render(*guageArrowUI, *UI_Shader, Vector2(screenWidth - 250.0f, screenHeight - 200.0f), Vector2(200.0f, 200.0f),
			MathHelper::DegressToRadians((player.GetSpeed() / 5.0f) - 125.0f), Vector3(1.0f, 0.0f, 0.0));
		spriteRenderer->Render(*speedBoxUI, *UI_Shader, Vector2(screenWidth - 230.0f, screenHeight - 60.0f), Vector2(159.0f, 51.0f));
		std::stringstream ss;
		ss << player.linearVelocity.Magnitude();
		textRenderer->RenderText(ss.str(), Vector2(screenWidth - 210.0f, 20.0f), 0.7f, Vector3(0.0f, 0.0f, 0.0f), screenWidth, screenHeight);
		ss.str("");
		ss << currentTime;
		textRenderer->RenderText(ss.str(), Vector2(screenWidth - 210.0f, (screenHeight - 250.0f) - 80.0f), 1.0f, Vector3(1.0f, 1.0f, 1.0f), screenWidth, screenHeight);
		spriteRenderer->Render(*currentTimeUI, *UI_Shader, Vector2(screenWidth - 220.0f, 250.0f), Vector2(220.0f, 40.0f));
		ss.str("");
		ss << ghostRacer.raceTime;
		textRenderer->RenderText(ss.str(), Vector2(screenWidth - 210.0f, (screenHeight - 100.0f) - 80.0f), 1.0f, Vector3(1.0f, 1.0f, 1.0f), screenWidth, screenHeight);
		spriteRenderer->Render(*bestTimeUI, *UI_Shader, Vector2(screenWidth - 220.0f, 100.0f), Vector2(220.0f, 40.0f));
		glDisable(GL_BLEND);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
}

void RacingScene::SetPlayerMovement(bool move)
{
	player.updateMovement = move;
}

void RacingScene::SetRenderUIState(bool renderUI)
{
	renderGameplayUI = renderUI;
}