#include "ShootDirector.h"
#include"Player.h"
#include"BulletPool.h"
#include"Bullet.h"
ShootDirector::ShootDirector()
{
}

ShootDirector::~ShootDirector()
{
}

void ShootDirector::Update( Player* _player, BulletPool* _bulletPool)
{
	if (_player->IsShotFlag())
	{
		auto bullet = _bulletPool->GetUnUsedBullet();
		if (!bullet)
		{
			return;
		}
		bullet->Shot(_player->GetPosition(),_player->GetShootDirection(),_player->GetShotSpeed());
	}
}
