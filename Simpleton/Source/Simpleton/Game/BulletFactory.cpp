//====================================================================================================
// Filename:	BulletFactory.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "BulletFactory.h"
#include "../Core//Application.h"

BulletFactory::BulletFactory()
	: mNumActive(0)
{
}

BulletFactory::~BulletFactory()
{
	Clear();
}

void BulletFactory::Initialize(int amount, std::string name)
{
	mBullets.resize(amount);

	for(int i = 0; i < amount; ++i)
	{
		mBullets[i] = new Bullet();
		mBullets[i]->name = name;
		mBullets[i]->Initilaize();
		mBullets[i]->mBulletFactory = this;
		mBullets[i]->mIndex = i;
		mBullets[i]->SetActive(false);
	}
}

void BulletFactory::Clear()
{
	mBullets.clear();
}

Bullet* BulletFactory::GetBullet()
{
	if (mNumActive == mBullets.size())
		return nullptr;

	return mBullets[mNumActive++];
}

void BulletFactory::ReturnBullet(Bullet* bullet)
{
	if (mNumActive == 0)
		return;
	bullet->transform->position = Vector2 (-50.0f, -50.0f);
	bullet->SetActive(false);
	std::swap(mBullets[bullet->mIndex], mBullets[--mNumActive]);
	std::swap(mBullets[bullet->mIndex]->mIndex, mBullets[mNumActive]->mIndex);
}