//====================================================================================================
// Filename:	Graphics.h
// Created by:	Johnny Wu
// Description:	Singleton Class for the graphics system.
//====================================================================================================
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL.h>
#include <SDL_image.h>

//====================================================================================================
// Class Declarations
//====================================================================================================

class Graphics
{
	friend class Application;
public:
	static Graphics& Instance()	{ static Graphics instance; return instance; }
	~Graphics();

	// Statics
	static SDL_Renderer* Renderer;

private:
	Graphics();
	Graphics(Graphics const&);	// Don't implement
	void operator=(Graphics const&);	// Don't implement

	// Functions to startup and shutdown the graphics system
	void Initialize(SDL_Window* window);
	void Terminate();

	// Functions to be called before and after any rendering
	void BeginRender();
	void EndRender();

	SDL_Window* mpWindow;
};

#endif // #ifndef _GRAPHICS_H_