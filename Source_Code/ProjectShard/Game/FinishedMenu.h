#ifndef FINISHED_MENU_H
#define FINISHED_MENU_H

#include "..\Core\ResourceManager.h"
#include "..\Renderer\SpriteRenderer.h"
#include "..\Renderer\Text.h"
#include "..\Math\CollisionRectangle.h"
#include "MenuText.h"
#include "..\Input\InputManager.h"
#include "..\Audio\Sound.h"
#include <fstream>

class FinishedMenu
{
public:
	FinishedMenu(GLsizei screenWidth, GLsizei screenHeight);
	~FinishedMenu();

	bool selectedMainMenu;
	bool selectedPlayAgain;
	float finishedLapTime;
	float personalBestTime;

	void Init();
	void Update();
	void Render(GLsizei screenWidth, GLsizei screenHeight);
	void SetWorldRecord(float lapTime);

private:
	SpriteRenderer *spriteRenderer;
	Sound sound;
	Shader *UI_Shader;
	Texture *UI_MenuPannel;
	float menuWidth, menuHeight;
	Text textRenderer;
	MenuText menuTitle;
	MenuText lapTimeText, personalBestText, worldBestText;
	MenuText lapTime, personalBest, worldBest;
	MenuLabel playAgainButton, mainMenuButton;
	Vector2 selectPosition;
	CollisionRectangle selectRect;
	// Personal best time file and offline last recorded world record
	std::fstream raceRecordFiles;
	float worldBestTime;

	void UpdateLable(MenuLabel &label);
	void RenderLabel(MenuText &menuLabel, GLsizei screenWidth, GLsizei sceenHeight);
	void WriteToFile();
};

#endif