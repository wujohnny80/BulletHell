//====================================================================================================
// Filename:	Text.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Text.h"

#include <assert.h>
#include <iostream>
#include <fstream>
#include <SDL.h>

#include "GameObject.h"
#include "TextureManager.h"
#include "Timer.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

Text::Text()
	: mpTexture(nullptr)
	, mWidth(0.0f)
	, mHeight(0.0f)
	, mVisible(true)
	, mFlipH(false)
	, mIsCentered(false)
	, mAngle(0.0)
	, mpFont(nullptr)
	, mFontFile("")
	, mMsg("Default Text")
	, mFontSize(14)
	, mBold(false)
	, mItalic(false)
	, mUnderline(false)
	, mStrikeThru(false)
	, mOutline(false)
	, mOutlineSize(2)
{
	mColor.r = 0;
	mColor.g = 0;
	mColor.b = 0;
	mColor.a = 255;
	
	mClip.x = 0;
	mClip.y = 0;
	mClip.w = 0;
	mClip.h = 0;

	mOffset.x = 0;
	mOffset.y = 0;
	mOffset.w = 0;
	mOffset.h = 0;
}

Text::~Text()
{
	TTF_CloseFont(mpFont);
}

void Text::Initialize(std::string fontFile)
{
	mFontFile = "../../Assets/Fonts/";	// Up two folder from project dir -> Asset -> Fonts
	mFontFile += fontFile;
	SetFont();
	SetTexture();
}

void Text::Update()
{
	if (!enabled)
		return;

	if (mVisible)
	{
		SetFont();
		SetTexture();
		SetOffset();
		Render();
	}
}

void Text::Render()
{
	// Check if we have a valid texture
	if (mpTexture == nullptr)
		return;

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (mFlipH)
		flip = SDL_FLIP_HORIZONTAL;

	mpTexture->Render(&mClip, &mOffset, mColor, mAngle, flip);
}

void Text::SetTexture()
{
	mpTexture = TextureManager::Instance().GetFontTexture(this);

	// Set Texture offset and clip
	SetOffset();
	mClip.w = (int)mWidth;
	mClip.h = (int)mHeight;
}

void Text::SetOffset()
{
	mWidth = mpTexture->Width();
	mHeight = mpTexture->Height();

	if (mIsCentered)
	{
		mOffset.x = (int)(gameObject->transform->position.x - mWidth * 0.5f * gameObject->transform->scale.x);
		mOffset.y = (int)(gameObject->transform->position.y - mHeight * 0.5f * gameObject->transform->scale.y);
		mOffset.w = (int)(mWidth * gameObject->transform->scale.x);
		mOffset.h = (int)(mHeight * gameObject->transform->scale.y);
	}
	else
	{
		mOffset.x = (int)gameObject->transform->position.x;
		mOffset.y = (int)gameObject->transform->position.y;
		mOffset.w = (int)(mWidth * gameObject->transform->scale.x);
		mOffset.h = (int)(mHeight * gameObject->transform->scale.y);
	}
}

Vector2 Text::TopLeft()
{
	if (mIsCentered)
	{
		return Vector2(gameObject->transform->position.x - mWidth * 0.5f * gameObject->transform->scale.x,
					   gameObject->transform->position.y - mHeight * 0.5f * gameObject->transform->scale.y);
	}
	else
		return gameObject->transform->position;
}

Vector2 Text::BottomRight()
{
	if (mIsCentered)
	{
		return Vector2(gameObject->transform->position.x + mWidth * 0.5f * gameObject->transform->scale.x,
					   gameObject->transform->position.y + mHeight * 0.5f * gameObject->transform->scale.y);
	}
	else
	{
		return Vector2(gameObject->transform->position.x + mWidth * gameObject->transform->scale.x,
					   gameObject->transform->position.y + mHeight * gameObject->transform->scale.y);
	}
}

Vector2 Text::Center()
{
	if (mIsCentered)
		return gameObject->transform->position;
	else
	{
		return Vector2(gameObject->transform->position.x + mWidth * 0.5f * gameObject->transform->scale.x,
					   gameObject->transform->position.y + mHeight * 0.5f * gameObject->transform->scale.y);
	}
}

void Text::SetFont()
{
    //Open the font
	mpFont = TTF_OpenFont(mFontFile.c_str(), mFontSize);
    if( mpFont == nullptr )
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(404);
    }

	// Set font properties
	int fontStyle = 0;
	if (mBold)
		fontStyle |= TTF_STYLE_BOLD;
	if (mItalic)
		fontStyle |= TTF_STYLE_ITALIC;
	if (mUnderline)
		fontStyle |= TTF_STYLE_UNDERLINE;
	if (mStrikeThru)
		fontStyle |= TTF_STYLE_STRIKETHROUGH;

	TTF_SetFontStyle(mpFont, fontStyle);

	if (mOutline)
		TTF_SetFontOutline(mpFont, 2);	// default outline thickness is 2
}