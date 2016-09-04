#include "TestPlayArea.h"

TestPlayArea::TestPlayArea()
	: floorTexture("Resources/grass.jpg"), testText(900.0f, 600.0f)
{
	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	engine = irrklang::createIrrKlangDevice();
}

TestPlayArea::~TestPlayArea()
{
	engine->drop();
}

void TestPlayArea::InitalizeScene()
{
	sceneObjects.LoadShader("Shaders/EnviromentObject.vert", "Shaders/EnviromentObject.frag");
	sceneObjects.Use();
	glUniform1i(glGetUniformLocation(sceneObjects.Program, "diffuseTexture"), 0);

	testText.Load("fonts/arial.ttf");

	irrklang::vec3df position(-55.0f, 10.0f, -20.0f);
	engine->play2D("Resources/Sounds/Bodyfall_sound_effects/BF_Short_Hard_1c.ogg");
}

void TestPlayArea::UpdateScene()
{
	
}

void TestPlayArea::RenderScene(Camera &camera)
{
	Matrix4 projection = Matrix4();
	projection = projection.perspectiveProjection(camera.zoom, 900.0f / 600.0f, 0.1f, 100.0f);
	Matrix4 view = camera.GetViewMatrix();
	Matrix4 model = Matrix4();
	Matrix4 translate = Matrix4();
	Matrix4 scale = Matrix4();
	translate = translate.translate(Vector3(0.0f, 0.0f, 0.0f));
	scale = scale.scale(Vector3(50.0f, 1.0f, 50.0f));
	model = scale * translate;
	sceneObjects.Use();
	glActiveTexture(GL_TEXTURE0);
	floorTexture.Bind();
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects.Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects.Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(sceneObjects.Program, "model"), 1, GL_FALSE, &model.data[0]);
	primitives.RenderCube();

	testText.RenderText("ProjectShard", Vector2(25.0f, 25.0f), 1.0f, Vector3(0.0f, 0.0f, 0.0f));
	testText.RenderText("Play", Vector2(25.0f, 570.0f), 0.5f, Vector3(0.0, 0.0f, 0.0f));
}