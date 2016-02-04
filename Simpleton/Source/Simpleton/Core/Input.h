//====================================================================================================
// Filename:	Input.h
// Created by:	Johnny Wu
// Description:	Class for the input system.
//====================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include <unordered_map>

#include "Application.h"
#include "InputTypes.h"
#include "../Math/Math.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class Input
{
	friend class Application;
public:
	static Input& Instance()	{ static Input instance; return instance; }
	
	static bool AnyKeyPressed()	{ return mAnyKeyPressed; }

	// Functions to query for a key state
	static bool KeyDown(int key);
	//bool KeyPressed(int key);
	
	// Functions to query for a mouse state
	static bool MouseDown();
	static bool MousePressed();
	static Vector2 mousePosition;

private:
	Input();
	Input(Input const&);		// Don't implement
	void operator=(Input const&);	// Don't implement

	void Update();

	void PressKey(int key);
	void ReleaseKey(int key);
	bool WasKeyDown(int key);
	
	void SetMouse(int x, int y);

	static std::unordered_map<int, bool> mCurrentKeyState;
	static std::unordered_map<int, bool> mPrevKeyState;

	// Statics
	static bool mAnyKeyPressed;
};

#endif // #ifndef _INPUT_H_