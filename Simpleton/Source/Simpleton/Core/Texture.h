//====================================================================================================
// Filename:	Texture.h
// Created by:	Johnny Wu
// Description:	Wrapper class for a SDL_Texture
//====================================================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include "MapData.h"

class Text;

//====================================================================================================
// Class Declarations
//====================================================================================================
class Texture
{
	friend class TextureManager;
public:
	Texture();
	~Texture();
	
	void Render(SDL_Rect* clip, SDL_Rect* offset, SDL_Color color, double angle, SDL_RendererFlip flip);
	float Width() const		{ return (float)mWidth; }
	float Height() const	{ return (float)mHeight; }

private:
	void Load(const char* fileName);
	void LoadAsTilemap(MapData* map);
	void LoadImage(const char* fileName);
	void LoadAsFont(const Text* text);

	SDL_Texture* mpTexture;
	int mWidth;
	int mHeight;
};

#endif // #ifndef _TEXTURE_H_