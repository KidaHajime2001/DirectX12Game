#include "PlayerShotDirector.h"
#include"Player.h"
#include"BulletPool.h"
#include"Bullet.h"
#include"XMF3Math.h"
PlayerShotDirector::PlayerShotDirector()
: m_bulletPool(new BulletPool())
{
	//オブジェクト100個作成
	m_bulletPool->CreatePool(100);
}

PlayerShotDirector::~PlayerShotDirector()
{
	delete m_bulletPool;
}


void PlayerShotDirector::Update(const bool& _isShot, const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT3& _direction, const float& _speed)
{
	//弾の更新
	m_bulletPool->Update();

	//弾の発射
	if (_isShot)
	{
		//未使用の弾を確保
		auto bullet = m_bulletPool->GetUnUsedBullet();
		//プールの上限なら終了
		if (!bullet)
		{
			return;
		}
		//弾発射位置をプレイヤーの先端に調整
		auto firePos = XMF3Math::AddXMFLOAT3(_pos,XMF3Math::SetMagnitude(_direction,FIRE_POSITION));
		bullet->Shot(firePos,_direction,_speed);
	}
}

void PlayerShotDirector::Draw()
{
	m_bulletPool->Draw();
}
