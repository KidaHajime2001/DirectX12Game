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
	//�T�C�Y���쐬
	for (int i = 0; i < _size; i++)
	{
		Bullet* _bullet = new Bullet(CollisionTag::PlayerBullet,false);
		m_bulletPool.push_back(_bullet);
	}
}

void BulletPool::DestroyPool()
{
	//�v�[���̃N���A
	std::for_each(m_bulletPool.begin(), m_bulletPool.end(), [](Bullet* p) {delete p; });
	m_bulletPool.clear();
}

Bullet* BulletPool::GetUnUsedBullet()
{
	//�g�p���Ă��Ȃ��I�u�W�F�N�g��T���ĕԂ�
	for (auto _bullet : m_bulletPool)
	{
		if (!_bullet->IsAlive())
		{
			return _bullet;
		}
	}
	return nullptr;
}

void BulletPool::Update()
{
	int i = 0;
	for (auto _bullet : m_bulletPool)
	{
		if (_bullet->IsAlive())
		{
			_bullet->Update();
			i++;
		}
	}
	return;
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
