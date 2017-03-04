#ifndef COLLISION_RECTANGLE_H
#define COLLISION_RECTANGLE_H

#include "Vector2.h"

class CollisionRectangle
{
private:
	Vector2 position;
	short width, height;

public:
	CollisionRectangle();

	void SetRectangle(Vector2 &_position, short _width, short _height);
	bool Intersects(CollisionRectangle &rect);
};

#endif