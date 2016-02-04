//====================================================================================================
// Filename:	Cell.h
// Created by:	Johnny Wu
// Description:	Class for a Collision Grid-Based Partitioning
//====================================================================================================
#ifndef _PARTITIONCELL_H_
#define _PARTITIONCELL_H_

#include <iostream>
#include <unordered_set>

#include "Collider.h"
#include "GameObject.h"
#include "../Math/Rect.h"

class CollisionSystem;

//====================================================================================================
// Class Declaration
//====================================================================================================
class PartitionCell
{
	friend class CollisionSystem;
public:
	PartitionCell();
	~PartitionCell();
	
	void Initialize(CollisionSystem* colSys, int id, float x, float y, float w, float h);
	void Update();
	void CheckCollision();
	void DrawRect();

private:
	CollisionSystem* mColSystem;
	std::unordered_set<Collider*> mColliders;
	int mID;
	Rect mRect;
};

#endif //#ifndef _PARTITIONCELL_H_