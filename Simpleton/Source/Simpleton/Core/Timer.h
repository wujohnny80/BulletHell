//====================================================================================================
// Filename:	Timer.h
// Created by:	Johnny Wu
// Description:	Singleton class for hi-res timer. It tracks the time elapsed between each Update()
//				call and the total number of times Update() is called every second.
//====================================================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include <SDL.h>

class Timer
{
	friend class Application;
public:
	static Timer& Instance()		{ static Timer instance; return instance; }
	
	// Statics
	static float deltaTime;
	static float FPS;
	static float time;

private:
	Timer();
	Timer(Timer const&);			// Don't implement
	void operator=(Timer const&);	// Don't implement

	void Update();

	unsigned int mTicksPerSecond;
	unsigned int mLastTick;
	unsigned int mCurrentTick;
};

#endif // #ifndef _TIMER_H_