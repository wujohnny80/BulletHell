//====================================================================================================
// Filename:	Text.h
// Created by:	Johnny Wu
// Description:	Class for a 2D Text Component.
//====================================================================================================
#ifndef _TEXT_H_
#define _TEXT_H_

#include "Component.h"
#include "Texture.h"
#include "../Math/Vector2.h"
#include <SDL_ttf.h>
#include <string>

//====================================================================================================
// Class Declarations
//====================================================================================================
class Text : public Component
{
	friend class Texture;
public:
	Text();
	~Text();

	// Function to update the Text
	void Initialize(std::string fontFile);
	virtual void Update();

	void SetText(const std::string message)		{ mMsg = message; }
	void SetSize(const int size)				{ mFontSize = size; }
	void Bold(const bool b)						{ mBold = b; }
	void Italicize(const bool b)				{ mItalic = b; }
	void Underline(const bool b)				{ mUnderline = b; }
	void StrikeThru(const bool b)				{ mStrikeThru = b; }
	void Outline(const bool b)					{ mOutline = b; }
	void SetOutlineSize(const int size)			{ mOutlineSize = size; }

	// Function to get and set Text attributes
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
	void Render();
	void SetTexture();
	void SetFont();
	void SetOffset();

	// Texture related variables
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

	// Text properties	
	TTF_Font* mpFont;
	std::string mFontFile;
	std::string mMsg;
	int mFontSize;
	bool mBold;
	bool mItalic;
	bool mUnderline;
	bool mStrikeThru;
	bool mOutline;
	int mOutlineSize;
};

#endif // #ifndef _TEXT_H_