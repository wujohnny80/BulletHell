//====================================================================================================
// Filename:	BulletSite.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "BulletSite.h"
#include "BulletFactory.h"
#include "GameManager.h"

#include "../Core/Input.h"
#include "../Core/Timer.h"

#include <stdio.h>

//====================================================================================================
// Class Definitions
//====================================================================================================
BulletSite::BulletSite()
	: GameObject()
	, mGameManager(nullptr)
	, mDirection(Vector2())
	, mFireRate(0.0f)
	, mTimer(0.0f)
{
}

BulletSite::~BulletSite()
{
}

void BulletSite::Initialize(GameObject* owner, GameManager* gm)
{
	mOwner = owner;
	mGameManager = gm;
	name = "BulletSite";
}

void BulletSite::Update()
{
	GameObject::UpdateComponents();
	mTimer += Timer::deltaTime;
}

void BulletSite::HandleCollision(GameObject* other)
{
}

void BulletSite::Deactivate()
{
}

void BulletSite::Shoot()
{
	if (mTimer < mFireRate)
		return;

	mTimer = 0;

	Bullet* bullet = nullptr;
	if (mOwner->name == "Player")
	{
		bullet = mGameManager->GetBulletFactory()->GetBullet();
		if (bullet == nullptr)
			return;
		bullet->SetSpeed(500.0f);
		bullet->GetComponent<Sprite>()->SetColor(255, 255, 255, 255);		
		bullet->name = "PlayerBullet";
	}
	else if (mOwner->name == "Enemy" || mOwner->name == "Enemy2" || mOwner->name == "Boss")
	{
		bullet = mGameManager->GetEnemyBulletFactory()->GetBullet();
		if (bullet == nullptr)
			return;
		bullet->SetSpeed(500.0f);
		bullet->GetComponent<Sprite>()->SetColor(255, 0, 255, 255);
		bullet->name = "EnemyBullet";
	}
	bullet->transform->position = transform->position;
	bullet->direction = mDirection;
	bullet->GetComponent<CircleCollider>()->Update();
	bullet->SetActive(true);
}