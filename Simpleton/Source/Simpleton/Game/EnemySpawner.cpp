//====================================================================================================
// Filename:	EnemySpawner.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Boss.h"
#include "EnemySpawner.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "GameManager.h"
#include "Math.h"
#include "../Core/Timer.h"

#include <fstream>
#include <iostream>

//====================================================================================================
// Class Definitions
//====================================================================================================

EnemySpawner::EnemySpawner()
	: totalMaxCount(0)
	, totalCounter(0)
	, mGameManager(nullptr)
{
}

EnemySpawner::~EnemySpawner()
{
	mEnemies.clear();
}

void EnemySpawner::Initialize(GameManager* gm, std::string fileName)
{
	mGameManager = gm;

	// Construct full path name
	std::string fullPath = "../../Assets/Levels/";
	fullPath += fileName;

	// Open File
	std::ifstream file;
	file.open(fullPath);
	if (file.fail())
	{
		std::cout << "Failed to open file " << fullPath << std::endl;
		exit(404);
		return;
	}

	// Read/Write
	std::string type;
	float rate = 0.0f;
	int xMin = 0;
	int xMax = 0;
	int yMin = 0;
	int yMax = 0;
	unsigned int qty = 0;

	while (!file.eof())
	{
		if(file.peek() == '#' || file.peek() == 10) // 10 is the return character
		{
			getline(file, type);
			continue;
		}

		file >> type >> rate >> xMin >> xMax >> yMin >> yMax >> qty;

		// Set spawn properties
		EnemySpawnProperty esp;
		esp.counter = 0;
		esp.maxCount = qty;
		esp.spawnRate = rate;
		esp.timer = 0.0f;
		esp.xMin = xMin;
		esp.xMax = xMax;
		esp.yMin = yMin;
		esp.yMax = yMax;
		esp.index = totalMaxCount;

		mSpawnProperties[type] = esp;
		totalMaxCount += qty;

		for (unsigned int i = 0; i < qty; ++i)
		{
			// Spawn
			if (type == "Enemy")
			{
				Enemy* obj = new Enemy();
				obj->Initialize(mGameManager);
				int x = Math::RandomRange(xMin, xMax);
				int y = Math::RandomRange(yMin, yMax);
				obj->transform->position = Vector2(x, y);
				obj->SetActive(false);
				mEnemies.push_back(obj);
			}
			else if (type == "Enemy2")
			{
				Enemy2* obj = new Enemy2();
				obj->Initialize(mGameManager);
				obj->SetActive(false);
				mEnemies.push_back(obj);
			}
			else if (type == "Boss")
			{
				Boss* obj = new Boss();
				obj->Initialize(mGameManager);
				int x = Math::RandomRange(xMin, xMax);
				int y = Math::RandomRange(yMin, yMax);
				obj->transform->position = Vector2(x, y);
				obj->SetActive(false);
				mEnemies.push_back(obj);
			}
		}
	}
	
	// Close File
	file.close();
}

void EnemySpawner::Update()
{
	if (totalCounter >= totalMaxCount)
		return;

	// Check each unit types
	auto it = mSpawnProperties.begin();
	for (; it != mSpawnProperties.end(); ++it)
	{
		EnemySpawnProperty esp = it->second;
		// If everything of this type was spawned, skip
		if (esp.counter >= esp.maxCount)
			continue;

		// Check timer to spawn
		it->second.timer += Timer::deltaTime;
		if (esp.timer > esp.spawnRate)
		{
			if (esp.counter < esp.maxCount)
			{
				mEnemies[esp.index + esp.counter]->SetActive(true);

				// make sure to modify the original, not the copy
				++it->second.counter;
				it->second.timer = 0.0f;
				++totalCounter;
			}
		}
	}
}