#include "PlayerShotDirector.h"
#include"Player.h"
#include"BulletPool.h"
#include"Bullet.h"
PlayerShotDirector::PlayerShotDirector()
: m_bulletPool(new BulletPool())
{
	
	m_bulletPool->CreatePool(100);
}

PlayerShotDirector::~PlayerShotDirector()
{

	delete m_bulletPool;
}

void PlayerShotDirector::Update(const bool _isShot, const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _direction, const float _speed)
{

	m_bulletPool->Update();
	if (_isShot)
	{
		auto bullet = m_bulletPool->GetUnUsedBullet();
		if (!bullet)
		{
			return;
		}
		bullet->Shot(_pos,_direction,_speed);
	}
}

void PlayerShotDirector::Draw()
{
	m_bulletPool->Draw();
}
