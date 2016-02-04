//====================================================================================================
// Filename:	Background.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Background.h"
#include "../Core/Application.h"
#include "../Core/Timer.h"

#include <stdio.h>

//====================================================================================================
// Class Definitions
//====================================================================================================

Background::Background()
	: mSprite(nullptr)
	, mMap(nullptr)
	, mSpeed(0.0f)
	, myPartner(nullptr)
{
}

Background::~Background()
{
	delete mMap;
}

void Background::Initialize(const char* mapFile)
{
	mMap = new MapData();
	mMap->LoadMap(mapFile);
	AddComponent<Sprite>();
	mSprite = GetComponent<Sprite>();
	mSprite->SetTiledTexture(mMap);
	mSprite->SetCentered(false);
	mSpeed = 100.0f;
	layer = -2;
}

void Background::Update()
{
	UpdateComponents();
	ResetToTop();
	transform->position.y += mSpeed * Timer::deltaTime;
}

void Background::HandleCollision(GameObject* other)
{
}

void Background::Deactivate()
{
}

void Background::ResetToTop()
{
	if (transform->position.y > (float)Application::screenHeight)
	{
		//transform->position.y = (float)-Application::screenHeight;
		transform->position.y = myPartner->transform->position.y - myPartner->GetComponent<Sprite>()->Height();
	}
}