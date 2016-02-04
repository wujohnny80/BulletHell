//====================================================================================================
// Filename:	Vector2.h
// Created by:	Johnny Wu
// Description:	Class for a 2D vector.
//====================================================================================================
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <math.h>

class Vector2
{
public:
	float x, y;

	Vector2();
	Vector2(const Vector2& rhs);
	Vector2(float _x, float _y);
	Vector2(int _x, int _y);
	~Vector2();

	bool	operator==		(const Vector2& rhs) const;
	bool	operator!=		(const Vector2& rhs) const;
	Vector2 operator-		() const;
	Vector2 operator+		(const Vector2& rhs) const;
	Vector2 operator-		(const Vector2& rhs) const;
	Vector2 operator*		(float s) const;
	Vector2 operator/		(float s) const;

	friend Vector2 operator*(float s, const Vector2& v);
	friend Vector2 operator/(float s, const Vector2& v);
	Vector2& operator+=		(const Vector2& rhs);	
	Vector2& operator-=		(const Vector2& rhs);
	Vector2& operator*=		(float s);
	Vector2& operator/=		(float s);

	float MagnitudeSqr() const	{ return (x * x) + (y * y); } 
	float Magnitude() const		{ return sqrt(MagnitudeSqr()); }
	Vector2& Normalized();
};

#endif // #ifndef _VECTOR2_H_