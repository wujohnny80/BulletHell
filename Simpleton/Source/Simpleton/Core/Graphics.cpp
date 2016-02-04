//====================================================================================================
// Filename:	Graphics.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Graphics.h"
#include <stdio.h>
#include <SDL_ttf.h>

//====================================================================================================
// Statics
//====================================================================================================
SDL_Renderer* Graphics::Renderer = nullptr;

//====================================================================================================
// Class Definitions
//====================================================================================================

Graphics::Graphics()
{
}

//----------------------------------------------------------------------------------------------------

Graphics::~Graphics()
{
}

//----------------------------------------------------------------------------------------------------

void Graphics::Initialize(SDL_Window* window)
{
	// Cache the window
	mpWindow = window;

	// Do Initialization
	Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if( Renderer == nullptr )
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Initialize renderer color
		SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		// Initialize PNG and JPG support
		if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
		{
			printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		}

		// Initialize TTF
		if (TTF_Init() < 0)
		{
			printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		}
	}
}

//----------------------------------------------------------------------------------------------------

void Graphics::Terminate()
{
	//Destroy window
	SDL_DestroyRenderer(Renderer);
	Renderer = nullptr;
	TTF_Quit();
}

//----------------------------------------------------------------------------------------------------

void Graphics::BeginRender()
{
	// Clear screen to black
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);
}

void Graphics::EndRender()
{
	//Update screen
	SDL_RenderPresent(Renderer);
}