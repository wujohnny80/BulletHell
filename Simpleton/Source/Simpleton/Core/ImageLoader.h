//====================================================================================================
// Filename:	ImageLoader.h
// Created by:	Johnny Wu
// Description:	Static class loading images. Supports PNG, JPG, more
//====================================================================================================
#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include "SDL_image.h"
#include "MapData.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class ImageLoader
{
public:
	static SDL_Texture* Load(const char* filePath);
	static SDL_Texture* LoadAsTilemap(MapData* map);
};

#endif // #ifndef _IMAGELOADER_H_