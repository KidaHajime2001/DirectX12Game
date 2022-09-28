#include "BulletPool.h"
#include"Bullet.h"
#include <algorithm>
#include"CollisionManager.h"
BulletPool::BulletPool()
{
}

BulletPool::~BulletPool()
{
	DestroyPool();
}

void BulletPool::CreatePool(int _size)
{
	for (int i = 0; i < _size; i++)
	{
		Bullet* _bullet = new Bullet(CollisionTag::PlayerBullet,false);
		m_bulletPool.push_back(_bullet);
	}
}

void BulletPool::DestroyPool()
{
	std::for_each(m_bulletPool.begin(), m_bulletPool.end(), [](Bullet* p) {delete p; });
	m_bulletPool.clear();
}

Bullet* BulletPool::GetUnUsedBullet()
{
	for (auto _bullet : m_bulletPool)
	{
		if (!_bullet->IsAlive())
		{
			return _bullet;
		}

	}

	return nullptr;
}
void BulletPool::AddCollisionManager(CollisionManager* _mng)
{
	for (auto _bullet : m_bulletPool)
	{

		
			_mng->AddCollision(_bullet->GetCollision());
		


	}
}


void BulletPool::Update()
{
	for (auto _bullet : m_bulletPool)
	{
		if (_bullet->IsAlive())
		{
			_bullet->Update();
		}

	}
}

void BulletPool::Draw()
{
	for (auto _bullet : m_bulletPool)
	{
		if (_bullet->IsAlive())
		{
			_bullet->Draw();
		}

	}
}
