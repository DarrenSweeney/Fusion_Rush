#ifndef TEST_PLAY_AREA_H
#define TEST_PLAY_AREA_H

#include "Shader.h"
#include "Primitives.h"
#include "Math\Matrix4x4.h"
#include "Camera.h"
#include "Texture.h"
#include "Text.h"
#include <irrKlang\irrKlang.h>
#include "DebugDrawManager.h"
#include "ResourceManager.h"
#include "Model.h"

class TestPlayArea
{
private:
	Primitives primitives;
	Texture floorTexture;
	Text testText;
	irrklang::ISoundEngine* engine;
	Model *sceneModel;
	Shader *modelShader;
	Shader *sceneObjects;

public:
	TestPlayArea();
	~TestPlayArea();

	void InitalizeScene();
	void UpdateScene();
	void RenderScene(Camera &camera);
};

#endif