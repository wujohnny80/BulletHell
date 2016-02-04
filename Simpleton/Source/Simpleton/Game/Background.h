//====================================================================================================
// Filename:	Background.h
// Created by:	Johnny Wu
// Description:	Class for a Background.
//====================================================================================================
#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include "../Core/GameObject.h"
#include "../Core/MapData.h"
#include "../Core/Sprite.h"

//====================================================================================================
// Class Declarations
//====================================================================================================
class Background : public GameObject
{
public:
	Background();
	virtual ~Background();

	void Initialize(const char* mapFile);
	virtual void Update() override;
	virtual void HandleCollision(GameObject* other) override;
	virtual void Deactivate() override;
	void SetPartner(Background* p)		{ myPartner = p; }

private:
	void ResetToTop();

	Sprite* mSprite;
	MapData* mMap;

	Background* myPartner;
	float mSpeed;
};

#endif // #ifndef _BACKGROUND_H