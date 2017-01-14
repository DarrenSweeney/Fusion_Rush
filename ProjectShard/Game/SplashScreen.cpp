#include "SplashScreen.h"

SplashScreen::SplashScreen()
	: timer(0.0f), changeScene(false)
{
	engineLogo = g_resourceMgr.GetTexture(SID("Engine_Logo"));

	spriteShader = g_resourceMgr.GetShader(SID("UI_Shader"));
	spriteRenderer = new SpriteRenderer();

	sound.Play2D("Resources/Music/engine_logo_sound.wav");
}

SplashScreen::~SplashScreen()
{
	delete engineLogo;
	delete spriteRenderer;
}

/*
	May change this class to draw before uploading. Add bool to check if resource
	manager is finihed loading. Also need to add fade. Also need to refactor Main
	class into Game Application.
*/
void SplashScreen::Update(GLfloat dt)
{
	timer += dt;

	if (timer > 7.0f)
	{
		// Change scene
		changeScene = true;
		sound.soundEngine->stopAllSounds();
	}
}

void SplashScreen::Render(GLsizei screenWidth, GLsizei screenHeight)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Matrix4 projection = Matrix4();
	projection = projection.orthographicProjection(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);
	spriteShader->Use();
	glUniformMatrix4fv(glGetUniformLocation(spriteShader->Program, "projection"), 1, GL_FALSE, &projection.data[0]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	spriteRenderer->Render(*engineLogo, *spriteShader, Vector2((screenWidth / 2) - (509.0f / 2.0f), (screenHeight / 2) - (476.0f / 2.0f)), Vector2(509.0f, 476.0f));
	glDisable(GL_BLEND);
}