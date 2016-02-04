//====================================================================================================
// Filename:	CollisionQuadTree.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "CollisionQuadTree.h"
#include "Application.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

#include <iostream>
#include <typeinfo>
#include <string>

//====================================================================================================
// Class Definitions
//====================================================================================================
CollisionQuadTree::CollisionQuadTree()
{
}

CollisionQuadTree::~CollisionQuadTree()
{
	Clear();
}

void CollisionQuadTree::Initialize(int boundX, int boundY, unsigned int maxObj, float minWidth, float minHeight)
{
	mRoot.mBounds.w = (float)boundX;
	mRoot.mBounds.h = (float)boundY;
	mRoot.mMaxObjs = maxObj;
	mRoot.mMinW = minWidth;
	mRoot.mMinH = minHeight;
}

void CollisionQuadTree::Insert(Collider* col)
{
	mRoot.Insert(col);
}

void CollisionQuadTree::Clear()
{
	mRoot.Clear();
}

void CollisionQuadTree::Update()
{
	mRoot.Update();
}

CollisionQuadTree::Quad::Quad()
	: mMaxObjs(0)
	, mMinW(0.0f)
	, mMinH(0.0f)
	, mSplit(false)
	, mBounds(Rect())
{
}

CollisionQuadTree::Quad::~Quad()
{
	Clear();
}

void CollisionQuadTree::Quad::Insert(Collider* col)
{
	if (!mSplit)
	{
		mCols.push_back(col);
		if (mCols.size() >= mMaxObjs)
			Split();
	}
	else
	{
		// Assign to the proper quadrants
		for (unsigned int i = 0; i < mChildren.size(); ++i)
		{
			if (mChildren[i]->InBounds(col))
				mChildren[i]->Insert(col);
		}
	}
}

void CollisionQuadTree::Quad::Clear()
{
	for(unsigned int i = 0; i < mChildren.size(); ++i)
	{
		delete mChildren[i];
		mChildren[i] = nullptr;
	}
	mChildren.clear();
	mCols.clear();
	mSplit = false;
	mBounds = Rect();
	mBounds.w = (float)Application::screenWidth;
	mBounds.h = (float)Application::screenHeight;
}

void CollisionQuadTree::Quad::Update()
{
	// DEBUG DRAW
	if (Application::debugMode && mBounds.w != Application::screenWidth)
	{
		SDL_Color c = {255, 0, 0, 255};
		mBounds.DebugDraw(c, false);
	}

	if (mSplit)
	{
		unsigned int s = mChildren.size();
		for (unsigned int i = 0; i < s; ++i)
		{
			mChildren[i]->Update();
		}
	}
	else
	{
		// Check Collisions
		unsigned int s = mCols.size();

		// Don't bother when there's only 1 collider in the quad
		if (s <= 1)
			return;

		for (unsigned int i = 0; i < s; ++i)
		{
			if (!mCols[i]->enabled)
				continue;
			for (unsigned int j = i + 1; j < s; ++j)
			{
				if (!mCols[j]->enabled)
					continue;

				// DEBUG DRAW
				if (Application::debugMode && mBounds.w != Application::screenWidth)
				{
					SDL_Color c = {255, 0, 0, 5};
					mBounds.DebugDraw(c, true);
				}

				if (mCols[i]->IsColliding(mCols[j]))
					mCols[i]->gameObject->HandleCollision(mCols[j]->gameObject);
			}
		}
	}
}

void CollisionQuadTree::Quad::Split()
{
	// Ignore split if already reached min bounds;
	if (mBounds.w < mMinW || mBounds.h < mMinH)
		return;

	mSplit = true;
	mChildren.resize(4);

	// Create children
	for (int i = 0; i < 4; ++i)
	{
		mChildren[i] = new Quad();
		mChildren[i]->mBounds.x = mBounds.x + (i % 2) * mBounds.w * 0.5f;
		mChildren[i]->mBounds.y = mBounds.y + (i / 2) * mBounds.h * 0.5f;
		mChildren[i]->mBounds.w = mBounds.w * 0.5f;
		mChildren[i]->mBounds.h = mBounds.h * 0.5f;
		mChildren[i]->mMaxObjs = mMaxObjs;
		mChildren[i]->mMinW = mMinW;
		mChildren[i]->mMinH = mMinH;
	}

	// Pass objs to kids
	for (unsigned int i = 0; i < mCols.size(); ++i)
	{
		Insert(mCols[i]);
	}

	mCols.clear();
}

bool CollisionQuadTree::Quad::InBounds(Collider* col)
{
	float minX = 0;
	float maxX = 0;
	float minY = 0;
	float maxY = 0;

	if (typeid(*col) == typeid(CircleCollider))
	{
		CircleCollider* ccol = static_cast<CircleCollider*>(col);
		minX = ccol->circle.center.x - ccol->circle.radius;
		maxX = ccol->circle.center.x + ccol->circle.radius;
		minY = ccol->circle.center.y - ccol->circle.radius;
		maxY = ccol->circle.center.y + ccol->circle.radius;
	}
	else if (typeid(*col) == typeid(BoxCollider))
	{
		BoxCollider* bcol = static_cast<BoxCollider*>(col);
		minX = bcol->rect.x;
		maxX = bcol->rect.Max().x;
		minY = bcol->rect.y;
		maxY = bcol->rect.Max().y;
	}

	// Check colliders position
	if (minX > mBounds.Max().x)
	{
		return false;
	}
	if (maxX < mBounds.x)
	{
		return false;
	}
	if (minY > mBounds.Max().y)
	{
		return false;
	}
	if (maxY < mBounds.y)
	{
		return false;
	}
	return true;
}