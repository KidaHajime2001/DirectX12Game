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
	//�e���v���[�g�ŋ��ʂ̏����ɂ��������ǈ����t���R���X�g���N�^�̃e���v���[�g���킩��Ȃ�
	switch (_actorTag)
	{

	case ActorTag::Enemy:
		
		
		//�쐬
		for (int i = 0; i < _size; i++)
		{
				
			Actor* enemy = new Enemy(CollisionTag::Enemy, true);
			enemy->Init();
			m_enemypool.pool.push_back(enemy);
		}

		//�T�C�Y�̋L��
		m_enemypool.poolSize = _size;
			
		//�쐬�ς݃v�[���Ƃ��ċL��
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

