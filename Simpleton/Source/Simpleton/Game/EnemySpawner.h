//====================================================================================================
// Filename:	EnemySpawner.h
// Created by:	Johnny Wu
// Description:	Class for a game manager.
//====================================================================================================
#ifndef _ENEMYSPAWNER_H_
#define _ENEMYSPAWNER_H_

#include "../Core/Application.h"
#include "../Core/GameObject.h"

#include <string>
#include <unordered_map>
#include <vector>

class GameManager;
//====================================================================================================
// Class Declarations
//====================================================================================================
class EnemySpawner
{
public:
	EnemySpawner();
	~EnemySpawner();

	void Initialize(GameManager* gm, std::string fileName);
	void Update();
	const std::vector<GameObject*>& GetEnemies()		{ return mEnemies; }

private:
	struct EnemySpawnProperty
	{
	public:
		float spawnRate;
		int maxCount;
		int counter;
		float timer;
		int xMin;
		int xMax;
		int yMin;
		int yMax;
		int index;
	};

	std::vector<GameObject*> mEnemies;
	std::unordered_map<std::string, EnemySpawnProperty> mSpawnProperties;
	int totalMaxCount;
	int totalCounter;
	GameManager* mGameManager;
};

#endif // #ifndef _ENEMYSPAWNER_H_