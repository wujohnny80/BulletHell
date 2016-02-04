//====================================================================================================
// Filename:	Missile.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Missile.h"
#include "MissileFactory.h"
#include "../Core/Application.h"
#include "../Core/Input.h"
#include "../Core/Timer.h"
#include "../Math/Math.h"

#include <iostream>

//====================================================================================================
// Class Definitions
//====================================================================================================

Missile::Missile()
	: GameObject()
	, mCollider(nullptr)
	, mSprite(nullptr)
	, mMissileFactory(nullptr)
	, mIndex(-1)
	, mSpeed(0.0f)
	, mTimer(0)
	, mT(0.0f)
	, mDist(0.0f)
{
}

Missile::~Missile()
{
}

void Missile::Initilaize()
{
	mSprite = AddComponent<Sprite>();
	mSprite->SetTexture("Bullet.png");
	mSprite->SetCentered(true);
	
	transform->position = Vector2(Application::screenWidth * 0.5f,
									Application::screenHeight * 0.5f);
	transform->scale = Vector2(1.0f, 1.0f);

	mCollider = AddComponent<CircleCollider>();
	mCollider->circle.radius = mSprite->Width() * 0.5f;

	layer = -1;
}

void Missile::Spawn(Vector2 pos)
{
	transform->position = pos;
	
	mPoints.clear();
	ClearQueue();
	mT = 0;	

	float dist = (Input::mousePosition - pos).Magnitude();

	// Set path points
	mPath.push(pos);
	for (int i = 0; i < 2; ++i)
	{
		float randX = rand() % (int)(dist * 0.5f) - dist * 0.25f;
		float randY = (float)(rand() % (int)(dist * 0.5f));
		Vector2 p = Vector2(randX, randY) + pos;
		mPath.push(p);
	}
	mPath.push(Input::mousePosition);

	for (int i = 0; i < 4; ++i)
	{
		mPoints.push_back(mPath.front());
		mPath.pop();
	}

	mDist = Math::GetBezierDistance(mPoints);

	SetActive(true);
}

void Missile::Update()
{
	if (!IsActive())
		return;

	GameObject::UpdateComponents();
	
	UpdateMovement();

	//CheckBounds();
}

void Missile::HandleCollision(GameObject* other)
{	
}

void Missile::Deactivate()
{
}

void Missile::UpdateMovement()
{
	mT += mSpeed * Timer::deltaTime / mDist;
	if (mT > 1)
	{
		if (!mPath.empty())
		{
			mPoints.clear();
			mPoints.push_back(transform->position);
			for (int i = 0; i < 3; ++i)
			{
				mPoints.push_back(mPath.front());
				mPath.pop();
			}

			mDist = Math::GetBezierDistance(mPoints);
			mT = 0;
		}
		else
		{
			mT = 1;
			mMissileFactory->ReturnMissile(this);
		}
	}

	transform->position = Math::GetCubicBezierPosition(mT, mPoints);
}

void Missile::CheckBounds()
{
	if (mMissileFactory == nullptr)
		return;

	// Right/Left walls
	if (transform->position.x < -mSprite->Width() * 0.5f)
	{
		mMissileFactory->ReturnMissile(this);
	}
	else if (transform->position.x > Application::screenWidth + mSprite->Width() * 0.5f)
	{
		mMissileFactory->ReturnMissile(this);
	}
	// Top/Bottom walls
	if (transform->position.y < -mSprite->Height() * 0.5f)
	{
		mMissileFactory->ReturnMissile(this);
	}
	else if	(transform->position.y > Application::screenHeight + mSprite->Height() * 0.5f)
	{
		mMissileFactory->ReturnMissile(this);
	}
}

void Missile::ClearQueue()
{
	std::queue<Vector2> empty;
	std::swap(mPath, empty);
}