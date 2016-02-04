//====================================================================================================
// Filename:	AnimationState.h
// Created by:	Johnny Wu
// Description:	Base struct for a 2D AnimationState.
//====================================================================================================
#ifndef _ANIMATIONSTATE_H_
#define _ANIMATIONSTATE_H_

//====================================================================================================
// Class Declarations
//====================================================================================================
struct AnimationState
{
	// Assumptions:
	// Each frame has same width, height. An animation is on a single row of an image
	// All animation are on the same image
	// x, y is the top-left position of frame 0

	std::string name;
	int x, y, w, h, frameCount, fps;
};

#endif // #ifndef _ANIMATIONSTATE_H_