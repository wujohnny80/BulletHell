//====================================================================================================
// Filename:	Collider.h
// Created by:	Johnny Wu
// Description:	Base class for 2D colliders
//====================================================================================================
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include <map>
#include <typeinfo>
#include <string>

#include "Component.h"
#include "../Math/Vector2.h"

//====================================================================================================
// Class Declarations
//====================================================================================================
class Collider : public Component
{
public:
	Collider();
	virtual ~Collider();
	
	virtual void Update() {};
	virtual bool IsColliding(Collider* other) = 0;
};

#endif // #ifndef _COLLIDER_H_