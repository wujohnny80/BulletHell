//====================================================================================================
// Filename:	TextureManager.h
// Created by:	Johnny Wu
// Description:	Class for the managing all textures.
//====================================================================================================
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <unordered_map>
#include <string>

#include "SDL.h"
#include "Texture.h"

class Text;

//====================================================================================================
// Class Declarations
//====================================================================================================

class TextureManager
{
public:
	static TextureManager& Instance()	{ static TextureManager instance; return instance; }
	void Terminate();
	
	Texture* GetTexture(std::string textureName);
	Texture* GetTiledTexture(MapData* map);
	Texture* GetFontTexture(const Text* text);
private:
	TextureManager();	
	TextureManager(TextureManager const&);	// Don't implement
	void operator=(TextureManager const&);	// Don't implement

	std::unordered_map<std::string, Texture*> mImageMap;	// Map of all image resources
	std::unordered_map<const Text*, Texture*> mFontMap;		// Map of all font resources
};

#endif // #ifndef _TEXTUREMANAGER_H_