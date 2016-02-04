//====================================================================================================
// Filename:	CircleCollider.h
// Created by:	Johnny Wu
// Description:	Class for circle colliders
//====================================================================================================
#ifndef _CIRCLECOLLIDER_H_
#define _CIRCLECOLLIDER_H_

#include "Collider.h"
#include "../Math/Circle.h"
#include "../Math/Math.h"

//====================================================================================================
// Class Declarations
//====================================================================================================
class CircleCollider : public Collider
{
public:
	CircleCollider();
	~CircleCollider();
	
	virtual void Update();
	virtual bool IsColliding(Collider* other);
	Circle circle;
};

#endif // #ifndef _CIRCLECOLLIDER_H_