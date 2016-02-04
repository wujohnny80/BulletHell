//====================================================================================================
// Filename:	Bullet.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Bullet.h"
#include "BulletFactory.h"
#include "GameManager.h"
#include "../Core/Application.h"
#include "../Core/Timer.h"
#include "../Math/Math.h"
#include <iostream>

//====================================================================================================
// Class Definitions
//====================================================================================================

Bullet::Bullet()
	: GameObject()
	, mCollider(nullptr)
	, mSprite(nullptr)
	, mBulletFactory(nullptr)
	, mIndex(-1)
	, direction(Vector2())
	, velocity(Vector2())
	, mSpeed(0.0f)
	, mTimer(0)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initilaize()
{
	mSprite = AddComponent<Sprite>();
	mSprite->SetTexture("bullet.png");
	mSprite->SetCentered(true);
	
	transform->position = Vector2(Application::screenWidth * 0.5f,
									Application::screenHeight * 0.5f);
	transform->scale = Vector2(2.0f, 2.0f);

	mCollider = AddComponent<CircleCollider>();
	mCollider->circle.radius = mSprite->Width() * 0.5f;

	layer = -1;
}

void Bullet::Update()
{
	if (!IsActive())
		return;

	UpdateComponents();

	velocity = direction * mSpeed;
	transform->position += velocity * Timer::deltaTime;
	
	CheckBounds();
}

void Bullet::HandleCollision(GameObject* other)
{
	// If I am Player's bullet and I hit an enemy, kill the other
	if (other->name == "Enemy" && name == "PlayerBullet")
	{
		other->Deactivate();
		Deactivate();
	}
	if (other->name == "Enemy2" && name == "PlayerBullet")
	{
		other->Deactivate();
		Deactivate();
	}
	if (other->name == "Boss" && name == "PlayerBullet")
	{
		other->Deactivate();
		Deactivate();
	}

	// If I am Enemy bullet and I hit a player
	if (other->name == "Player" && name == "EnemyBullet")
	{
		other->Deactivate();
		Deactivate();
	}
}

void Bullet::Deactivate()
{
	if (mBulletFactory == nullptr)
		return;

	mBulletFactory->ReturnBullet(this);
}

void Bullet::CheckBounds()
{
	// Right/Left walls
	if (transform->position.x < -mSprite->Width() * 0.5f)
	{
		Deactivate();
	}
	else if (transform->position.x > Application::screenWidth + mSprite->Width() * 0.5f)
	{
		Deactivate();
	}
	// Top/Bottom walls
	if (transform->position.y < -mSprite->Height() * 0.5f)
	{
		Deactivate();
	}
	else if	(transform->position.y > Application::screenHeight + mSprite->Height() * 0.5f)
	{
		Deactivate();
	}
}

void Bullet::BounceWall()
{	
	// Right/Left walls
	if (transform->position.x < mSprite->Width() * 0.5f)
	{
		transform->position.x = mSprite->Width() * 0.5f;
		direction = Vector2(-direction.x, direction.y);
	}
	else if (transform->position.x > Application::screenWidth - mSprite->Width() * 0.5f)
	{
		transform->position.x = Application::screenWidth - mSprite->Width() * 0.5f;
		direction = Vector2(-direction.x, direction.y);
	}
	// Top/Bottom walls
	if (transform->position.y < mSprite->Height() * 0.5f)
	{
		transform->position.y = mSprite->Height() * 0.5f;
		direction = Vector2(direction.x, -direction.y);
	}
	else if	(transform->position.y > Application::screenHeight - mSprite->Height() * 0.5f)
	{
		transform->position.y = Application::screenHeight - mSprite->Height() * 0.5f;
		direction = Vector2(direction.x, -direction.y);
	}
}

void Bullet::BounceBullet(Bullet* other)
{
	Vector2 thisColDir = -((other->transform->position - transform->position).Normalized());
	direction += thisColDir;
	direction = direction.Normalized();

	Vector2 otherColDir = -((transform->position - other->transform->position).Normalized());
	other->direction += otherColDir;
	other->direction = other->direction.Normalized();
}