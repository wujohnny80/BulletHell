//====================================================================================================
// Filename:	Enemy.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Enemy.h"
#include "BulletFactory.h"
#include "GameManager.h"

#include "../Core/Input.h"
#include "../Core/Timer.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
Enemy::Enemy()
	: GameObject()
	, mGameManager(nullptr)
	, mCollider(nullptr)
	, mSprite(nullptr)
	, mBulletSiteCount(1)
	, mSpeed(0.0f)
	, mMaxHealth(0)
	, mCurrentHealth(0)
{
}

Enemy::~Enemy()
{
	int size = mBulletSites.size();
	for (int i = 0; i < size; ++i)
	{
		delete mBulletSites[i];
		mBulletSites[i] = nullptr;
	}
	mBulletSites.clear();
}

void Enemy::Initialize(GameManager* gm)
{
	name = "Enemy";
	mGameManager = gm;

	mSprite = AddComponent<Sprite>();
	mSprite->SetTexture("enemy1.png");
	mSprite->SetCentered(true);
	mSprite->SetAngle(180.0);
	
	transform->position = Vector2();
	transform->scale = Vector2(0.2f, 0.2f);

	mCollider = AddComponent<CircleCollider>();
	mCollider->circle.radius = mSprite->Width() * 0.5f;

	mSpeed = 300.0f;
	mMaxHealth = 2;
	mCurrentHealth = mMaxHealth;

	// Initialize bullet sites
	for (int i = 0; i < mBulletSiteCount; ++i)
	{	
		BulletSite* bs = new BulletSite();
		bs->transform->SetParent(this->transform);
		bs->transform->localPosition = Vector2(0.0f, mSprite->Height() * 0.5f);
		bs->Initialize(this, mGameManager);
		bs->SetFireRate(0.5f);
		mBulletSites.push_back(bs);
	}
}

void Enemy::Update()
{
	if (!IsActive())
		return;
	
	if (mCurrentHealth <= 0)
	{
		GameManager::AddScore(100);
		SetActive(false);
		return;
	}

	UpdateComponents();

	UpdateMovement();
	Shoot();
	CheckBounds();
	
	int size = mBulletSites.size();
	for (int i = 0; i < size; ++i)
	{
		mBulletSites[i]->Update();
	}
	
	mSprite->SetColor(255, 255, 255, 255);
}

void Enemy::HandleCollision(GameObject* other)
{
	if (other->name == "PlayerBullet")
	{
		Deactivate();
		other->Deactivate();
	}
	if (other->name == "Player")
	{
		Deactivate();
		other->Deactivate();
	}
}

void Enemy::Deactivate()
{
	--mCurrentHealth;
	mSprite->SetColor(255, 0, 0, 255);
}

void Enemy::UpdateMovement()
{
	transform->position.y += mSpeed * Timer::deltaTime;	
}

void Enemy::Shoot()
{
	int size = mBulletSites.size();
	for (int i = 0; i < size; ++i)
	{
		mBulletSites[i]->SetDirection(Vector2(0, 1));
		mBulletSites[i]->Shoot();
	}
}

void Enemy::CheckBounds()
{
	// Right/Left walls
	if (transform->position.x < -mSprite->Width() * 0.5f)
	{
		SetActive(false);
	}
	else if (transform->position.x > Application::screenWidth + mSprite->Width() * 0.5f)
	{
		SetActive(false);
	}
	// Bottom walls
	if	(transform->position.y > Application::screenHeight + mSprite->Height() * 0.5f)
	{
		SetActive(false);
	}
}