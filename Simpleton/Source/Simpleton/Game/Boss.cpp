//====================================================================================================
// Filename:	Boss.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Boss.h"
#include "BulletFactory.h"
#include "GameManager.h"

#include "../Core/Input.h"
#include "../Core/Timer.h"

#include <stdio.h>

//====================================================================================================
// Class Definitions
//====================================================================================================
Boss::Boss()
	: GameObject()
	, mGameManager(nullptr)
	, mCollider(nullptr)
	, mSprite(nullptr)
	, mMaxHealth(0)
	, mCurrentHealth(0)
	, mBulletSiteCount(20)
	, mSpeed(0.0f)
{
}

Boss::~Boss()
{
	int size = mBulletSites.size();
	for (int i = 0; i < size; ++i)
	{
		delete mBulletSites[i];
		mBulletSites[i] = nullptr;
	}
	mBulletSites.clear();
}

void Boss::Initialize(GameManager* gm)
{
	mGameManager = gm;
	name = "Boss";
	mSprite = AddComponent<Sprite>();
	mSprite->SetTexture("Boss.png");
	mSprite->SetCentered(true);
	mSprite->SetAngle(180.0);
	
	Vector2 spawnPos = Vector2(Application::screenWidth * 0.5f, Application::screenHeight * 0.5f - 250.0f);
	transform->position = spawnPos;
	transform->scale = Vector2(0.5f, 0.5f);

	mCollider = AddComponent<CircleCollider>();
	mCollider->circle.radius = mSprite->Width() * 0.5f;
	
	mSpeed = 0.0f;
	mMaxHealth = 5000;
	mCurrentHealth = mMaxHealth;

	// Initialize bullet sites
	for (int i = 0; i < mBulletSiteCount; ++i)
	{	
		BulletSite* bs = new BulletSite();
		bs->transform->SetParent(this->transform);
		bs->transform->localPosition = Vector2(0.0f, 0.0f);
		bs->Initialize(this, mGameManager);
		bs->SetFireRate(3.0f);
		mBulletSites.push_back(bs);
	}
}

void Boss::Update()
{
	if (!IsActive())
		return;
	
	if (mCurrentHealth <= 0)
	{
		GameManager::AddScore(100000);
		SetActive(false);
		return;
	}

	GameObject::UpdateComponents();

	Shoot();
	
	int size = mBulletSites.size();
	for (int i = 0; i < size; ++i)
	{
		mBulletSites[i]->Update();
	}
	
	mSprite->SetColor(255, 255, 255, 255);
}

void Boss::HandleCollision(GameObject* other)
{
	if (other->name == "PlayerBullet")
	{
		Deactivate();
		other->Deactivate();
	}
	if (other->name == "Player")
	{
		other->Deactivate();
	}	
}

void Boss::Deactivate()
{
	--mCurrentHealth;
	mSprite->SetColor(255, 0, 0, 255);
	std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	std::cout << mCurrentHealth;
}

void Boss::Shoot()
{
	int size = mBulletSites.size();
	for (int i = 0; i < size; ++i)
	{
		float xSpacing = 100.0f;
		float startX = -(mBulletSiteCount - 1) * xSpacing * 0.5f;
		Vector2 target = Vector2(Application::screenWidth * 0.5f, Application::screenHeight * 0.5f);
		Vector2 dir = (target + Vector2(startX + (i * xSpacing), 0.0f)) - mBulletSites[i]->transform->position;
		dir = dir.Normalized();
		mBulletSites[i]->SetDirection(dir);
		mBulletSites[i]->Shoot();
	}
}