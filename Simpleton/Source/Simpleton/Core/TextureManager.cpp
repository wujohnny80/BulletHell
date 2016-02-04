//====================================================================================================
// Filename:	TextureManager.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "TextureManager.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
TextureManager::TextureManager()
{
}

void TextureManager::Terminate()
{
	// Deallocate image textures
	auto it = mImageMap.begin();
	for (; it != mImageMap.end(); ++it)
	{
		delete it->second;
	}
	mImageMap.clear();

	// Deallocate font textures
	auto itFont = mFontMap.begin();
	for (; itFont != mFontMap.end(); ++itFont)
	{
		delete itFont->second;
	}
	mFontMap.clear();
}

//----------------------------------------------------------------------------------------------------

Texture* TextureManager::GetTexture(std::string textureName)
{
	auto it = mImageMap.find(textureName);
    if (it != mImageMap.end())
        return it->second;
	else
	{
		Texture* newTexture = new Texture();
		newTexture->Load(textureName.c_str());
		mImageMap[textureName] = newTexture;
		return newTexture;
	}
}

//----------------------------------------------------------------------------------------------------

Texture* TextureManager::GetTiledTexture(MapData* map)
{
	if (mImageMap[map->FileName()] != nullptr)
		return mImageMap[map->FileName()];
	else
	{
		Texture* newTexture = new Texture();
		newTexture->LoadAsTilemap(map);
		mImageMap[map->FileName()] = newTexture;
		return newTexture;
	}
}

//----------------------------------------------------------------------------------------------------

Texture* TextureManager::GetFontTexture(const Text* text)
{
	auto it = mFontMap.find(text);
    if (it != mFontMap.end())
	{
		it->second->LoadAsFont(text);
        return it->second;
	}
	else
	{
		Texture* newTexture = new Texture();
		newTexture->LoadAsFont(text);
		mFontMap[text] = newTexture;
		return newTexture;
	}
}