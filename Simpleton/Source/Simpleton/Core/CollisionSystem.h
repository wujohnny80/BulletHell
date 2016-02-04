//====================================================================================================
// Filename:	CollisionSystem.h
// Created by:	Johnny Wu
// Description:	Singleton class for collision system.
//====================================================================================================
#ifndef _COLLISIONSYSTEM_H_
#define _COLLISIONSYSTEM_H_

#include <vector>
#include <unordered_set>

#include "PartitionCell.h"
#include "Collider.h"
#include "CollisionQuadTree.h"

//====================================================================================================
// Class Declarations
//====================================================================================================
class CollisionSystem
{
	friend class Application;
public:
	static CollisionSystem& Instance()	{ static CollisionSystem instance; return instance; }
	
	void AddCollider(Collider* collider);
	void RemoveCollider(Collider* collider);
	int Hash(Vector2 point);
	void InsertToCell(Collider* col);

	enum PartitionType
	{
		None = 0,
		Cell,
		QuadTree	// By default, max objects per quad is 8
	};

private:
	CollisionSystem();
	CollisionSystem(CollisionSystem const&);	// Don't implement
	void operator=(CollisionSystem const&);		// Don't implement

	void Initialize(PartitionType partition, float minWidth, float minHeight);
	void Update();
	void Terminate();
	
	std::unordered_set<Collider*> mColliders;
	PartitionType mPartitionType;
	CollisionQuadTree mQuadTree;
	std::vector<PartitionCell> mCells;
	float mCellWidth;
	float mCellHeight;
	int mColms;
	int mRows;
};

#endif // #ifndef _CollisionSystem_H_