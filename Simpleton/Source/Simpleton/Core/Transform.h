//====================================================================================================
// Filename:	Transform.h
// Created by:	Johnny Wu
// Description:	Class for a 2D Transform Component.
//====================================================================================================
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Component.h"
#include "../Math/Vector2.h"

#include <vector>

//====================================================================================================
// ***NOTE***
// Current set-up has inefficiency where any transform that has a parent will be called N times based
// on how deep the heirarchy it is at.
//		To fix this:
// Set up so that transform will only update its localPosition, and call a special function which only
// gets called on the root Transform. This function will update all of its childrens position recursively
//====================================================================================================

//====================================================================================================
// Class Declarations
//====================================================================================================
class Transform : public Component
{
public:
	Transform();
	//Transform(Transform* p = &root);
	~Transform();

	virtual void Update();
	// UpdateChildren();
	void SetParent(Transform* t);
	const std::vector<Transform*>& GetChildren() const		{ return mChildren; }
	void AddChild(Transform* t);

	// Static
	static Transform root;

	// Public variables	
	Vector2 position;
	Vector2 localPosition;
	Vector2 scale;
	Transform* parent;

private:
	std::vector<Transform*> mChildren;
};

#endif // #ifndef _TRANSFORM_H_