//====================================================================================================
// Filename:	BulletFactory.h
// Created by:	Johnny Wu
// Description:	Class for a BulletFactory.
//====================================================================================================
#ifndef _BULLETFACTORY_H_
#define _BULLETFACTORY_H_

#include <vector>
#include <string>

#include "Bullet.h"

//====================================================================================================
// Class Declarations
//====================================================================================================
class BulletFactory
{
public:
	BulletFactory();
	~BulletFactory();

	void Initialize(int amount, std::string name);
	void Clear();

	Bullet* GetBullet();
	void ReturnBullet(Bullet* bullet);
	const std::vector<Bullet*>& GetBullets()		{ return mBullets; }

private:
	unsigned int mNumActive;
	std::vector<Bullet*> mBullets;
};

#endif // _BULLETFACTORY_H_