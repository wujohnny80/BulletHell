//====================================================================================================
// Filename:	Component.h
// Created by:	Johnny Wu
// Description:	Base class for any Components to be attached to GameObjects.
//====================================================================================================
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <string>

class GameObject;

//====================================================================================================
// Class Declarations
//====================================================================================================
class Component
{
public:
	Component()
		: enabled(false)
		, gameObject(nullptr)
	{}
	virtual ~Component() {}
	virtual void Update() = 0;

	// Public variables
	bool enabled;
	GameObject* gameObject;
};

#endif // #ifndef _COMPONENT_H_