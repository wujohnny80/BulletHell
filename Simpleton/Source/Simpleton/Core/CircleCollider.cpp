//====================================================================================================
// Filename:	CircleCollider.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"

#include <iostream>
#include <typeinfo>

//====================================================================================================
// Class Definitions
//====================================================================================================
CircleCollider::CircleCollider()
	: circle(Circle())
{
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
	circle.center = gameObject->transform->position;
}

bool CircleCollider::IsColliding(Collider* other)
{
	if (typeid(*other) == typeid(*this))
	{
		// Do circle circle check
		CircleCollider* col = static_cast<CircleCollider*>(other);
		return Math::Intersect(circle, col->circle);
	}
	else if (typeid(*other) == typeid(BoxCollider*))
	{
		// Do box circle check
		BoxCollider* col = static_cast<BoxCollider*>(other);
		return Math::Intersect(circle, col->rect);
	}
	else
		return false;
}