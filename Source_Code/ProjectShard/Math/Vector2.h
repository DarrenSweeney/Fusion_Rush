#ifndef VECTOR_2_H
#define VECTOR_2_H

class Vector2
{
public:
	float x, y;

	Vector2();
	Vector2(float x, float y);

	Vector2 operator-(Vector2 &vec2);
	Vector2 operator-=(Vector2 &vec2);
	Vector2 operator+(Vector2 &vec2);
	Vector2 operator+=(Vector2 &vec2);

	Vector2 Lerp(Vector2 &start, Vector2 &end, float interpolator);
};

#endif