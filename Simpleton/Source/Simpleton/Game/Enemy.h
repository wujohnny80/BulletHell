//====================================================================================================
// Filename:	Enemy.h
// Created by:	Johnny Wu
// Description:	Class for a Enemy.
//====================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "BulletSite.h"

#include "../Core/CircleCollider.h"
#include "../Core/GameObject.h"
#include "../Core/Sprite.h"

#include <vector>
#include <string>

class GameManager;

//====================================================================================================
// Class Declarations
//====================================================================================================
class Enemy : public GameObject
{
public:
	Enemy();
	virtual ~Enemy();
	
	void Initialize(GameManager* gm);
	virtual void Update() override;
	virtual void HandleCollision(GameObject* other) override;
	virtual void Deactivate() override;

private:
	void UpdateMovement();
	void Shoot();
	void CheckBounds();

	// Components
	GameManager* mGameManager;
	Sprite* mSprite;
	CircleCollider* mCollider;
	std::vector<BulletSite*> mBulletSites;
	
	int mBulletSiteCount;
	float mSpeed;
	int mCurrentHealth;
	int mMaxHealth;
};

#endif // #ifndef _ENEMY_H_