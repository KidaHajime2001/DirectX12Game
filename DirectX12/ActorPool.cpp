#include "ActorPool.h"
#include <iostream>
#include <algorithm>
#include"Enemy.h"
#include<random>
#include"CollisionManager.h"
#include"Bullet.h"
Pool::Pool()
{
}

Pool::~Pool()
{
	Destroy();
}

void Pool::Create(int _size, ActorTag _actorTag)
{
	//テンプレートで共通の処理にしたいけど引数付きコンストラクタのテンプレートがわからない
	switch (_actorTag)
	{

	case ActorTag::Enemy:
		
		
		//作成
		for (int i = 0; i < _size; i++)
		{
				
			Actor* enemy = new Enemy(CollisionTag::Enemy, true);
			enemy->Init();
			m_enemypool.pool.push_back(enemy);
		}

		//サイズの記憶
		m_enemypool.poolSize = _size;
			
		//作成済みプールとして記憶
		m_poolVec.push_back(m_enemypool);
		

		break;
	
	}
	
}

void Pool::AddCollisionManager(CollisionManager* _mng)
{
	for (auto pool : m_poolVec)
	{
		
		for (auto actor : pool.pool)
		{
			_mng->AddCollision(actor->GetCollision());
		}
		
		
	}
	
}

void Pool::Destroy()
{
	for (auto pool:m_poolVec)
	{
		std::for_each(pool.pool.begin(), pool.pool.end(), [](Actor* p) {delete p; });
		pool.pool.clear();
	}
	
}

void Pool::Update()
{
	for (auto pool : m_poolVec)
	{
		
		for (auto actor : pool.pool)
		{
			
				actor->Update();
			
		}

	}
}

void Pool::Draw()
{
	for (auto pool : m_poolVec)
	{
	
		for (auto actor : pool.pool)
		{

				actor->Draw();
		}
		

	}
}

Actor* Pool::GetUnUsedActor()
{
	return nullptr;
}

int Pool::NowAliveCount()
{
	return 0;
}

