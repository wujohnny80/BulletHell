//====================================================================================================
// Filename:	Rect.h
// Created by:	Johnny Wu
// Description:	Struct for a 2D rectangle.
//====================================================================================================
#ifndef _RECT_H_
#define _RECT_H_

#include "Line.h"
#include "SDL.h"
#include "Vector2.h"

struct Rect
{
	float x, y, w, h;

	// Constructors
	Rect();
	Rect(float x, float y, float w, float h);

	Line GetLeft() const		{ return Line(x, y, x, y + h); }
	Line GetRight() const		{ return Line(x + w, y, x + w, y + h); }
	Line GetTop() const			{ return Line(x, y, x + w, y); }
	Line GetBottom() const		{ return Line(x, y + h, x + w, y + w); }

	Vector2 Max() const			{ return Vector2(x + w, y + h); }
	Vector2 Center() const		{ return Vector2(x + w * 0.5f, y + h * 0.5f); }

	void DebugDraw(SDL_Color color, bool fill);
};

#endif // #ifndef _RECT_H_