//====================================================================================================
// Filename:	BulletSite.h
// Created by:	Johnny Wu
// Description:	Class for a BulletSite.
//====================================================================================================
#ifndef _BULLETSITE_H_
#define _BULLETSITE_H_

#include "../Core/GameObject.h"

class GameManager;

//====================================================================================================
// Class Declarations
//====================================================================================================
class BulletSite : public GameObject
{
public:
	BulletSite();
	virtual ~BulletSite();
	
	void Initialize(GameObject* owner, GameManager* gm);
	virtual void Update() override;
	virtual void HandleCollision(GameObject* other) override;
	virtual void Deactivate() override;

	void Shoot();
	void SetFireRate(float r)		{ mFireRate = r; }
	void SetDirection(Vector2 dir)	{ mDirection = dir; }

private:
	GameManager* mGameManager;
	GameObject* mOwner;
	Vector2 mDirection;
	float mFireRate;
	float mTimer;
};

#endif // #ifndef _BULLETSITE_H_