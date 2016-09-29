#ifndef TEST_PLAY_AREA_H
#define TEST_PLAY_AREA_H

#include "Shader.h"
#include "Primitives.h"
#include "Math\Matrix4x4.h"
#include "Camera.h"
#include "Texture.h"
#include "Text.h"
#include "DebugDrawManager.h"
#include "ResourceManager.h"
#include "Model.h"
//#include "Sound.h"

class TestPlayArea
{
private:
	Primitives primitives;
	Texture *floorTexture;
	Text testText;
	Model *sceneModel;
	Shader *modelShader;
	Shader *sceneObjects;
	//Sound sound;

public:
	TestPlayArea();
	~TestPlayArea();

	void InitalizeScene();
	void UpdateScene();
	void RenderScene(Camera &camera);
};

#endif