//====================================================================================================
// Filename:	PartitionCell.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "PartitionCell.h"
#include "Application.h"
#include "CollisionSystem.h"
#include "Sprite.h"

#include <iostream>
#include <string>

//====================================================================================================
// Class Definitions
//====================================================================================================
PartitionCell::PartitionCell()
	: mColSystem(nullptr)
	, mID(-1)
	, mRect(Rect())
{
}

PartitionCell::~PartitionCell()
{
	mColliders.clear();
}

void PartitionCell::Initialize(CollisionSystem* colSys, int id, float x, float y, float w, float h)
{
	mColSystem = colSys;
	mID = id;
	mRect.x = x;
	mRect.y = y;
	mRect.w = w;
	mRect.h = h;
}

void PartitionCell::Update()
{
	std::unordered_set<Collider*> toRemove;

	auto it = mColliders.begin();
	for (; it != mColliders.end(); ++it)
	{
		if (!(*it)->enabled)
			continue;

		Vector2 TL = (*it)->gameObject->GetComponent<Sprite>()->TopLeft();
		Vector2 TR = (*it)->gameObject->GetComponent<Sprite>()->TopLeft();
		TR.x += (*it)->gameObject->GetComponent<Sprite>()->Width();
		Vector2 BL = (*it)->gameObject->GetComponent<Sprite>()->TopLeft();
		BL.y += (*it)->gameObject->GetComponent<Sprite>()->Height();
		Vector2 BR = (*it)->gameObject->GetComponent<Sprite>()->BottomRight();

		if (mColSystem->Hash(TL) != mID &&
			mColSystem->Hash(TR) != mID &&
			mColSystem->Hash(BL) != mID &&
			mColSystem->Hash(BR) != mID)
		{
			mColSystem->InsertToCell((*it));
			toRemove.emplace(*it);
		}
	}

	auto it2 = toRemove.begin();
	for (; it2 != toRemove.end(); ++it2)
	{
		mColliders.erase(*it2);
	}
}

void PartitionCell::CheckCollision()
{
	auto it = mColliders.begin();
	for (; it != mColliders.end(); ++it)
	{
		if (!(*it)->enabled)
			continue;

		auto next = it;
		++next;
		for (; next != mColliders.end(); ++next)
		{
			if (!(*next)->enabled)
				continue;
			
			// DEBUG DRAW
			if (Application::debugMode)
			{
				SDL_Color c = {255, 0, 0, 50};
				mRect.DebugDraw(c, true);
			}

			if ((*it)->IsColliding(*next))
				(*it)->gameObject->HandleCollision((*next)->gameObject);
		}
	}
}

void PartitionCell::DrawRect()
{
	SDL_Color c = {255, 0, 0, 255};
	mRect.DebugDraw(c, false);
}