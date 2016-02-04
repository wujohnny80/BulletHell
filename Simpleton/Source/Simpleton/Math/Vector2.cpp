//====================================================================================================
// Filename:	Vector2.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Vector2.h"

#include <stdio.h>

Vector2::Vector2() 
	: x(0.0f)
	, y(0.0f)
{
}

Vector2::Vector2(const Vector2& rhs)
	: x(rhs.x)
	, y(rhs.y)
{
}

Vector2::Vector2(float _x, float _y)
	: x(_x)
	, y(_y)
{
}

Vector2::Vector2(int _x, int _y)
	: x((float)_x)
	, y((float)_y)
{
}

Vector2::~Vector2()
{
}

bool Vector2::operator==(const Vector2& rhs) const
{
	if ((x == rhs.x) && (y == rhs.y))
	{
		return true;
	}
	return false;
}

bool Vector2::operator!=(const Vector2& rhs) const
{
	if ((x != rhs.x) || (y != rhs.y))
	{
		return true;
	}
	return false;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(float s) const
{
	return Vector2(x * s, y * s);
}

Vector2 Vector2::operator/(float s) const
{
	if (s == 0)
		printf("Cannot divide by zero\n");
	const float inv = 1.0f / s;
	return Vector2(x * inv, y * inv);
}

Vector2 operator*(float s, const Vector2& v)
{
	return v * s;
}

Vector2 operator/(float s, const Vector2& v)
{
	return v / s;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2& Vector2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}

Vector2& Vector2::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}

Vector2& Vector2::Normalized()
{
	if (x == 0.0f && y == 0.0f)
		printf("Cannot normalize zero length vector\n");
	const float inv = 1.0f / Magnitude();
	x *= inv;
	y *= inv;
	return *this;
}