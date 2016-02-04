//====================================================================================================
// Filename:	Sprite.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Sprite.h"

#include <assert.h>
#include <iostream>
#include <fstream>

#include "SDL.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Timer.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

Sprite::Sprite()
	: mpTexture(nullptr)
	, mWidth(0.0f)
	, mHeight(0.0f)
	, mVisible(true)
	, mFlipH(false)
	, mIsCentered(false)
	, mAngle(0.0)
	, mIsSpriteSheet(false)
	, mFrame(0)
	, mAnimDone(false)
	, mAnimate(false)
	, mTimer(0.0f)
{
	mColor.r = 255;
	mColor.g = 255;
	mColor.b = 255;
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

Sprite::~Sprite()
{
}

void Sprite::Update()
{
	if (!enabled)
		return;

	// Update any animation
	mTimer += Timer::deltaTime;
	if (mVisible)
	{
		SetOffset();
		if (mAnimate)
		{
			SetClip(mFrame);
			if (mTimer > 1.0f / mCurrentAnimState.fps)
			{
				mFrame++;
				mTimer = 0.0f;

				// Reached last frame, loop back
				if (mFrame >= mCurrentAnimState.frameCount)
				{
 					mFrame = 0;
					mAnimDone = true;
				}
			}
		}
		Render();
	}
}

void Sprite::Render()
{
	// Check if we have a valid texture
	if (mpTexture == nullptr)
		return;

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (mFlipH)
		flip = SDL_FLIP_HORIZONTAL;

	mpTexture->Render(&mClip, &mOffset, mColor, mAngle, flip);
}

void Sprite::SetTexture(std::string fileName)
{
	mpTexture = TextureManager::Instance().GetTexture(fileName);
	SetOffset();
	mClip.w = (int)mWidth;
	mClip.h = (int)mHeight;
}

void Sprite::SetTiledTexture(MapData* map)
{
	mpTexture = TextureManager::Instance().GetTiledTexture(map);
	SetOffset();
	mClip.w = (int)mWidth;
	mClip.h = (int)mHeight;
}

void Sprite::LoadAnimation(const char* fileName)
{
	// Construct full path name
	std::string fullPath = "../../Assets/Animations/";
	fullPath += fileName;

	// Open the file
	std::ifstream file;
	file.open(fullPath);

	// Check if the file is openend properly
	if (file.fail())
	{
		std::cout << "Failed to open file\n";
		return;
	}

	// Read/Write
	std::string temp, imgfile, name;
	int x, y, w, h, numframes, fps;

	if (file.peek() == '#')
		getline(file, temp);

	file >> temp >> imgfile;

	while (!file.eof())
	{
		if(file.peek() == '#' || file.peek() == 10)
		{
			getline(file, temp);
			continue;
		}
		file >> temp >> name >> x >> y >> w >> h >> numframes >> fps;

		AnimationState s;
		s.name = name;
		s.x = x;
		s.y = y;
		s.w = w;
		s.h = h;
		s.frameCount = numframes;
		s.fps = fps;
		mAnimations[name] = s;

		getline(file, temp);
	}

	mIsSpriteSheet = true;
	mAnimate = true;
	mCurrentAnimState = mAnimations[0];
	SetTexture(imgfile);
	SetClip(mFrame);

	// We are done with the file
	file.close();
}

void Sprite::SetAnimState(std::string state)
{
	auto it = mAnimations.find(state);
    if (it == mAnimations.end())
	{
		printf("Animation %s does not exist!", state);
		return;
	}

	mCurrentAnimState = mAnimations[state];
	mFrame = 0;
	mTimer = 0.0f;
	mAnimDone = false;
}

void Sprite::SetClip(int frame)
{
	mClip.x = mCurrentAnimState.x + mFrame * mCurrentAnimState.w;
	mClip.y = mCurrentAnimState.y;
	mClip.w = mCurrentAnimState.w;
	mClip.h = mCurrentAnimState.h;
}

void Sprite::SetOffset()
{
	if (mIsSpriteSheet)
	{
		mWidth = (float)mCurrentAnimState.w;
		mHeight = (float)mCurrentAnimState.h;
	}
	else
	{
		mWidth = mpTexture->Width();
		mHeight = mpTexture->Height();
	}

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

Vector2 Sprite::TopLeft()
{
	if (mIsCentered)
	{
		return Vector2(gameObject->transform->position.x - mWidth * 0.5f * gameObject->transform->scale.x,
					   gameObject->transform->position.y - mHeight * 0.5f * gameObject->transform->scale.y);
	}
	else
		return gameObject->transform->position;
}

Vector2 Sprite::BottomRight()
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

Vector2 Sprite::Center()
{
	if (mIsCentered)
		return gameObject->transform->position;
	else
	{
		return Vector2(gameObject->transform->position.x + mWidth * 0.5f * gameObject->transform->scale.x,
					   gameObject->transform->position.y + mHeight * 0.5f * gameObject->transform->scale.y);
	}
}