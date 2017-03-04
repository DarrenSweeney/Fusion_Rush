#ifndef MENU_TEXT_H
#define MENU_TEXT_H

#include "..\Math\CollisionRectangle.h"
#include "..\Math\Vector3.h"
#include "..\Math\Vector2.h"

struct MenuText
{
	Vector3 color;
	Vector2 position;
	const char* text = "";
	float scale = 1.0f;
};

struct MenuLabel : MenuText
{
	CollisionRectangle rect;
	bool labelSelected;
};

#endif