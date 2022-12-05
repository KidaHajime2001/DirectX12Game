#include "PlayerShotDirector.h"
#include"Player.h"
#include"BulletPool.h"
#include"Bullet.h"
#include"XMF3Math.h"
PlayerShotDirector::PlayerShotDirector()
: m_bulletPool(new BulletPool())
{
	//�I�u�W�F�N�g100�쐬
	m_bulletPool->CreatePool(100);
}

PlayerShotDirector::~PlayerShotDirector()
{
	delete m_bulletPool;
}


void PlayerShotDirector::Update(const bool& _isShot, const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT3& _direction, const float& _speed)
{
	//�e�̍X�V
	m_bulletPool->Update();

	//�e�̔���
	if (_isShot)
	{
		//���g�p�̒e���m��
		auto bullet = m_bulletPool->GetUnUsedBullet();
		//�v�[���̏���Ȃ�I��
		if (!bullet)
		{
			return;
		}
		//�e���ˈʒu���v���C���[�̐�[�ɒ���
		auto firePos = XMF3Math::AddXMFLOAT3(_pos,XMF3Math::SetMagnitude(_direction,FIRE_POSITION));
		bullet->Shot(firePos,_direction,_speed);
	}
}

void PlayerShotDirector::Draw()
{
	m_bulletPool->Draw();
}
