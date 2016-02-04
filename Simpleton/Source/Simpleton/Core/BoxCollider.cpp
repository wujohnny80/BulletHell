//====================================================================================================
// Filename:	BoxCollider.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "GameObject.h"

#include <typeinfo>

//====================================================================================================
// Class Definitions
//====================================================================================================
BoxCollider::BoxCollider()
	: rect(Rect())
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Update()
{	
	rect.x = gameObject->transform->position.x - 0.5f;
	rect.y = gameObject->transform->position.y - 0.5f;
}

bool BoxCollider::IsColliding(Collider* other)
{
	if (typeid(*other) == typeid(*this))
	{
		// Do box box check
		BoxCollider* col = static_cast<BoxCollider*>(other);
		return Math::Intersect(rect, col->rect);
	}
	else if (typeid(*other) == typeid(CircleCollider*))
	{
		// Do box circle check
		CircleCollider* col = static_cast<CircleCollider*>(other);
		return Math::Intersect(rect, col->circle);
	}
	else
		return false;
}