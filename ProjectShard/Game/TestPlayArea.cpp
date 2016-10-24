#include "TestPlayArea.h"

TestPlayArea::TestPlayArea()
	: testText(900.0f, 600.0f)
{
	
}

TestPlayArea::~TestPlayArea()
{
	delete sceneObjects;
	delete raceTrack;
	delete building;
	delete block;
}

void TestPlayArea::InitalizeScene()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

	sceneObjects = g_resourceMgr.GetShader(SID("EnviromentObject"));
	sceneObjects->Use();
	glUniform1i(glGetUniformLocation(sceneObjects->Program, "diffuseTexture"), 0);

	testText.Load("Resources/Fonts/arial.ttf");
	raceTrack = g_resourceMgr.GetModel(SID("RaceTrack"));
	barrier = g_resourceMgr.GetModel(SID("Barrier"));
	building = g_resourceMgr.GetModel(SID("Building"));
	block = g_resourceMgr.GetModel(SID("Block"));

	racingTrack.Init();

	//sound.soundEngine->play2D("Resources/Sounds/Bodyfall_sound_effects/BF_Short_Hard_1c.ogg");
}

void TestPlayArea::UpdateScene(float deltaTime)
{
	g_debugDrawMgr.AddLine(Vector3(-55.0f, 10.0f, -20.0f), Vector3(-5.0f, 0.5f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	g_debugDrawMgr.AddLine(Vector3(-5.0f, 0.5f, 0.0f), Vector3(-5.0f, 10.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	g_debugDrawMgr.AddCross(Vector3(0.0f, 20.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
	g_debugDrawMgr.AddCross(Vector3(10.0f, 10.0f, 10.0f), Vector3(1.0f, 1.0f, 0.0f));

	player.Update(deltaTime);

	if (racingTrack.TrackBlockCollision(player.boundingBox))
	{
		player.Spawn();
	}

	racingTrack.Update(deltaTime);
}

void TestPlayArea::RenderScene(GLsizei screenWidth, GLsizei screenHeight)
{
	glClearColor(0.4f, 0.4f, 0.15f, 1.0f);

	Matrix4 projection = player.camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = player.camera.GetViewMatrix();
	Matrix4 model = Matrix4();
	Matrix4 translate = Matrix4();
	Matrix4 scale = Matrix4();

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
	racingTrack.RenderTrackReflection(player.camera, screenWidth, screenHeight);
	glDisable(GL_STENCIL_TEST);

	//testText.RenderText("ProjectShard", Vector2(0.0f, 0.0f), 1.0f, Vector3(0.0f, 0.0f, 0.0f), screenWidth, screenHeight);
	//testText.RenderText("Test font rendering, 1, 2, 3, 4, 5, # # #  { } /// - +", Vector2(25.0f, 570.0f), 0.5f, Vector3(0.0, 0.0f, 0.0f), screenWidth, screenHeight);
}