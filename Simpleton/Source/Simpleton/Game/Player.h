//====================================================================================================
// Filename:	Player.h
// Created by:	Johnny Wu
// Description:	Class for a Player.
//====================================================================================================
#ifndef _Player_H_
#define _Player_H_

#include "BulletSite.h"
#include "MissileFactory.h"

#include "../Core/CircleCollider.h"
#include "../Core/GameObject.h"
#include "../Core/Sprite.h"

#include <vector>

class GameManager;

//====================================================================================================
// Class Declarations
//====================================================================================================
class Player : public GameObject
{
public:
	Player();
	virtual ~Player();
	
	void Initialize(GameManager* gm);
	virtual void Update() override;
	virtual void HandleCollision(GameObject* other) override;
	virtual void Deactivate() override;

private:
	void UpdateInput();
	void Shoot();
	void FireMissile();
	void CheckBounds();

	GameManager* mGameManager;
	CircleCollider* mCollider;
	Sprite* mSprite;

	std::vector<BulletSite*> mBulletSites;
	MissileFactory* mMissileFactory;

	int mBulletSiteCount;
	float mSpeed;
};

#endif // #ifndef _Player_H_