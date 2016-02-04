//====================================================================================================
// Filename:	Enemy2.h
// Created by:	Johnny Wu
// Description:	Class for a Enemy2.
//====================================================================================================
#ifndef _ENEMY2_H_
#define _ENEMY2_H_

#include "BulletSite.h"

#include "../Core/CircleCollider.h"
#include "../Core/GameObject.h"
#include "../Core/Sprite.h"

#include <vector>
#include <string>

class Enemy2ShipFactory;
class GameManager;

//====================================================================================================
// Class Declarations
//====================================================================================================
class Enemy2 : public GameObject
{
	friend class Enemy2ShipFactory;
public:
	Enemy2();
	virtual ~Enemy2();
	
	void Initialize(GameManager* gm);
	virtual void Update() override;
	virtual void HandleCollision(GameObject* other) override;
	virtual void Deactivate() override;

private:
	void UpdateMovement();
	void Shoot();
	void CheckBounds();
	static void InitializePath();

	// Components
	GameManager* mGameManager;
	Sprite* mSprite;
	CircleCollider* mCollider;
	std::vector<BulletSite*> mBulletSites;

	// Factory related
	//EnemyShipFactory* mShipFactory;
	int mIndex;
	
	int mBulletSiteCount;
	float mSpeed;
	int mCurrentHealth;
	int mMaxHealth;

	// Pathing related
	static std::vector<Vector2> sPoints;
	std::vector<Vector2> mPath;

	Vector2 mStart;
	Vector2 mEnd;
	int mCurrentWaypoint;
	float mT;
	float mDist;
	int mLevel;
	int mNumBranches;
};

#endif // #ifndef _ENEMY2_H_