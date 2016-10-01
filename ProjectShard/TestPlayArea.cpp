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
	delete sceneModel;
	delete modelShader;
	delete sceneObjects;
	floorTexture->DeleteTexture();
	delete floorTexture;
}

void TestPlayArea::InitalizeScene()
{
	sceneObjects = g_resourceMgr.GetShader(SID("Darren"));
	sceneObjects->Use();
	glUniform1i(glGetUniformLocation(sceneObjects->Program, "diffuseTexture"), 0);

	testText.Load("fonts/arial.ttf");
	floorTexture = g_resourceMgr.GetTexture(SID("FloorTexture"));

	//sound.soundEngine->play2D("Resources/Sounds/Bodyfall_sound_effects/BF_Short_Hard_1c.ogg");

	sceneModel = g_resourceMgr.GetModel(SID("Nanosuit"));
	modelShader = g_resourceMgr.GetShader(SID("ModelShader"));
}

void TestPlayArea::UpdateScene()
{
	g_debugDrawMgr.AddLine(Vector3(-55.0f, 10.0f, -20.0f), Vector3(-5.0f, 0.5f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	g_debugDrawMgr.AddLine(Vector3(-5.0f, 0.5f, 0.0f), Vector3(-5.0f, 10.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	g_debugDrawMgr.AddCross(Vector3(0.0f, 20.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
	g_debugDrawMgr.AddCross(Vector3(10.0f, 10.0f, 10.0f), Vector3(1.0f, 1.0f, 0.0f));
}

void TestPlayArea::RenderScene(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = Matrix4();
	projection = projection.perspectiveProjection(camera.zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);
	Matrix4 view = camera.GetViewMatrix();
	Matrix4 model = Matrix4();
	Matrix4 translate = Matrix4();
	Matrix4 scale = Matrix4();
	translate = translate.translate(Vector3(0.0f, 0.0f, 0.0f));
	scale = scale.scale(Vector3(50.0f, 1.0f, 50.0f));
	model = scale * translate;
	sceneObjects->Use();
	glActiveTexture(GL_TEXTURE0);
	floorTexture->Bind();
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects->Program, "model"), 1, GL_FALSE, &model.data[0]);
	primitives.RenderCube();
	floorTexture->UnBind();

	modelShader->Use();
	Matrix4 modelMatrix = Matrix4();
	Matrix4 modelScale = Matrix4();
	modelScale = modelScale.scale(Vector3(0.04f, 0.04f, 0.04f));
	modelMatrix = modelScale;
	glUniformMatrix4fv(glGetUniformLocation(modelShader->Program, "model"), 1, GL_FALSE, &modelMatrix.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(modelShader->Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(modelShader->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	sceneModel->Draw(*modelShader);

	modelScale = Matrix4();
	translate = Matrix4();
	translate = translate.translate(Vector3(30.0f, 0.0f, 0.0f));
	modelScale = modelScale.scale(Vector3(0.04f, 0.04f, 0.04f));
	modelMatrix = modelScale * translate;
	glUniformMatrix4fv(glGetUniformLocation(modelShader->Program, "model"), 1, GL_FALSE, &modelMatrix.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(modelShader->Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(modelShader->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	sceneModel->Draw(*modelShader);

	testText.RenderText("ProjectShard", Vector2(0.0f, 0.0f), 1.0f, Vector3(0.0f, 0.0f, 0.0f), screenWidth, screenHeight);
	testText.RenderText("Test font rendering, 1, 2, 3, 4, 5, # # #  { } /// - +", Vector2(25.0f, 570.0f), 0.5f, Vector3(0.0, 0.0f, 0.0f), screenWidth, screenHeight);
}