#include "MainMenu.h"

MainMenu::MainMenu()
	: defaultColor(1.0f, 1.0f, 1.0f), selectColor(0.4f, 0.4f, 1.0f)
{
	playLabel.position = Vector2(40.0f, 400.0f);
	playLabel.color = selectColor;
	playLabel.text = "Play Game";

	signInOutLabel.position = Vector2(40.0f, 350.0f);
	signInOutLabel.color = defaultColor;
	signInOutLabel.text = "Sign In";

	exitLabel.position = Vector2(40.0f, 300.0f);
	exitLabel.color = defaultColor;
	exitLabel.text = "Exit Game";

	exitAsk.color = defaultColor;
	exitAsk.text = "Exit?";
	exitNo.color = selectColor;
	exitNo.text = "No";
	exitNo.scale = 0.8f;
	exitYes.color = defaultColor;
	exitYes.text = "Yes";
	exitYes.scale = 0.8f;

	worldRankLabel.position = Vector2(20.0f, 60.0f);
	worldRankLabel.text = "World Rank: NA";
	worldRankLabel.color = defaultColor;
	worldRankLabel.scale = 0.5f;

	currentPlayer.position = Vector2(80.0f, 15.0f);
	currentPlayer.text = "-";
	currentPlayer.color = defaultColor;
	currentPlayer.scale = 0.5f;

	leaderboardTitle.position = Vector2(500.0f, 500.0f);
	leaderboardTitle.text = "World Top 10";
	leaderboardTitle.color = defaultColor;
	leaderboardTitle.scale = 0.7f;

	serverStatus.position = Vector2(700, 10);
	serverStatus.color = Vector3(1.0f, 0.0f, 0.0f);
	serverStatus.scale = 0.7f;
	serverStatus.text = "Offline";

	usernameText.color = defaultColor;
	usernameText.scale = 0.8f;
	usernameText.text = "Username";
	passwordText.color = defaultColor;
	passwordText.scale = 0.8f;
	passwordText.text = "Password";
	loginLabel.color = defaultColor;
	loginLabel.text = "Login";
	loginLabel.scale = 0.6f;
	cancelLabel.color = defaultColor;
	cancelLabel.text = "Cancel";
	cancelLabel.scale = 0.6f;
	noAccountLabel.color = defaultColor;
	noAccountLabel.text = "No account?";
	noAccountLabel.scale  = 0.6f;

	selectPosition = playLabel.position;

	UI_Shader = g_resourceMgr.GetShader(SID("UI_Shader"));
	UI_Bottom = g_resourceMgr.GetTexture(SID("Bottom_UI"));
	UI_Pannal = g_resourceMgr.GetTexture(SID("Menu_UI"));
	UI_Enter = g_resourceMgr.GetTexture(SID("Enter_UI"));

	spriteRenderer = new SpriteRenderer();
}

MainMenu::~MainMenu()
{
	delete UI_Shader;
	delete UI_Bottom;
	delete UI_Pannal;
	delete spriteRenderer;
}

void MainMenu::InitScene()
{
	textRenderer.Load("Resources/Fonts/arial.ttf");

	playLabel.rect.SetRectangle(playLabel.position, 30, 10);
	signInOutLabel.rect.SetRectangle(signInOutLabel.position, 30, 10);
	exitLabel.rect.SetRectangle(exitLabel.position, 30, 10);
	selectRect.SetRectangle(selectPosition, 50, 50);
}

void MainMenu::UpdateScene(float delatTime, GLsizei screenWidth, GLsizei screenHeight)
{
	gameSparksInfo.Update();

	if (gameSparksInfo.GetStatus())
	{
		serverStatus.text = "Online";
		serverStatus.color = Vector3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		serverStatus.text = "Offline";
		serverStatus.color = Vector3(1.0f, 0.0f, 0.0f);
	}

	selectRect.SetRectangle(selectPosition, 200, 50);

	switch (currentMenuState)
	{
		case MenuState::MenuOpitions:
		{
			if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_UP) && selectPosition.y != playLabel.position.y)
				selectPosition.y += 50.0f;
			else if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_DOWN) && selectPosition.y != exitLabel.position.y)
				selectPosition.y -= 50.0f;

			UpdateLable(playLabel);
			if (playLabel.labelSelected)
			{
				currentSelectState = SelectState::PlaySelected;
				playGame = true;
				playLabel.labelSelected = false;
			}
			else
				playGame = false;
			UpdateLable(signInOutLabel);
			if (signInOutLabel.labelSelected)
			{
				currentSelectState = SelectState::SignInOutSeleted;
				currentMenuState = MenuState::SignInOpitions;
				selectPosition = signInOutPannelPos + Vector2(0.0f, 50.0f);
				// Clear the data fields
				signInUserName.clear();
				signInPassword.clear();
				InputManager::GetInstance().keyInput.clear();
			}
			UpdateLable(exitLabel);
			if (exitLabel.labelSelected)
			{
				currentSelectState = SelectState::ExitSelected;
				currentMenuState = MenuState::ExitOpitions;
				selectPosition = exitPannelPosition;
			}

			break;
		}

		case MenuState::SignInOpitions:
		{
			usernameRect.SetRectangle(signInOutPannelPos + Vector2(30.0f, 60.0f), 200.0f, 30.0f);
			passwordRect.SetRectangle(signInOutPannelPos + Vector2(30.0f, 160.0f), 200.0f, 30.0f);

			// TODO(Darren): Grrr very messy code, will refactor at a later stage.
			loginLabel.rect.SetRectangle(Vector2(loginLabel.position.x, screenHeight - loginLabel.position.y), 30, 50);
			cancelLabel.rect.SetRectangle(Vector2(cancelLabel.position.x, screenHeight - cancelLabel.position.y), 30, 50);
			noAccountLabel.rect.SetRectangle(Vector2(noAccountLabel.position.x - 50.0f, screenHeight - (noAccountLabel.position.y - 150.0f)), 200.0f, 50);

			if (selectRect.Intersects(usernameRect))
			{
				std::string input = InputManager::GetInstance().keyInput;
				signInUserName = input;

				// NOTE(Darren): I could seperate this, duplicate. Could put with backspace check.
				if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_ENTER)
					|| InputManager::GetInstance().IsKeyPressed(GLFW_KEY_DOWN)
					|| InputManager::GetInstance().IsKeyPressed(GLFW_KEY_TAB))
				{
					InputManager::GetInstance().keyInput.clear();
					selectPosition.y += 120.0f;
				}
			}
			else if (selectRect.Intersects(passwordRect))
			{
				std::string input = InputManager::GetInstance().keyInput;
				signInPassword = input;

				if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_ENTER)
					|| InputManager::GetInstance().IsKeyPressed(GLFW_KEY_DOWN)
					|| InputManager::GetInstance().IsKeyPressed(GLFW_KEY_TAB))
				{
					InputManager::GetInstance().keyInput.clear();
					selectPosition.y += 120.0f;
				}
			}

			if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_BACKSPACE))
			{
				if (InputManager::GetInstance().keyInput.size() > 0)
					InputManager::GetInstance().keyInput.pop_back();
			}

			UpdateLable(loginLabel);
			UpdateLable(cancelLabel);
			UpdateLable(noAccountLabel);

			if (loginLabel.labelSelected)
			{
				SendSignInRequest();
				gameSparksInfo.InitGS();
			}

			if (cancelLabel.labelSelected)
			{
				currentMenuState = MenuState::MenuOpitions;
				currentSelectState = SelectState::NotSelected;
				selectPosition = signInOutLabel.position;
			}

			if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_UP) && !selectRect.Intersects(usernameRect))
				selectPosition.y -= 120.0f;
			else if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_DOWN) && !selectRect.Intersects(noAccountLabel.rect))
				selectPosition.y += 120.0f;

			if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_RIGHT) && selectRect.Intersects(loginLabel.rect))
				selectPosition.x += 150.0f;
			else if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_LEFT) && selectRect.Intersects(cancelLabel.rect))
				selectPosition.x -= 150.0f;

			break;
		}

		case MenuState::ExitOpitions:
		{
			if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_RIGHT) && selectPosition.x != exitPannelPosition.x + 150.0f)
				selectPosition.x += 150.0f;
			else if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_LEFT) && selectPosition.x != exitPannelPosition.x)
				selectPosition.x -= 150.0f;

			exitNo.rect.SetRectangle(exitNo.position, 30, 50);
			exitYes.rect.SetRectangle(exitYes.position, 30, 50);

			UpdateLable(exitNo);
			if (exitNo.labelSelected)
			{
				selectPosition = exitLabel.position;
				currentMenuState = MenuState::MenuOpitions;
				currentSelectState = SelectState::NotSelected;
			}
			UpdateLable(exitYes);
			if (exitYes.labelSelected)
			{
				exitGame = true;
			}

			break;
		}

		default:
			break;
	}

	if (gameSparksInfo.loginSuccessful)
	{
		currentUserName = gameSparksInfo.username;
		playerRank = gameSparksInfo.currentPlayerRank;
		currentPlayer.text = currentUserName.c_str();
		worldRankLabel.text = playerRank.c_str();
		gameSparksInfo.loginSuccessful = false;
	}
}

void MainMenu::SendSignInRequest()
{
	gameSparksInfo.username = signInUserName;
	gameSparksInfo.password = signInPassword;
}

void MainMenu::UpdateLable(MenuLabel &label)
{
	if (selectRect.Intersects(label.rect))
	{
		label.color = selectColor;

		if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_ENTER))
			label.labelSelected = true;
		else
			label.labelSelected = false;
	}
	else
	{
		label.color = defaultColor;
		label.labelSelected = false;
	}

	// TODO(Darren): Need to refactor main menu code, one part i could out the update
	// of the collision rect in here.
}

void MainMenu::RenderScene(GLsizei screenWidth, GLsizei screenHeight)
{
	float pannelHeight = screenHeight - playLabel.position.y;
	leaderboardUIPos = Vector2(screenWidth - 430.0f, 30.0f);
	exitPannelPosition = Vector2((screenWidth / 2) - 200.0f, (screenHeight / 2) - 70.0f);
	exitAsk.position = exitPannelPosition + Vector2(150.0f, 90.0f);
	exitNo.position = exitPannelPosition + Vector2(100.0f, 20.0f);
	exitYes.position = exitPannelPosition + Vector2(250.0f, 20.0f);
	signInOutPannelPos = Vector2((screenWidth / 2) - 200.0f, (screenHeight / 2) - 70.0f);
	usernameText.position = signInOutPannelPos + Vector2(20.0f, 90.0f);
	passwordText.position = signInOutPannelPos + Vector2(20.0f, -10.0f);
	loginLabel.position = signInOutPannelPos + Vector2(50.0f, -110.0f);
	cancelLabel.position = signInOutPannelPos + Vector2(250.0f, -110.0f);
	noAccountLabel.position = signInOutPannelPos + Vector2(100.0f, -160.0f);

	Matrix4 projection = Matrix4();
	projection = projection.orthographicProjection(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);
	UI_Shader->Use();
	glUniformMatrix4fv(glGetUniformLocation(UI_Shader->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	spriteRenderer->Render(*UI_Bottom, *UI_Shader, Vector2(0.0f, screenHeight - 100.0f), Vector2(screenWidth + 40.0f, 100.0f));
	spriteRenderer->Render(*UI_Pannal, *UI_Shader, Vector2(-5.0f, pannelHeight - 80.0f), Vector2(300.0f, 220.0f));
	spriteRenderer->Render(*UI_Pannal, *UI_Shader, leaderboardUIPos, Vector2(400.0f, 600.0f));

	if (currentSelectState == SelectState::ExitSelected)
	{
		spriteRenderer->Render(*UI_Pannal, *UI_Shader, exitPannelPosition, Vector2(400.0f, 150.0f));
	}
	if (currentSelectState == SelectState::SignInOutSeleted)
	{
		// Username
		spriteRenderer->Render(*UI_Enter, *UI_Shader, signInOutPannelPos + Vector2(30.0f, 60.0f), Vector2(350.0f, 50.0f));
		// Password
		spriteRenderer->Render(*UI_Enter, *UI_Shader, signInOutPannelPos + Vector2(30.0f, 160.0f), Vector2(350.0f, 50.0f));
		// UI pannel for password entering
		spriteRenderer->Render(*UI_Pannal, *UI_Shader, signInOutPannelPos, Vector2(400.0f, 320.0f));
	}
	leaderboardTitle.position = Vector2(screenWidth - 325.0f, screenHeight - 80.0f);

	glEnable(GL_BLEND);		
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	RenderLabel(playLabel, screenWidth, screenHeight);
	RenderLabel(signInOutLabel, screenWidth, screenHeight);
	RenderLabel(exitLabel, screenWidth, screenHeight);
	RenderLabel(worldRankLabel, screenWidth, screenHeight);
	RenderLabel(currentPlayer, screenWidth, screenHeight);
	RenderLabel(leaderboardTitle, screenWidth, screenHeight);
	RenderLeaderboardEntry(screenWidth, screenHeight);
	serverStatus.position.x = screenWidth - 110;
	RenderLabel(serverStatus, screenWidth, screenHeight);
	if (currentSelectState == SelectState::ExitSelected)
	{
		RenderLabel(exitAsk, screenWidth, screenHeight);
		RenderLabel(exitNo, screenWidth, screenHeight);
		RenderLabel(exitYes, screenWidth, screenHeight);
	}
	if (currentSelectState == SelectState::SignInOutSeleted)
	{
		RenderLabel(usernameText, screenWidth, screenHeight);
		RenderLabel(passwordText, screenWidth, screenHeight);
		RenderLabel(loginLabel, screenWidth, screenHeight);
		RenderLabel(cancelLabel, screenWidth, screenHeight);
		RenderLabel(noAccountLabel, screenWidth, screenHeight);
	}

	if (currentSelectState == SelectState::SignInOutSeleted)
	{
		textRenderer.RenderText(signInUserName.c_str(), signInOutPannelPos + Vector2(40.0f, 45.0f),  0.8f, Vector3(1.0f, 1.0f, 1.0f), screenWidth, screenHeight);
		textRenderer.RenderText(signInPassword.c_str(), signInOutPannelPos + Vector2(40.0f, -60.0f), 0.8f, Vector3(1.0f, 1.0f, 1.0f), screenWidth, screenHeight);
	}

	glDisable(GL_BLEND);
}

void MainMenu::RenderLeaderboardEntry(GLsizei screenWidth, GLsizei screenHeight)
{
	int index = 0;
	float firstEntryHeight = (screenHeight - leaderboardUIPos.y) - 120.0f;
	float firstEntryWidth = (screenWidth - leaderboardUIPos.x) + 10.0f;

	for (std::vector<LeaderboardEntry>::iterator it = gameSparksInfo.leaderboardEntry.begin();
		it != gameSparksInfo.leaderboardEntry.end(); it++, index++)
	{
		std::ostringstream oss;
		oss << it->rank.GetValue();
		textRenderer.RenderText(oss.str(), Vector2(leaderboardUIPos.x + 10.0f, firstEntryHeight + (-50 * index)), 0.6f, defaultColor, screenWidth, screenHeight);
		textRenderer.RenderText(it->username.GetValue().c_str(), Vector2(leaderboardUIPos.x + 80.0f, firstEntryHeight + (-50 * index)), 0.6f, defaultColor, screenWidth, screenHeight);
		oss.str("");
		oss << it->time.GetValue();
		textRenderer.RenderText(oss.str(), Vector2(leaderboardUIPos.x + 350.0f, firstEntryHeight + (-50 * index)), 0.6f, defaultColor, screenWidth, screenHeight);
	}
}

void MainMenu::RenderLabel(MenuText &menuLable, GLsizei screenWidth, GLsizei sceenHeight)
{
	textRenderer.RenderText(menuLable.text, menuLable.position, menuLable.scale, menuLable.color, screenWidth, sceenHeight);
}