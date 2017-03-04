#include "FinishedMenu.h"

FinishedMenu::FinishedMenu(GLsizei screenWidth, GLsizei screenHeight)
	:	menuWidth(400.0f), menuHeight(600.0f), finishedLapTime(0.0f), personalBestTime(0.0f), worldBestTime(0.0f)
{
	spriteRenderer = new SpriteRenderer();

	menuTitle.text = "FINISHED RACE!";
	menuTitle.color = Vector3(1.0f, 1.0f, 1.0f);
	menuTitle.scale = 0.8f;

	lapTimeText.text = "Lap Time";
	lapTimeText.color = Vector3(1.0f, 1.0f, 1.0f);
	lapTimeText.scale = 0.5f;

	lapTime.color = Vector3(0.0f, 1.0f, 0.0f);
	lapTime.scale = 0.6f;

	personalBestText.text = "Personal Best Time";
	personalBestText.color = Vector3(1.0f, 1.0f, 1.0f);
	personalBestText.scale = 0.5f;

	personalBest.color = Vector3(0.0f, 1.0f, 0.0f);
	personalBest.scale = 0.6f;

	worldBestText.text = "World Best Time";
	worldBestText.color = Vector3(1.0f, 1.0f, 1.0f);
	worldBestText.scale = 0.5f;

	worldBest.color = Vector3(0.0f, 1.0f, 0.0f);
	worldBest.scale = 0.6f;

	playAgainButton.text = "Play Again";
	playAgainButton.scale = 0.6f;

	mainMenuButton.text = "Main Menu";
	mainMenuButton.scale = 0.6f;

	selectPosition = Vector2((float)screenWidth - menuWidth - 10.0f, screenHeight - 570.0f);

	raceRecordFiles.open("Race_Record.txt");
	raceRecordFiles >> personalBestTime;
	raceRecordFiles.close();
}

FinishedMenu::~FinishedMenu()
{
	delete UI_MenuPannel;
	delete spriteRenderer;
}

void FinishedMenu::Init()
{
	textRenderer.Load("Resources/Fonts/arial.ttf");

	UI_Shader = g_resourceMgr.GetShader(SID("UI_Shader"));
	UI_MenuPannel = g_resourceMgr.GetTexture(SID("Menu_UI"));

	playAgainButton.rect.SetRectangle(playAgainButton.position, 30, 10);

	if(sound.soundEngine != NULL)
		sound.soundEngine->setSoundVolume(0.2f);
}

void FinishedMenu::Update()
{
	selectRect.SetRectangle(selectPosition, 100, 50);

	playAgainButton.rect.SetRectangle(playAgainButton.position, 50, 30);
	mainMenuButton.rect.SetRectangle(mainMenuButton.position, 50, 30);

	if ((InputManager::GetInstance().IsKeyPressed(GLFW_KEY_RIGHT) || InputManager::GetInstance().IsControllerButtonPressed(XBOX360_RIGHT))
		&& !selectRect.Intersects(mainMenuButton.rect))
	{
		selectPosition.x += 100;
		sound.Play2D("Resources/Sounds/Menu/Menu_Nav.wav");
	}

	if ((InputManager::GetInstance().IsKeyPressed(GLFW_KEY_LEFT) || InputManager::GetInstance().IsControllerButtonPressed(XBOX360_LEFT))
		&& !selectRect.Intersects(playAgainButton.rect))
	{
		selectPosition.x -= 100;
		sound.Play2D("Resources/Sounds/Menu/Menu_Nav.wav");
	}

	UpdateLable(playAgainButton);
	if (playAgainButton.labelSelected)
	{
		selectedPlayAgain = true;
		sound.Play2D("Resources/Sounds/Menu/Menu_Select.wav");
	}
	UpdateLable(mainMenuButton);
	if (mainMenuButton.labelSelected)
	{
		selectedMainMenu = true;
		sound.Play2D("Resources/Sounds/Menu/Menu_Select.wav");
	}

	// Check if finished lap is the best or if there is no person best
	if (finishedLapTime < personalBestTime || (personalBestTime == 0.0f))
	{
		personalBestTime = finishedLapTime;
		WriteToFile();
	}
}

void FinishedMenu::UpdateLable(MenuLabel &label)
{
	if (selectRect.Intersects(label.rect))
	{
		label.color = Vector3(0.4f, 0.4f, 1.0f);

		if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_ENTER)
			|| InputManager::GetInstance().IsControllerButtonPressed(XBOX360_A))
		{
			label.labelSelected = true;
		}
		else
			label.labelSelected = false;
	}
	else
	{
		label.color = Vector3(1.0f, 1.0f, 1.0f);
		label.labelSelected = false;
	}
}

void FinishedMenu::Render(GLsizei screenWidth, GLsizei screenHeight)
{
	menuTitle.position = Vector2((float)screenWidth - menuWidth - 5.0f, screenHeight - 100.0f);
	lapTimeText.position = Vector2((float)screenWidth - menuWidth + 95.0f, screenHeight - 200.0f);
	lapTime.position = Vector2((float)screenWidth - menuWidth + 95.0f, screenHeight - 250.0f);
	personalBestText.position = Vector2((float)screenWidth - menuWidth + 45.0f, screenHeight - 300.0f);
	personalBest.position = Vector2((float)screenWidth - menuWidth + 95.0f, screenHeight - 350.0f);
	worldBestText.position = Vector2((float)screenWidth - menuWidth + 60.0f, screenHeight - 400.0f);
	worldBest.position = Vector2((float)screenWidth - menuWidth + 95.0f, screenHeight - 450.0f);

	stringstream ss;
	ss << finishedLapTime;
	std::string string_ = ss.str();
	lapTime.text = string_.c_str();
	ss.str("");
	ss << personalBestTime;
	std::string string_1 = ss.str();
	personalBest.text = string_1.c_str();
	ss.str("");
	ss << worldBestTime;
	std::string string_2 = ss.str();
	worldBest.text = string_2.c_str();

	// Buttons
	playAgainButton.position = Vector2((float)screenWidth - menuWidth - 10.0f, screenHeight - 570.0f);
	mainMenuButton.position = Vector2((float)screenWidth - menuWidth + 165.0f, screenHeight - 570.0f);

	Matrix4 projection = Matrix4();
	projection = projection.orthographicProjection(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);
	UI_Shader->Use();
	glUniformMatrix4fv(glGetUniformLocation(UI_Shader->Program, "projection"), 1, GL_FALSE, &projection.data[0]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	spriteRenderer->Render(*UI_MenuPannel, *UI_Shader, Vector2((float)screenWidth - menuWidth - 50.0f, 50.0f), Vector2(menuWidth, menuHeight));
	RenderLabel(menuTitle, screenWidth, screenHeight);
	RenderLabel(lapTimeText, screenWidth, screenHeight);
	RenderLabel(lapTime, screenWidth, screenHeight);
	RenderLabel(personalBestText, screenWidth, screenHeight);
	RenderLabel(personalBest, screenWidth, screenHeight);
	RenderLabel(worldBestText, screenWidth, screenHeight);
	RenderLabel(worldBest, screenWidth, screenHeight);

	// Buttons
	RenderLabel(playAgainButton, screenWidth, screenHeight);
	RenderLabel(mainMenuButton, screenWidth, screenHeight);
	glDisable(GL_BLEND);
}

void FinishedMenu::SetWorldRecord(float lapTime)
{
	worldBestTime = lapTime;
}

void FinishedMenu::RenderLabel(MenuText &menuLable, GLsizei screenWidth, GLsizei screenHeight)
{
	textRenderer.RenderText(menuLable.text, menuLable.position, menuLable.scale, menuLable.color, screenWidth, screenHeight);
}

void FinishedMenu::WriteToFile()
{
	raceRecordFiles.open("Race_Record.txt");
	raceRecordFiles << personalBestTime;
	raceRecordFiles.close();
}