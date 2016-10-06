#include "TestPlayArea.h"

TestPlayArea::TestPlayArea()
	: testText(900.0f, 600.0f)
{
	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

TestPlayArea::~TestPlayArea()
{
	delete sceneObjects;
	floorTexture->DeleteTexture();
	delete floorTexture;
}

void TestPlayArea::InitalizeScene()
{
	sceneObjects = g_resourceMgr.GetShader(SID("EnviromentObject"));
	sceneObjects->Use();
	glUniform1i(glGetUniformLocation(sceneObjects->Program, "diffuseTexture"), 0);

	testText.Load("Resources/Fonts/arial.ttf");
	floorTexture = g_resourceMgr.GetTexture(SID("FloorTexture"));

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
	Matrix4 projection = Matrix4();
	projection = projection.perspectiveProjection(player.camera.zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 1000.0f);
	Matrix4 view = player.camera.GetViewMatrix();
	Matrix4 model = Matrix4();
	Matrix4 translate = Matrix4();
	Matrix4 scale = Matrix4();
	translate = translate.translate(Vector3(0.0f, -4.0f, 0.0f));
	scale = scale.scale(Vector3(150.0f, 1.0f, 150.0f));
	model = scale * translate;
	sceneObjects->Use();
	glActiveTexture(GL_TEXTURE0);
	floorTexture->Bind();
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "model"), 1, GL_FALSE, &model.data[0]);
	primitives.RenderCube();
	floorTexture->UnBind();

	model = Matrix4();
	translate = Matrix4();
	translate = translate.translate(Vector3(0.0f, 2.0f, 0.0f));
	scale = Matrix4();
	scale = scale.scale(Vector3(15.0f, 15.0f, 15.0f));
	model = scale * translate;
	glActiveTexture(GL_TEXTURE0);
	floorTexture->Bind();
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "model"), 1, GL_FALSE, &model.data[0]);
	primitives.RenderCube();
	floorTexture->UnBind();

	player.Render(screenWidth, screenHeight);

	//testText.RenderText("ProjectShard", Vector2(0.0f, 0.0f), 1.0f, Vector3(0.0f, 0.0f, 0.0f), screenWidth, screenHeight);
	//testText.RenderText("Test font rendering, 1, 2, 3, 4, 5, # # #  { } /// - +", Vector2(25.0f, 570.0f), 0.5f, Vector3(0.0, 0.0f, 0.0f), screenWidth, screenHeight);
}