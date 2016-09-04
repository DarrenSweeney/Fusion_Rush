#ifndef TEST_PLAY_AREA_H
#define TEST_PLAY_AREA_H

#include "Shader.h"
#include "Primitives.h"
#include "Math\Matrix4x4.h"
#include "Camera.h"
#include "Texture.h"
#include "Text.h"
#include <irrKlang\irrKlang.h>

class TestPlayArea
{
private:
	Shader sceneObjects;
	Primitives primitives;
	Texture floorTexture;
	Text testText;
	irrklang::ISoundEngine* engine;

public:
	TestPlayArea();
	~TestPlayArea();

	void InitalizeScene();
	void UpdateScene();
	void RenderScene(Camera &camera);
};

#endif