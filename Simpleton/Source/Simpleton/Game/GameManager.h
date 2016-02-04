//====================================================================================================
// Filename:	GameManager.h
// Created by:	Johnny Wu
// Description:	Class for a game manager.
//====================================================================================================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <fstream>
#include <iostream>
#include <vector>

#include "Background.h"
#include "BulletFactory.h"
#include "EnemySpawner.h"
#include "MissileFactory.h"
#include "Player.h"
#include "UIScore.h"

#include "../Core/Application.h"
#include "../Utilities/Heap.h"

//====================================================================================================
// Struct
//====================================================================================================
struct GameObjectNode
{
	GameObject* obj;
	bool operator<(const GameObjectNode& other)
	{
		return obj->layer < other.obj->layer;
	}
};

//====================================================================================================
// Class Declarations
//====================================================================================================

class GameManager : public Application
{
public:
	GameManager();
	~GameManager();

	BulletFactory* GetBulletFactory()		{ return mBulletFactory; }
	BulletFactory* GetEnemyBulletFactory()	{ return mEnemyBulletFactory; }
	MissileFactory* GetMissileFactory()		{ return mMissileFactory; }
	Player* GetPlayer()						{ return mPlayer; }
	static void AddScore(const int score);

protected:
	// Game related user defined logics
	virtual void InitGame();
	virtual void RunGame();
	virtual void StopGame();

private:
	Heap<GameObjectNode> mRenderQueue;
	std::vector<GameObject*> mObjects;

	Background* mBackground1;
	Background* mBackground2;

	BulletFactory* mBulletFactory;
	BulletFactory* mEnemyBulletFactory;
	EnemySpawner* mEnemySpawner;
	MissileFactory* mMissileFactory;
	Player* mPlayer;
	UIScore* mUIScore;

	static int mScore;
};

#endif // #ifndef _GAMEMANAGER_H_