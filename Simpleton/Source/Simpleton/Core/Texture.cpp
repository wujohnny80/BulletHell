//====================================================================================================
// Filename:	Texture.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Texture.h"

#include <assert.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>

#include "Graphics.h"
#include "TextureManager.h"
#include "Text.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
Texture::Texture()
	: mpTexture(nullptr)
	, mWidth(0)
	, mHeight(0)
{
}

Texture::~Texture()
{
	SDL_DestroyTexture(mpTexture);
}

void Texture::Load(const char* fileName)
{
	//Load the texture
	LoadImage(fileName);

	// Get texture dimension
	if (mpTexture != nullptr)
	{
		SDL_QueryTexture(mpTexture, 0, 0, &mWidth, &mHeight);
	}
}

void Texture::LoadAsTilemap(MapData* mapData)
{
	// Construct full path name
	std::string fullPath = "../../Assets/Images/";	// Up two folder from project dir -> Asset -> Images
	fullPath += mapData->FileName();

	// Assumes my mapData is already loaded
	if (mapData->FileName() == "")
		return;

	// Load tileset
	SDL_Surface* tileSurf = IMG_Load(fullPath.c_str());
	if (tileSurf == nullptr)
	{
		printf("Image at %s could not be loaded! SDL_image Error: %s\n", fullPath, IMG_GetError());
	}

	// Store to local vars
	int mapw = mapData->MapWidth();
	int maph = mapData->MapHeight();
	int tilew = mapData->TileWidth();
	int tileh = mapData->TileHeight();

	// Create SDL surface
	SDL_Surface* bgSurf = SDL_CreateRGBSurface( 0,
												mapw * tilew,
												maph * tileh,
												tileSurf->format->BitsPerPixel,
												tileSurf->format->Rmask,
												tileSurf->format->Gmask,
												tileSurf->format->Bmask,
												tileSurf->format->Amask );

	// Clip tileset onto our bg image
	// blit (src, clip, dest, loc)
	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;
	clip.w = tilew;
	clip.h = tileh;

	SDL_Rect offset = {0,0,0,0};

	int mapSize = mapData->Size();
	int tpr = tileSurf->w / tilew;

	for(int i = 0; i < mapSize; ++i)
	{
		clip.x = tilew * (mapData->MapBuffer()[i] % tpr);
		clip.y = tileh * (mapData->MapBuffer()[i] / tpr);

		SDL_BlitSurface(tileSurf, &clip, bgSurf, &offset);
		offset.x += tilew;
		if (offset.x == tilew * mapw)
		{
			offset.x = 0;
			offset.y += tileh;
		}
	}

	// Convert to SDL texture
	mpTexture = SDL_CreateTextureFromSurface(Graphics::Renderer, bgSurf);

	SDL_FreeSurface(tileSurf);
	SDL_FreeSurface(bgSurf);

	// Get texture dimension
	if (mpTexture != nullptr)
	{
		SDL_QueryTexture(mpTexture, 0, 0, &mWidth, &mHeight);
	}
}

void Texture::LoadAsFont(const Text* text)
{
	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(text->mpFont, text->mMsg.c_str(), text->mColor);
    if(textSurface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        //Create texture from surface pixels
		mpTexture = SDL_CreateTextureFromSurface(Graphics::Renderer, textSurface);
        if(mpTexture == nullptr)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
}

void Texture::Render(SDL_Rect* clip, SDL_Rect* offset, SDL_Color color, double angle, SDL_RendererFlip flip)
{
	// Check if we have a valid texture
	if (mpTexture == nullptr)
		return;

	// Set color and alpha
	SDL_SetTextureColorMod(mpTexture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(mpTexture, color.a);

	// Set blend mode
	SDL_SetTextureBlendMode(mpTexture, SDL_BLENDMODE_BLEND);
	
	SDL_RenderCopyEx(Graphics::Renderer, mpTexture, clip, offset, angle, 0, flip);
}

void Texture::LoadImage(const char* fileName)
{
	// Construct full path name
	std::string fullPath = "../../Assets/Images/";	// Up two folder from project dir -> Asset -> Images
	fullPath += fileName;

	// Load image
	SDL_Surface* loadedSurface = IMG_Load(fullPath.c_str());

	// Verify it was loaded
	if (loadedSurface == nullptr)
	{
		printf("Image at %s could not be loaded! SDL_image Error: %s\n", fullPath.c_str(), IMG_GetError());
	}
	else
    {
        // Create texture from surface pixels
		mpTexture = SDL_CreateTextureFromSurface(Graphics::Renderer, loadedSurface);
        if(mpTexture == nullptr)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", fullPath.c_str(), SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
}