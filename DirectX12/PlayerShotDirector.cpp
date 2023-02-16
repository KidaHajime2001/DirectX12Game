#include "PlayerShotDirector.h"
#include"Player.h"
#include"BulletPool.h"
#include"Bullet.h"
#include"XMF3Math.h"
PlayerShotDirector::PlayerShotDirector()
: m_bulletPool(new BulletPool())
{
	//オブジェクト100個作成
	m_bulletPool->CreatePool(300);
}

PlayerShotDirector::~PlayerShotDirector()
{
	delete m_bulletPool;
}


void PlayerShotDirector::Update()
{
	//弾の更新
	m_bulletPool->Update();
}

void PlayerShotDirector::SpreadShot(const bool& _isShot, const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT3& _direction, const float& _speed, const int& _shotLevel)
{
	for (int j = 0; j < _shotLevel+1; j++)
	{
		for (int i = 0; i < 7; i++)
		{

			//未使用の弾を確保
			auto bullet = m_bulletPool->GetUnUsedBullet();
			//プールの上限なら終了
			if (!bullet)
			{
				return;
			}
			//弾発射位置をプレイヤーの先端に調整
			auto vec = XMF3Math::RotateVec2_XZ(_direction, (float)(5 * (3 - (i + 1))));
			auto firePos = XMF3Math::AddXMFLOAT3(_pos, XMF3Math::SetMagnitude(vec, FIRE_POSITION*(j+1)));
			bullet->SpreadShot(firePos, vec, _speed);
		}
	}
	
}

void PlayerShotDirector::NormalShot(const bool& _isShot, const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT3& _direction, const float& _speed, const int& _shotLevel)
{
	for (int i = 0; i < _shotLevel + 1; i++)
	{
		//未使用の弾を確保
		auto bullet = m_bulletPool->GetUnUsedBullet();
		//プールの上限なら終了
		if (!bullet)
		{
			return;
		}
		//弾発射位置をプレイヤーの先端に調整

		auto vec = XMF3Math::RotateVec2_XZ(_direction, (360 / (_shotLevel + 1)) * i);

		auto firePos = XMF3Math::AddXMFLOAT3(_pos, XMF3Math::SetMagnitude(_direction, FIRE_POSITION));


		bullet->Shot(firePos, vec, _speed);
	}
}

void PlayerShotDirector::Draw()
{
	m_bulletPool->Draw();
}
