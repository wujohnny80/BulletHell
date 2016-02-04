//====================================================================================================
// Filename:	Sprite.h
// Created by:	Johnny Wu
// Description:	Class for a 2D Sprite Component.
//====================================================================================================
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <unordered_map>

#include "Component.h"
#include "AnimationState.h"
#include "Texture.h"
#include "../Math/Vector2.h"

//====================================================================================================
// Class Declarations
//====================================================================================================
class Sprite : public Component
{
public:
	Sprite();
	~Sprite();

	// Function to update the sprite
	virtual void Update();

	void SetTexture(std::string fileName);
	void SetTiledTexture(MapData* map);

	// Function to get and set sprite attributes
	float Width()			{ SetOffset(); return (float)mOffset.w; }
	float Height()			{ SetOffset(); return (float)mOffset.h; }
	void SetColor(int r, int g, int b, int a)
	{
		mColor.r = (Uint8)r;
		mColor.g = (Uint8)g;		
		mColor.b = (Uint8)b;		
		mColor.a = (Uint8)a;
	}
	void SetCentered(bool c)	{ mIsCentered = c; }
	void SetAngle(double a)		{ mAngle = a; }
	Vector2 TopLeft();
	Vector2 BottomRight();
	Vector2 Center();

private:
	// Animation Helper Functions
	void Render();
	void LoadAnimation(const char* fileName);
	void SetAnimState(std::string state);
	void SetClip(int frame);
	void SetOffset();

	// Texture and sprite related variables
	Texture* mpTexture;
	SDL_Color mColor;
	SDL_Rect mClip;
	SDL_Rect mOffset;
	float mWidth;
	float mHeight;
	bool mVisible;		// Render is called when true
	bool mFlipH;		// Flip Horizontal
	bool mIsCentered;	// Is image cenetered to the position
	double mAngle;
	
	// Animation related variables
	bool mIsSpriteSheet;
	std::unordered_map<std::string, AnimationState> mAnimations;
	AnimationState mCurrentAnimState;
	int mFrame;
	bool mAnimDone;
	bool mAnimate;

	// Timer
	float mTimer;
};

#endif // #ifndef _SPRITE_H_