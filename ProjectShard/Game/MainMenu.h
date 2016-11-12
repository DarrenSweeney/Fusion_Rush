#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "..\Renderer\Text.h"
#include "..\Core\ResourceManager.h"
#include "..\Renderer\Model.h"
#include "..\Audio\Sound.h"
#include "../Math/CollisionRectangle.h"
#include "../Input/InputManager.h"
#include "..\Renderer\Sprite.h"
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
		ExitOpitions
	};
	MenuState currentMenuState = MenuState::MenuOpitions;

	Shader *UI_Shader;
	Texture *UI_Bottom;
	Texture *UI_Pannal;
	Sprite *spriteRenderer;
	Vector2 leaderboardUIPos;
	Vector2 exitPannelPosition;
	MenuText exitAsk;
	MenuLabel exitNo, exitYes;

	void UpdateLable(MenuLabel &label);
	void RenderLabel(MenuText &menuLabel, GLsizei screenWidth, GLsizei sceenHeight);
	void RenderLeaderboardEntry(GLsizei screenWidth, GLsizei sceenHeight);

public:
	MainMenu();
	~MainMenu();

	bool exitGame;

	void InitScene();
	void UpdateScene(float delatTime);
	void RenderScene(GLsizei screenWidth, GLsizei sceenHeight);
};

#endif