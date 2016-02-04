//====================================================================================================
// Filename:	MissileFactory.h
// Created by:	Johnny Wu
// Description:	Class for a MissileFactory.
//====================================================================================================
#ifndef _MISSILEFACTORY_H_
#define _MISSILEFACTORY_H_

#include <vector>
#include <string>

#include "Missile.h"

//====================================================================================================
// Class Declarations
//====================================================================================================
class MissileFactory
{
public:
	MissileFactory();
	~MissileFactory();

	void Initialize(int amount, std::string name);
	void Clear();

	Missile* GetMissile();
	void ReturnMissile(Missile* Missile);
	const std::vector<Missile*>& GetMissiles()		{ return mMissiles; }

private:
	unsigned int mNumActive;
	std::vector<Missile*> mMissiles;
};

#endif // _MISSILEFACTORY_H_