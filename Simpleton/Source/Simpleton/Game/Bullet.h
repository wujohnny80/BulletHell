//====================================================================================================
// Filename:	Bullet.h
// Created by:	Johnny Wu
// Description:	Class for a Bullet.
//====================================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "../Core/CircleCollider.h"
#include "../Core/GameObject.h"
#include "../Core/Sprite.h"

class BulletFactory;

//====================================================================================================
// Class Declarations
//====================================================================================================
class Bullet : public GameObject
{
	friend class BulletFactory;
public:
	Bullet();
	virtual ~Bullet();

	void Initilaize();
	virtual void Update() override;
	virtual void HandleCollision(GameObject* other) override;
	virtual void Deactivate() override;
	void SetSpeed(float s)		{ mSpeed = s; }

	Vector2 direction;
	Vector2 velocity;

private:
	void CheckBounds();
	void BounceWall();
	void BounceBullet(Bullet* other);
	
	// Components
	CircleCollider* mCollider;
	Sprite* mSprite;

	// Factory related
	BulletFactory* mBulletFactory;
	int mIndex;

	// Bullet related
	float mSpeed;
	float mTimer;
};

#endif // #ifndef _BULLET_H_