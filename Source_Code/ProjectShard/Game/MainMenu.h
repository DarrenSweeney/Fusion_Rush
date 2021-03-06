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
#include "MenuText.h"

class MainMenu
{
private:
	Sound menuSound;
	Sound menuSoundTrack;

	Text textRenderer;
	CollisionRectangle selectRect;
	Vector2 selectPosition;
	Vector3 defaultColor, selectColor;

	MenuLabel playLabel;
	MenuLabel signInOutLabel;
	MenuLabel exitLabel;

	MenuText worldRankLabel;
	MenuText currentPlayer;
	MenuText bestRecordTime;
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
	Texture *gameTitle;
	Texture *typeElement;
	Vector2 typeElementPos;
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
	std::string signInUserName, signInPassword, signInReEnterPass;
	std::string signInPassDisplay;
	std::string currentUserName, playerRank, recordTime;

	// Error
	bool passwordMatchError, accountSignInError, userNameExistsError, notOnlineError;

	void SendSignInRequest();
	void AccountCreateRequest();
	void UpdateLable(MenuLabel &label);
	void RenderLabel(MenuText &menuLabel, GLsizei screenWidth, GLsizei sceenHeight);
	void RenderLeaderboardEntry(GLsizei screenWidth, GLsizei sceenHeight);

public:
	MainMenu();
	~MainMenu();

	bool exitGame, playGame;
	bool startSoundTrack;

	void InitScene();
	void UpdateScene(float delatTime, GLsizei screenWidth, GLsizei sceenHeight);
	void RenderScene(GLsizei screenWidth, GLsizei sceenHeight);
	void PlayMenuSelect();
	void PlayMenuError();
	void PlayMenuNav();
	void PlayKeyboardEnter();
	void PlayBackspaceSound();
};

#endif