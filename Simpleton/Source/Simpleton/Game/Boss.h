//====================================================================================================
// Filename:	Boss.h
// Created by:	Johnny Wu
// Description:	Class for a Boss.
//====================================================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "BulletSite.h"

#include "../Core/CircleCollider.h"
#include "../Core/GameObject.h"
#include "../Core/Sprite.h"

class GameManager;

//====================================================================================================
// Class Declarations
//====================================================================================================
class Boss : public GameObject
{
public:
	Boss();
	virtual ~Boss();
	
	void Initialize(GameManager* gm);
	virtual void Update() override;
	virtual void HandleCollision(GameObject* other) override;
	virtual void Deactivate() override;

private:
	void UpdateMovement();
	void Shoot();
	
	// Components
	GameManager* mGameManager;
	Sprite* mSprite;
	CircleCollider* mCollider;
	
	std::vector<BulletSite*> mBulletSites;
	
	int mMaxHealth;
	int mCurrentHealth;
	int mBulletSiteCount;
	float mSpeed;
};

#endif // #ifndef _BOSS_H_