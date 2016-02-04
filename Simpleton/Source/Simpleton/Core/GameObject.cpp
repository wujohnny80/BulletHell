//====================================================================================================
// Filename:	GameObject.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "GameObject.h"

//====================================================================================================
// Class Definitions
//====================================================================================================
GameObject::GameObject()
	: name("New GameObject")
	, layer(0)
	, mActive(true)
{
	AddComponent<Transform>();
	transform = GetComponent<Transform>();
}

GameObject::~GameObject()
{
	// Deallocate components
	auto it = mComponents.begin();
	for (; it != mComponents.end(); ++it)
	{
		delete it->second;
	}
	mComponents.clear();
}

void GameObject::UpdateComponents()
{
	auto it = mComponents.begin();
	for (; it != mComponents.end(); ++it)
	{
		it->second->Update();
	}
}


void GameObject::SetActive(bool a)
{
	mActive = a;
	auto it = mComponents.begin();
	for (; it != mComponents.end(); ++it)
	{
		it->second->enabled = mActive;
	}
}