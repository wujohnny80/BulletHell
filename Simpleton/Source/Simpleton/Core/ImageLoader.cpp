//====================================================================================================
// Filename:	ImageLoader.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "ImageLoader.h"

#include <stdio.h>
#include <assert.h>

#include "Graphics.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
SDL_Texture* ImageLoader::Load(const char* fileName)
{
	// Final texture
	SDL_Texture* newTexture = nullptr;

	// Load image
	SDL_Surface* loadedSurface = IMG_Load(fileName);

	// Verify it was loaded
	if (loadedSurface == nullptr)
	{
		printf("Image at %s could not be loaded! SDL_image Error: %s\n", fileName, IMG_GetError());
	}
	else
    {
        // Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Graphics::Renderer, loadedSurface);
        if( newTexture == nullptr )
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", fileName, SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

	return newTexture;
}