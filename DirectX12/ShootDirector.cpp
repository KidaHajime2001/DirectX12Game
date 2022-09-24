#include "ShootDirector.h"
#include"Player.h"
#include"BulletPool.h"
#include"Bullet.h"
ShootDirector::ShootDirector()
: m_bulletPool(new BulletPool())
{
	
	m_bulletPool->CreatePool(100);
}

ShootDirector::~ShootDirector()
{

	delete m_bulletPool;
}

void ShootDirector::Update( Player* _player)
{

	m_bulletPool->Update();
	if (_player->IsShotFlag())
	{
		auto bullet = m_bulletPool->GetUnUsedBullet();
		if (!bullet)
		{
			return;
		}
		bullet->Shot(_player->GetPosition(),_player->GetShootDirection(),_player->GetShotSpeed());
	}
}

void ShootDirector::Draw()
{
	m_bulletPool->Draw();
}
