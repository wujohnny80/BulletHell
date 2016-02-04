//====================================================================================================
// Filename:	Missile.h
// Created by:	Johnny Wu
// Description:	Class for a Missile.
//====================================================================================================
#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "../Core/CircleCollider.h"
#include "../Core/GameObject.h"
#include "../Core/Sprite.h"

#include <vector>
#include <queue>

class MissileFactory;

//====================================================================================================
// Class Declarations
//====================================================================================================
class Missile : public GameObject
{
	friend class MissileFactory;
public:
	Missile();
	virtual ~Missile();
	
	void Initilaize();
	virtual void Update() override;
	virtual void HandleCollision(GameObject* other) override;
	virtual void Deactivate() override;

	void SetSpeed(float s)		{ mSpeed = s; }
	void Spawn(Vector2 pos);

private:
	void UpdateMovement();
	void CheckBounds();
	void ClearQueue();
	
	// Components
	CircleCollider* mCollider;
	Sprite* mSprite;

	// Factory related
	MissileFactory* mMissileFactory;
	int mIndex;

	// Missile related	
	float mTimer;
	float mSpeed;

	// Path related
	float mT;
	float mDist;
	std::vector<Vector2> mPoints;
	std::queue<Vector2> mPath;
};

#endif // #ifndef _MISSILE_H_