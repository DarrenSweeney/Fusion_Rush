#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "..\Renderer\Text.h"
#include "..\Core\ResourceManager.h"
#include "..\Renderer\Model.h"
#include "..\Audio\Sound.h"
#include "..\Math\CollisionRectangle.h"
#include "..\Input\InputManager.h"
#include "..\Renderer\SpriteRenderer.h"
#include "..\GameSparksInfo.h"

struct MenuText
{
	Vector3 color;
	Vector2 position;
	const char* text;
	float scale = 1.0f;
};

struct MenuLabel : MenuText
{
	CollisionRectangle rect;
	bool labelSelected;
};

class MainMenu
{
private:
	GameSparksInfo gameSparksInfo;

	Text textRenderer;
	CollisionRectangle selectRect;
	Vector2 selectPosition;
	Vector3 defaultColor, selectColor;

	MenuLabel playLabel;
	MenuLabel signInOutLabel;
	MenuLabel exitLabel;

	MenuText worldRankLabel;
	MenuText currentPlayer;
	MenuText leaderboardTitle;
	MenuText serverStatus;

	enum class SelectState
	{
		NotSelected,
		PlaySelected,
		SignInOutSeleted,
		ExitSelected
	};
	SelectState currentSelectState = SelectState::NotSelected;

	enum class MenuState
	{
		MenuOpitions,
		SignInOpitions,
		CreateAccount,
		ExitOpitions
	};
	MenuState currentMenuState = MenuState::MenuOpitions;

	Shader *UI_Shader;
	Texture *UI_Bottom;
	Texture *UI_Pannal;
	Texture *UI_Enter;
	SpriteRenderer *spriteRenderer;
	Vector2 leaderboardUIPos;
	Vector2 exitPannelPosition;
	MenuText exitAsk;
	MenuLabel exitNo, exitYes;
	Vector2 signInOutPannelPos;
	Vector2 createAccountPannelPos;
	MenuText usernameText, passwordText;
	MenuLabel loginLabel, cancelLabel, createAccountLabel;
	CollisionRectangle usernameRect, passwordRect, reenterPasswordRec;
	std::string signInUserName, signInPassword;
	std::string currentUserName;	// NOTE(Darren): Need to implement
	std::string playerRank;			// NOTE(Darren): Need to implement

	void SendSignInRequest();
	void UpdateLable(MenuLabel &label);
	void RenderLabel(MenuText &menuLabel, GLsizei screenWidth, GLsizei sceenHeight);
	void RenderLeaderboardEntry(GLsizei screenWidth, GLsizei sceenHeight);

public:
	MainMenu();
	~MainMenu();

	bool exitGame, playGame;

	void InitScene();
	void UpdateScene(float delatTime, GLsizei screenWidth, GLsizei sceenHeight);
	void RenderScene(GLsizei screenWidth, GLsizei sceenHeight);
};

#endif