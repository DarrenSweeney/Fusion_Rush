#include "CollisionRectangle.h"

CollisionRectangle::CollisionRectangle()
	: width(0), height(0)
{

}

void CollisionRectangle::SetRectangle(Vector2 &_position, short _width, short _height)
{
	position = _position;
	width = _width;
	height = _height;
}

bool CollisionRectangle::Intersects(CollisionRectangle &rect)
{
	if (position.x < rect.position.x + rect.width &&
		position.x + width > rect.position.x &&
		position.y < rect.position.y + rect.height &&
		height + position.y > rect.position.y)
	{
		return true;
	}

	return false;
}