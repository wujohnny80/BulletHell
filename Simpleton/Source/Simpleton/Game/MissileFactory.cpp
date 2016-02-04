//====================================================================================================
// Filename:	MissileFactory.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "MissileFactory.h"
#include "../Core//Application.h"

MissileFactory::MissileFactory()
	: mNumActive(0)
{
}

MissileFactory::~MissileFactory()
{
	Clear();
}

void MissileFactory::Initialize(int amount, std::string name)
{
	mMissiles.resize(amount);

	for(int i = 0; i < amount; ++i)
	{
		mMissiles[i] = new Missile();
		mMissiles[i]->name = name;
		mMissiles[i]->Initilaize();
		mMissiles[i]->mMissileFactory = this;
		mMissiles[i]->mIndex = i;
		mMissiles[i]->SetActive(false);
	}
}

void MissileFactory::Clear()
{
	mMissiles.clear();
}

Missile* MissileFactory::GetMissile()
{
	if (mNumActive == mMissiles.size())
		return nullptr;

	return mMissiles[mNumActive++];
}

void MissileFactory::ReturnMissile(Missile* Missile)
{
	if (mNumActive == 0)
		return;
	Missile->SetActive(false);
	Missile->transform->position = Vector2 (-50.0f, -50.0f);
	std::swap(mMissiles[Missile->mIndex], mMissiles[--mNumActive]);
	std::swap(mMissiles[Missile->mIndex]->mIndex, mMissiles[mNumActive]->mIndex);
}