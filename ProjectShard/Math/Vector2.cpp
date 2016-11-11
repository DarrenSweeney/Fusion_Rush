#include "Vector2.h"

Vector2::Vector2()
	: x(0), y(0) {}

Vector2::Vector2(float _x, float _y)
	: x(_x), y(_y) {}

Vector2 Vector2::operator-(Vector2 &vec2)
{
	return Vector2(x - vec2.x, y - vec2.y);
}

Vector2 Vector2::operator-=(Vector2 &vec2)
{
	x -= vec2.x;
	y -= vec2.y;

	return *this;
}

Vector2 Vector2::operator+(Vector2 &vec2)
{
	return Vector2(x + vec2.x, y + vec2.y);
}

Vector2 Vector2::operator+=(Vector2 &vec2)
{
	x += vec2.x;
	y += vec2.y;

	return *this;
}