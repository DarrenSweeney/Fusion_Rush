#include "TestPlayArea.h"

RacingScene::RacingScene()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

	sceneObjects = g_resourceMgr.GetShader(SID("EnviromentObject"));
	sceneObjects->Use();
	glUniform1i(glGetUniformLocation(sceneObjects->Program, "diffuseTexture"), 0);

	raceTrack = g_resourceMgr.GetModel(SID("RaceTrack"));
	barrier = g_resourceMgr.GetModel(SID("Barrier"));
	building = g_resourceMgr.GetModel(SID("Building"));
	block = g_resourceMgr.GetModel(SID("Block"));
	blurShader = g_resourceMgr.GetShader(SID("BlurShader"));
}

RacingScene::~RacingScene()
{
	delete sceneObjects;
	delete raceTrack;
	delete building;
	delete block;
	delete blurShader;
}

void RacingScene::InitalizeScene(GLsizei screenWidth, GLsizei screenHeight)
{
	racingTrack.Init();
	g_debugDrawMgr.Init();

	GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
								 // Positions   // TexCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	// Setup screen VAO
	GLuint quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);

	SetUpBuffers(screenWidth, screenHeight);

	//sound.soundEngine->play2D("Resources/Sounds/Bodyfall_sound_effects/BF_Short_Hard_1c.ogg");
}

void RacingScene::SetUpBuffers(GLsizei screenWidth, GLsizei screenHeight)
{
	// Framebuffers
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// Create a color attachment texture
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RacingScene::UpdateScene(float deltaTime)
{
	g_debugDrawMgr.AddLine(Vector3(-55.0f, 10.0f, -20.0f), Vector3(-5.0f, 0.5f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	g_debugDrawMgr.AddLine(Vector3(-5.0f, 0.5f, 0.0f), Vector3(-5.0f, 10.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	g_debugDrawMgr.AddCross(Vector3(0.0f, 20.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
	g_debugDrawMgr.AddCross(Vector3(10.0f, 10.0f, 10.0f), Vector3(1.0f, 1.0f, 0.0f));

	player.Update(deltaTime);

	if (racingTrack.TrackCollision(player.boundingBox))
	{
		//player.linearVelocity = Vector3();
		player.Spawn();
	}

	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_P))
	{
		player.Spawn();
	}

	racingTrack.Update(deltaTime);
}

void RacingScene::RenderScene(GLsizei screenWidth, GLsizei screenHeight, bool windowResized)
{
	Matrix4 projection = player.camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = player.camera.GetViewMatrix();
	Matrix4 model = Matrix4();
	Matrix4 translate = Matrix4();
	Matrix4 scale = Matrix4();

	if (windowResized)
		SetUpBuffers(screenWidth, screenHeight);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Render gameplay assets
	glDisable(GL_BLEND);
	glDisable(GL_STENCIL_TEST);

	//skybox.Render(player.camera, screenWidth, screenHeight);
	player.Render(screenWidth, screenHeight);
	racingTrack.RenderSceneObjects(player.camera, screenWidth, screenHeight);

	// Render the track floor and barriers
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);
	glClear(GL_STENCIL_BUFFER_BIT);
	racingTrack.RenderTrack(player.camera, screenWidth, screenHeight);

	// Render reflections
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDepthMask(GL_TRUE);

	player.Reflection(screenWidth, screenHeight);
	racingTrack.RenderTrackReflection(player.camera, screenWidth, screenHeight);
	glDisable(GL_STENCIL_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Draw Screen
	blurShader->Use();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void RacingScene::TogglePlayerMovement()
{
	player.updateMovement = !player.updateMovement;
}