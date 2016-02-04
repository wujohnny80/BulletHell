//====================================================================================================
// Filename:	CollisionQuadTree.h
// Created by:	Johnny Wu
// Description:	Class for a Collision QuadTree
//====================================================================================================
#ifndef _COLLISIONQUADTREE_H_
#define _COLLISIONQUADTREE_H_

#include <iostream>
#include <vector>

#include "Collider.h"
#include "GameObject.h"
#include "../Math/Rect.h"

//====================================================================================================
// Class Declaration
//====================================================================================================
class CollisionQuadTree
{
public:
	CollisionQuadTree();
	~CollisionQuadTree();

	void Initialize(int boundX, int boundY, unsigned int maxObj, float minWidth, float minHeight);
	void Insert(Collider* col);
	void Clear();
	void Update();

private:
	class Quad
	{
	public:
		Quad();
		~Quad();
		
		Quad& operator=(const Quad&) {return *this;}
		
		void Insert(Collider* col);
		void Clear();
		void Update();
		void Split();
		bool InBounds(Collider* col);
		
		unsigned int mMaxObjs;
		float mMinW;
		float mMinH;
		bool mSplit;
		Rect mBounds;
		std::vector<Collider*> mCols;
		std::vector<Quad*> mChildren;

	}; // End of Class Node

	Quad mRoot;
}; // End of Class CollisionQuadTree

#endif //#ifndef _COLLISIONQUADTREE_H_