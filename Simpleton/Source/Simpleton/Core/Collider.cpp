//====================================================================================================
// Filename:	Collider.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Collider.h"
#include "CollisionSystem.h"
#include "GameObject.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
Collider::Collider()
	: Component()
{
	// Add to collision system
	CollisionSystem::Instance().AddCollider(this);
}

Collider::~Collider()
{
	CollisionSystem::Instance().RemoveCollider(this);
}