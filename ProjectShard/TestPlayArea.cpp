#include "TestPlayArea.h"

TestPlayArea::TestPlayArea()
	: floorTexture("Resources/grass.jpg")
{
	glEnable(GL_CULL_FACE);
}

TestPlayArea::~TestPlayArea()
{
	
}

void TestPlayArea::InitalizeScene()
{
	sceneObjects.LoadShader("Shaders/EnviromentObject.vert", "Shaders/EnviromentObject.frag");
	sceneObjects.Use();
	glUniform1i(glGetUniformLocation(sceneObjects.Program, "diffuseTexture"), 0);
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
}