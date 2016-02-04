//====================================================================================================
// Filename:	BoxCollider.h
// Created by:	Johnny Wu
// Description:	Class for box colliders
//====================================================================================================
#ifndef _BOXCOLLIDER_H_
#define _BOXCOLLIDER_H_

#include "Collider.h"
#include "../Math/Rect.h"
#include "../Math/Math.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class BoxCollider : public Collider
{
public:
	BoxCollider();
	~BoxCollider();
	
	virtual void Update();
	virtual bool IsColliding(Collider* other);
	Rect rect;
};

#endif // #ifndef _BOXCOLLIDER_H_