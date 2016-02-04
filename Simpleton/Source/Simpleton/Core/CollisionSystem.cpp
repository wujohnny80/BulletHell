//====================================================================================================
// Filename:	CollisionSystem.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "CollisionSystem.h"
#include "Application.h"
#include "Sprite.h"

#include <cmath>
//====================================================================================================
// Class Definitions
//====================================================================================================
CollisionSystem::CollisionSystem()
	: mCellWidth(0)
	, mCellHeight(0)
	, mColms(0)
	, mRows(0)
{
}

void CollisionSystem::Initialize(PartitionType partition, float minWidth, float minHeight)
{
	mPartitionType = partition;
	switch(mPartitionType)
	{
	case Cell:
		{
			mCellWidth = minWidth;
			mCellHeight = minHeight;
			mColms = (int)ceil((float)Application::screenWidth / mCellWidth);
			mRows = (int)ceil((float)Application::screenHeight / mCellHeight);
			int numCells = mColms * mRows + 1;

			mCells.resize(numCells);

			// Initialize cells
			unsigned int cellCount = mCells.size();
			for (unsigned int i = 0; i < cellCount; ++i)
			{
				float x = (i % mColms) * mCellWidth;
				float y = (i / mColms) * mCellHeight;
				mCells[i].Initialize(this, i, x, y, mCellWidth, mCellHeight);
			}

			// Put each object in the appropriate cell
			auto it = mColliders.begin();
			for (; it != mColliders.end(); ++it)
			{
				InsertToCell(*it);
			}
		}
		break;
	case QuadTree:
		{
			mQuadTree.Initialize(Application::screenWidth,
								Application::screenHeight,
								8,
								minWidth,
								minHeight);
		}
		break;
	default:
		break;
	}
}

void CollisionSystem::Update()
{
	switch(mPartitionType)
	{
	case Cell:
		{
			unsigned int cellCount = mCells.size();
			for (unsigned int i = 0; i < cellCount; ++i)
			{
				mCells[i].Update();
				if (Application::debugMode)
					mCells[i].DrawRect();
			}
			for (unsigned int j = 0; j < cellCount - 1; ++j)
			{
				mCells[j].CheckCollision();
			}
		}
		break;
	case QuadTree:
		{
			auto it = mColliders.begin();
			for (; it != mColliders.end(); ++it)
			{
				if ((*it)->enabled)
					mQuadTree.Insert(*it);
			}
			mQuadTree.Update();
			mQuadTree.Clear();
		}
		break;
	default:
		break;
	}
}

void CollisionSystem::Terminate()
{
	mColliders.clear();
}

void CollisionSystem::AddCollider(Collider* collider)
{
	mColliders.emplace(collider);
}

void CollisionSystem::RemoveCollider(Collider* collider)
{
	auto it = mColliders.begin();
	for(;it != mColliders.end(); ++it)
	{
		if ((*it) == collider)
		{
			mColliders.erase(it);
		}
	}
}

int CollisionSystem::Hash(Vector2 point)
{
	int colm = (int)(point.x / mCellWidth);
	int row = (int)(point.y / mCellHeight);

	if (row < 0 || row >= mRows)
		return mCells.size() - 1;
	if (colm < 0 || colm >= mColms)
		return mCells.size() - 1;

	return colm + row * mColms;
}

void CollisionSystem::InsertToCell(Collider* col)
{	
	Vector2 TL = col->gameObject->GetComponent<Sprite>()->TopLeft();
	Vector2 TR = col->gameObject->GetComponent<Sprite>()->TopLeft();
	TR.x += col->gameObject->GetComponent<Sprite>()->Width();
	Vector2 BL = col->gameObject->GetComponent<Sprite>()->TopLeft();
	BL.y += col->gameObject->GetComponent<Sprite>()->Height();
	Vector2 BR = col->gameObject->GetComponent<Sprite>()->BottomRight();

	int index1 = Hash(TL);
	int index2 = Hash(TR);
	int index3 = Hash(BL);
	int index4 = Hash(BR);

	mCells[index1].mColliders.emplace(col);
	mCells[index2].mColliders.emplace(col);
	mCells[index3].mColliders.emplace(col);
	mCells[index4].mColliders.emplace(col);
}