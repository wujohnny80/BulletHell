//====================================================================================================
// Filename:	GameManager.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "GameManager.h"
#include "Math.h"
#include "../Core/Input.h"
#include "../Core/Timer.h"
#include "../Core/Graphics.h"


//====================================================================================================
// Static
//====================================================================================================
int GameManager::mScore = 0;

//====================================================================================================
// Class Definitions
//====================================================================================================
GameManager::GameManager()
	: mBackground1(nullptr)
	, mBackground2(nullptr)
	, mBulletFactory(nullptr)
	, mEnemySpawner(nullptr)
	, mMissileFactory(nullptr)
	, mPlayer(nullptr)
	, mUIScore(0)
{
}

GameManager::~GameManager()
{
}

void GameManager::InitGame()
{
	// Background
	mBackground1 =  new Background();
	mBackground1->Initialize("map1.txt");
	mBackground2 =  new Background();
	mBackground2->Initialize("map1.txt");
	mBackground2->transform->position.y = (float)-Application::screenHeight;
	mBackground1->SetPartner(mBackground2);
	mBackground2->SetPartner(mBackground1);
	mObjects.push_back(mBackground1);
	mObjects.push_back(mBackground2);

	// Missile Factory
	mMissileFactory = new MissileFactory();
	mMissileFactory->Initialize(1000, "PlayerMissile");
	for (int i = 0; i < 1000; ++i)
	{
		mObjects.push_back(mMissileFactory->GetMissiles()[i]);
	}

	// Player
	mPlayer = new Player();
	mPlayer->Initialize(this);
	mObjects.push_back(mPlayer);

	// Bullet Factory
	mBulletFactory = new BulletFactory();
	mBulletFactory->Initialize(1200, "PlayerBullet");
	for (int i = 0; i < 1200; ++i)
	{
		mObjects.push_back(mBulletFactory->GetBullets()[i]);
	}

	// Enemy Bullet Factory
	mEnemyBulletFactory = new BulletFactory();
	mEnemyBulletFactory->Initialize(1000, "EnemyBullet");
	for (int i = 0; i < 1000; ++i)
	{
		mObjects.push_back(mEnemyBulletFactory->GetBullets()[i]);
	}

	// Enemy Factory
	mEnemySpawner = new EnemySpawner();
	mEnemySpawner->Initialize(this, "level1enemies.txt");
	int size = mEnemySpawner->GetEnemies().size();
	for (int i = 0; i < size; ++i)
	{
		mObjects.push_back(mEnemySpawner->GetEnemies()[i]);
	}

	// UIScore
	mUIScore = new UIScore();
	mUIScore->Initialize();
	mUIScore->Score() = 0;
	mObjects.push_back(mUIScore);
}

void GameManager::RunGame()
{	
	/*std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	std::cout << bulletCount << " " << Timer::FPS;*/

	// CHEAT
	if (Input::KeyDown(Keys::R))
	{
		mPlayer->SetActive(true);
	}

	mUIScore->Score() = mScore;
	mEnemySpawner->Update();

	// Insert into render queue
	unsigned int size = mObjects.size();
  	for(unsigned int i = 0; i < size; ++i)
	{
		// Create object node
		GameObjectNode node = { mObjects[i] };
		mRenderQueue.Insert(node);
	}
	
	// Dequeue and update
	int heapSize = mRenderQueue.Size();
	for(int j = 0; j < heapSize; ++j)
	{
		GameObject* o = mRenderQueue.Remove().obj;
		o->Update();
	}
	mRenderQueue.Clear();
}

void GameManager::StopGame()
{
	// Do Clean-up
	for(unsigned int i = 0; i < mObjects.size(); ++i)
		delete mObjects[i];
	mObjects.clear();

	delete mBulletFactory;
	delete mEnemyBulletFactory;
	delete mEnemySpawner;
	delete mMissileFactory;
}

void GameManager::AddScore(int score)
{
	mScore += score;
}