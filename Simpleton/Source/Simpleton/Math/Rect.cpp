//====================================================================================================
// Filename:	Rect.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Rect.h"
#include "Math.h"
#include "../Core/Graphics.h"

Rect::Rect()
	: x(0)
	, y(0)
	, w(0)
	, h(0)
{}

//----------------------------------------------------------------------------------------------------

Rect::Rect(float _x, float _y, float _w, float _h)
	: x(_x)
	, y(_y)
	, w(_w)
	, h(_h)
{}

//----------------------------------------------------------------------------------------------------

void Rect::DebugDraw(SDL_Color color, bool fill)
{
	SDL_Rect rect = {(int)x, (int)y, (int)w, (int)h};

	SDL_SetRenderDrawBlendMode(Graphics::Renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Graphics::Renderer, color.r, color.g, color.b, color.a);
	if (fill)		
		SDL_RenderFillRect(Graphics::Renderer, &rect);
	else
		SDL_RenderDrawRect(Graphics::Renderer, &rect);
}