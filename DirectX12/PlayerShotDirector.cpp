#include "PlayerShotDirector.h"
#include"Player.h"
#include"BulletPool.h"
#include"Bullet.h"
#include"XMF3Math.h"
PlayerShotDirector::PlayerShotDirector()
: m_bulletPool(new BulletPool())
{
	//�I�u�W�F�N�g100�쐬
	m_bulletPool->CreatePool(300);
}

PlayerShotDirector::~PlayerShotDirector()
{
	delete m_bulletPool;
}


void PlayerShotDirector::Update()
{
	//�e�̍X�V
	m_bulletPool->Update();
}

void PlayerShotDirector::SpreadShot(const bool& _isShot, const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT3& _direction, const float& _speed, const int& _shotLevel)
{
	for (int j = 0; j < _shotLevel+1; j++)
	{
		for (int i = 0; i < 7; i++)
		{

			//���g�p�̒e���m��
			auto bullet = m_bulletPool->GetUnUsedBullet();
			//�v�[���̏���Ȃ�I��
			if (!bullet)
			{
				return;
			}
			//�e���ˈʒu���v���C���[�̐�[�ɒ���
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
		//���g�p�̒e���m��
		auto bullet = m_bulletPool->GetUnUsedBullet();
		//�v�[���̏���Ȃ�I��
		if (!bullet)
		{
			return;
		}
		//�e���ˈʒu���v���C���[�̐�[�ɒ���

		auto vec = XMF3Math::RotateVec2_XZ(_direction, (360 / (_shotLevel + 1)) * i);

		auto firePos = XMF3Math::AddXMFLOAT3(_pos, XMF3Math::SetMagnitude(_direction, FIRE_POSITION));


		bullet->Shot(firePos, vec, _speed);
	}
}

void PlayerShotDirector::Draw()
{
	m_bulletPool->Draw();
}
