//====================================================================================================
// Filename:	UIScore.h
// Created by:	Johnny Wu
// Description:	Class for a UIScore.
//====================================================================================================
#ifndef _UISCORE_H
#define _UISCORE_H

#include "../Core/GameObject.h"
#include "../Core/Text.h"

//====================================================================================================
// Class Declarations
//====================================================================================================
class UIScore : public GameObject
{
public:
	UIScore();
	virtual ~UIScore();

	void Initialize();
	virtual void Update() override;
	virtual void HandleCollision(GameObject* other) override;
	virtual void Deactivate() override;

	int& Score()	{ return mScore; }

private:
	void SetText();

	// Component
	Text* mpText;
	int mScore;
};

#endif // #ifndef _UISCORE_H