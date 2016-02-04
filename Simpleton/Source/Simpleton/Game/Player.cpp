//====================================================================================================
// Filename:	Player.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Player.h"
#include "BulletFactory.h"
#include "GameManager.h"
#include "Missile.h"

#include "../Core/Input.h"
#include "../Core/Timer.h"

#include <stdio.h>

//====================================================================================================
// Class Definitions
//====================================================================================================
Player::Player()
	: GameObject()
	, mGameManager(nullptr)
	, mCollider(nullptr)
	, mSprite(nullptr)
	, mBulletSiteCount(5)
	, mSpeed(0.0f)
{
}

Player::~Player()
{
	int size = mBulletSites.size();
	for (int i = 0; i < size; ++i)
	{
		delete mBulletSites[i];
		mBulletSites[i] = nullptr;
	}
	mBulletSites.clear();
}

void Player::Initialize(GameManager* gm)
{
	mGameManager = gm;
	mMissileFactory = mGameManager->GetMissileFactory();
	name = "Player";
	mSprite = AddComponent<Sprite>();
	mSprite->SetTexture("ship.png");
	mSprite->SetCentered(true);
	
	transform->position = Vector2(Application::screenWidth * 0.5f, Application::screenHeight * 0.5f);
	transform->scale = Vector2(0.3f, 0.3f);

	mCollider = AddComponent<CircleCollider>();
	mCollider->circle.radius = mSprite->Width() * 0.5f;

	mSpeed = 500.0f;

	// Initialize bullet sites
	for (int i = 0; i < mBulletSiteCount; ++i)
	{	
		BulletSite* bs = new BulletSite();
		bs->transform->SetParent(this->transform);
		bs->transform->localPosition = Vector2(0.0f, -mSprite->Height() * 0.5f);
		bs->Initialize(this, mGameManager);
		bs->SetFireRate(0.1f);
		mBulletSites.push_back(bs);
	}
}

void Player::Update()
{
	if (!IsActive())
		return;

	UpdateComponents();

	UpdateInput();
	CheckBounds();

	int size = mBulletSites.size();
	for (int i = 0; i < size; ++i)
	{
		mBulletSites[i]->Update();
	}
}

void Player::HandleCollision(GameObject* other)
{
	if (other->name == "Enemy" || other->name == "Enemy2" || other->name == "Boss" || other->name == "EnemyBullet")
	{
		other->Deactivate();
		Deactivate();
	}
}

void Player::Deactivate()
{
	SetActive(false);
}

void Player::UpdateInput()
{
	if (Input::KeyDown(Keys::W))
	{	
		transform->position.y -= mSpeed * Timer::deltaTime;
	}
	if (Input::KeyDown(Keys::A))
	{
		transform->position.x -= mSpeed * Timer::deltaTime;
	}
	if (Input::KeyDown(Keys::S))
	{
		transform->position.y += mSpeed * Timer::deltaTime;
	}
	if (Input::KeyDown(Keys::D))
	{
		transform->position.x += mSpeed * Timer::deltaTime;
	}
	if (Input::KeyDown(Keys::MOUSE_L) || Input::KeyDown(Keys::SPACE))
	{
		Shoot();
	}
	if (Input::KeyDown(Keys::MOUSE_R))
	{
		FireMissile();
	}
}

void Player::Shoot()
{
	int size = mBulletSites.size();
	for (int i = 0; i < size; ++i)
	{
		float xSpacing = 50.0f;
		float startX = -(mBulletSiteCount - 1) * xSpacing * 0.5f;
		Vector2 dir = (Input::mousePosition + Vector2(startX + (i * xSpacing), 0.0f)) - mBulletSites[i]->transform->position;
		dir = dir.Normalized();
		mBulletSites[i]->SetDirection(dir);
		mBulletSites[i]->Shoot();
	}
}

void Player::FireMissile()
{
	int size = mBulletSites.size();
	for (int i = 0; i < size; ++i)
	{
		Missile* m = mMissileFactory->GetMissile();
		if (m != nullptr)
		{
			m->SetSpeed(400.0f);
			m->GetComponent<Sprite>()->SetColor(0, 0, 255, 255);
			m->Spawn(mBulletSites[i]->transform->position);
		}
	}
}

void Player::CheckBounds()
{
	// Right/Left walls
	if (transform->position.x < mSprite->Width() * 0.5f)
	{
		transform->position.x = mSprite->Width() * 0.5f;
	}
	else if (transform->position.x > Application::screenWidth - mSprite->Width() * 0.5f)
	{
		transform->position.x = Application::screenWidth - mSprite->Width() * 0.5f;		
	}
	// Top/Bottom walls
	if (transform->position.y < mSprite->Height() * 0.5f)
	{
		transform->position.y = mSprite->Height() * 0.5f;
	}
	else if	(transform->position.y > Application::screenHeight - mSprite->Height() * 0.5f)
	{
		transform->position.y = Application::screenHeight - mSprite->Height() * 0.5f;
	}
}