//====================================================================================================
// Filename:	Enemy2.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Enemy2.h"
#include "BulletFactory.h"
#include "GameManager.h"

#include "../Core/Input.h"
#include "../Core/Timer.h"

//====================================================================================================
// Static Definitions
//====================================================================================================
std::vector<Vector2> Enemy2::sPoints;

//====================================================================================================
// Class Definitions
//====================================================================================================
Enemy2::Enemy2()
	: GameObject()
	, mGameManager(nullptr)
	, mCollider(nullptr)
	, mSprite(nullptr)
	, mBulletSiteCount(1)
	, mSpeed(0.0f)
	, mMaxHealth(0)
	, mCurrentHealth(0)
	, mT(0.0f)
	, mDist(0.0f)
	, mLevel(0)
	, mNumBranches(2)
{
	InitializePath();
	mStart = mEnd = sPoints[0];
}

Enemy2::~Enemy2()
{
	int size = mBulletSites.size();
	for (int i = 0; i < size; ++i)
	{
		delete mBulletSites[i];
		mBulletSites[i] = nullptr;
	}
	mBulletSites.clear();
}

void Enemy2::Initialize(GameManager* gm)
{
	name = "Enemy2";
	mGameManager = gm;

	mSprite = AddComponent<Sprite>();
	mSprite->SetTexture("Enemy2.png");
	mSprite->SetCentered(true);
	mSprite->SetAngle(180.0);
	
	transform->position = Vector2();
	transform->scale = Vector2(0.5f, 0.5f);

	mCollider = AddComponent<CircleCollider>();
	mCollider->circle.radius = mSprite->Width() * 0.5f;

	mSpeed = 200.0f;
	mMaxHealth = 5;
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

	// Initialize waypoint path

	// Push the first point as starting position
	mPath.push_back(sPoints[0]);

	// Get the next 2 random point from the "tree"
	int wayPoint1 = Math::RandomRange(1, 2);
	int wayPoint2 = Math::RandomRange(3, 6);
	int wayPoint3 = Math::RandomRange(7, 8);
	mPath.push_back(sPoints[wayPoint1]);
	mPath.push_back(sPoints[wayPoint2]);
	mPath.push_back(sPoints[wayPoint3]);

	mDist = Math::GetBezierDistance(sPoints);
	
	transform->position = mStart;
}

void Enemy2::Update()
{
	if (!IsActive())
		return;
	
	if (mCurrentHealth <= 0)
	{
		GameManager::AddScore(500);
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

void Enemy2::HandleCollision(GameObject* other)
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

void Enemy2::Deactivate()
{	
	--mCurrentHealth;
	mSprite->SetColor(255, 0, 0, 255);
}

void Enemy2::UpdateMovement()
{
	//transform->position.y += mSpeed * Timer::deltaTime;
	mT += mSpeed * Timer::deltaTime / mDist;
	if (mT > 1)
	{
		SetActive(false);
	}
	
	transform->position = Math::GetCubicBezierPosition(mT, mPath);
}

void Enemy2::Shoot()
{
	int size = mBulletSites.size();
	for (int i = 0; i < size; ++i)
	{
		mBulletSites[i]->SetDirection(Vector2(0, 1));
		mBulletSites[i]->Shoot();
	}
}

void Enemy2::CheckBounds()
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

void Enemy2::InitializePath()
{
	sPoints.push_back(Vector2(Application::screenWidth * 0.5f, 0.0f));
	sPoints.push_back(Vector2(0.0f,									Application::screenHeight * 0.33f));
	sPoints.push_back(Vector2((float)Application::screenWidth,		Application::screenHeight * 0.33f));
	sPoints.push_back(Vector2(0.0f,									Application::screenHeight * 0.66f));
	sPoints.push_back(Vector2(Application::screenWidth * 0.375f,	Application::screenHeight * 0.66f));
	sPoints.push_back(Vector2(Application::screenWidth * 0.625f,	Application::screenHeight * 0.66f));
	sPoints.push_back(Vector2(0.0f,									Application::screenHeight * 0.66f));
	sPoints.push_back(Vector2(Application::screenWidth * 0.25f,		(float)Application::screenHeight));
	sPoints.push_back(Vector2(Application::screenWidth * 0.75f,		(float)Application::screenHeight));
}