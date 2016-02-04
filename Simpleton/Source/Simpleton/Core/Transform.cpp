//====================================================================================================
// Filename:	Transform.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Transform.h"

//====================================================================================================
// Statics
//====================================================================================================
Transform Transform::root;

//====================================================================================================
// Class Definitions
//====================================================================================================
Transform::Transform()
	: position(Vector2())
	, localPosition(Vector2())
	, scale(Vector2(1.0f, 1.0f))
{
	parent = &root != this ? &root : nullptr;
	if (this != &root)
		root.AddChild(this);
}

Transform::~Transform()
{
}

void Transform::Update()
{
	position += parent->position + localPosition;
	int size = mChildren.size();
	for (int i = 0; i < size; ++i)
	{
		mChildren[i]->position = position + mChildren[i]->localPosition;
	}
}

void Transform::AddChild(Transform* t)
{
	mChildren.push_back(t);
}

void Transform::SetParent(Transform* t)
{
	parent = t;
	parent->AddChild(this);
}