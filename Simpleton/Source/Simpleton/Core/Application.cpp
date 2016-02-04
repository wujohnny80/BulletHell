//====================================================================================================
// Filename:	Application.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Application.h"

#include <assert.h>
#include <stdio.h>

#include "CollisionSystem.h"
#include "Graphics.h"
#include "Input.h"
#include "Timer.h"
#include "TextureManager.h"

//====================================================================================================
// Statics
//====================================================================================================
int Application::screenWidth = 0;
int Application::screenHeight = 0;
bool Application::debugMode = 0;

//====================================================================================================
// Class Definition
//====================================================================================================
Application::Application()
	: mpWindow(nullptr)
{
}

Application::~Application()
{
}

void Application::Initialize(const char* appName, int width, int height, bool debug)
{
	// Cache window dimesion
	screenWidth = width;
	screenHeight = height;
	debugMode = debug;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}

	// Create window
	mpWindow = SDL_CreateWindow(appName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if(mpWindow == nullptr)
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	// Create and initialize all engine systems
	Graphics::Instance().Initialize(mpWindow);

	// User init logic
	InitGame();
	
	// Init Collision system
	CollisionSystem::Instance().Initialize(CollisionSystem::PartitionType::QuadTree, 64, 64);
}

void Application::Update()
{
	SDL_Event evnt;
	bool isRunning = true;
	while (isRunning)
	{
		// Update Timer
		Timer::Instance().Update();
	
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type) 
			{
			case SDL_QUIT:
				SDL_Quit();
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				Input::Instance().PressKey(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				Input::Instance().ReleaseKey(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				Input::Instance().SetMouse(evnt.motion.x, evnt.motion.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				Input::Instance().PressKey(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				Input::Instance().ReleaseKey(evnt.button.button);
				break;
			}
		}

		// Update Input
		Input::Instance().Update();

		// Begin scene
		Graphics::Instance().BeginRender();

		// User update logic
		RunGame();

		// Update Collision
		CollisionSystem::Instance().Update();

		// End scene
		Graphics::Instance().EndRender();
	}
}

void Application::Terminate()
{
	// Shutdown all engine systems
	CollisionSystem::Instance().Terminate();

	// User clean up logic
	StopGame();

	TextureManager::Instance().Terminate();
	Graphics::Instance().Terminate();

	// Destroy the window
	SDL_DestroyWindow(mpWindow);
	mpWindow = nullptr;
}