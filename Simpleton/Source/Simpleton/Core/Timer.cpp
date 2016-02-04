//====================================================================================================
// Filename:	Timer.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Timer.h"

#include <stdio.h>

//====================================================================================================
// Statics
//====================================================================================================
float Timer::deltaTime = 0.0f;
float Timer::FPS = 0.0f;
float Timer::time = 0.0f;

Timer::Timer()
	: mTicksPerSecond(0)
	, mLastTick(0)
	, mCurrentTick(0)
{
}

void Timer::Update()
{
	mCurrentTick = SDL_GetTicks(); // Gives time in milliseconds
	deltaTime = (mCurrentTick - mLastTick) * 0.001f; // Get deltaTime in seconds
	mLastTick = mCurrentTick; // Set lastTick
	time += deltaTime;	// Add to time

	static float s_FrameSinceLastSecond = 0.0f;
	static float s_AccumulatedTime = 0.0f;

	// Calculate the FPS
	s_AccumulatedTime += deltaTime;
	s_FrameSinceLastSecond += 1.0f;

	// Update FPS is one second has passed
	if (s_AccumulatedTime>= 1.0f)
	{
		FPS = s_FrameSinceLastSecond / s_AccumulatedTime;
		s_AccumulatedTime = 0.0f;
		s_FrameSinceLastSecond = 0.0f;
	}
}