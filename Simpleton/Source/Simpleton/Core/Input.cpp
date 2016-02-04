//====================================================================================================
// Filename:	Input.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Input.h"

//====================================================================================================
// Statics
//====================================================================================================
Vector2 Input::mousePosition;
bool Input::mAnyKeyPressed = false;
std::unordered_map<int, bool> Input::mCurrentKeyState;
std::unordered_map<int, bool> Input::mPrevKeyState;

//====================================================================================================
// Class Definitions
//====================================================================================================

Input::Input()
{
}

//----------------------------------------------------------------------------------------------------

void Input::Update()
{
	// Loop through currentKeyState and copy it over to prevKeyState
	auto it = mCurrentKeyState.begin();
	for (; it != mCurrentKeyState.end(); ++it)
	{
		mPrevKeyState[it->first] = it->second;
	}
}

//----------------------------------------------------------------------------------------------------

void Input::PressKey(int key)
{
	mAnyKeyPressed = true;
	mCurrentKeyState[key] = true;
}

//----------------------------------------------------------------------------------------------------

void Input::ReleaseKey(int key)
{
	mAnyKeyPressed = false;
	mCurrentKeyState[key] = false;
}

//----------------------------------------------------------------------------------------------------

bool Input::KeyDown(int key)
{
	return mCurrentKeyState[key];
}

//----------------------------------------------------------------------------------------------------

//bool Input::KeyPressed(int key)
//{
//	if (KeyDown(key) && !WasKeyDown(key)) 
//	{
//		return true;
//	}
//	return false;
//}

//----------------------------------------------------------------------------------------------------

void Input::SetMouse(int x, int y)
{
	mousePosition.x = (float)x;
	mousePosition.y = (float)y;
}

//----------------------------------------------------------------------------------------------------

bool Input::WasKeyDown(int key)
{
	// Don't create a key if it doesnt exist.
	auto it = mPrevKeyState.find(key);
	if (it != mPrevKeyState.end()) 
	{
		return it->second;
	}
	else 
	{
		// Didn't find the key
		return false;
	}
}