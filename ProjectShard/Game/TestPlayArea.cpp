#include "TestPlayArea.h"

TestPlayArea::TestPlayArea()
	: testText(900.0f, 600.0f)
{
	// Set OpenGL options
	/*glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
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
}

void TestPlayArea::RenderScene(GLsizei screenWidth, GLsizei screenHeight)
{
	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

	Matrix4 projection = Matrix4();
	projection = projection.perspectiveProjection(player.camera.zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 1000.0f);
	Matrix4 view = player.camera.GetViewMatrix();
	Matrix4 model = Matrix4();
	Matrix4 translate = Matrix4();
	Matrix4 scale = Matrix4();

	glDisable(GL_BLEND);
	glDisable(GL_STENCIL_TEST);
	model = Matrix4();
	translate = Matrix4();
	translate = translate.translate(Vector3(7.5f, 3.0f, -50.0f));
	scale = Matrix4();
	scale = scale.scale(Vector3(7.0f, 7.0f, 7.0f));
	Matrix4 rotate = Matrix4();
	model = scale * translate;
	sceneObjects->Use();
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "model"), 1, GL_FALSE, &model.data[0]);
	block->Draw(*sceneObjects);

	skybox.Render(player.camera, screenWidth, screenHeight);

	player.Render(screenWidth, screenHeight);
	racingTrack.RenderSceneObjects(player.camera, screenWidth, screenHeight);

	// Draw Floor
	glEnable(GL_BLEND);//map_Kd Building_Side.png
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);
	glClear(GL_STENCIL_BUFFER_BIT);
	racingTrack.RenderTrack(player.camera, screenWidth, screenHeight);

	// Draw cube reflection
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDepthMask(GL_TRUE);

	model = Matrix4();
	translate = Matrix4();
	translate = translate.translate(Vector3(7.5f, -9.0f, -50.0f));
	scale = Matrix4();
	scale = scale.scale(Vector3(7.0f, 7.0f, 7.0f));
	model = scale * translate;
	sceneObjects->Use();
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "model"), 1, GL_FALSE, &model.data[0]);
	block->Draw(*sceneObjects);

	player.Reflection(screenWidth, screenHeight);
	racingTrack.RenderTrackReflection(player.camera, screenWidth, screenHeight);

	glDisable(GL_STENCIL_TEST);

	//testText.RenderText("ProjectShard", Vector2(0.0f, 0.0f), 1.0f, Vector3(0.0f, 0.0f, 0.0f), screenWidth, screenHeight);
	//testText.RenderText("Test font rendering, 1, 2, 3, 4, 5, # # #  { } /// - +", Vector2(25.0f, 570.0f), 0.5f, Vector3(0.0, 0.0f, 0.0f), screenWidth, screenHeight);
}