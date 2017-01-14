#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include "..\Core\ResourceManager.h"
#include "..\Renderer\SpriteRenderer.h"
#include "..\Audio\Sound.h"

class SplashScreen
{
private:
	Texture *engineLogo;
	Shader *spriteShader;
	SpriteRenderer *spriteRenderer;
	GLfloat timer;
	Sound sound;

public:
	SplashScreen();
	~SplashScreen();

	bool changeScene;

	void Update(GLfloat dt);
	void Render(GLsizei screenWidth, GLsizei screenHeight);
};

#endif