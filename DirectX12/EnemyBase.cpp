#include "EnemyBase.h"
#include "PMDModel.h"
#include"Sound.h"
#include"EffekseerMng.h"
#include"XMF3Math.h"
#include"Collision.h"
#include"EnemyType.h"
#include"EnemyShotDirector.h"

EnemyBase::EnemyBase(CollisionTag _tag, bool _alive)
	:Actor(_tag)
	,m_isAlive(_alive)
	, m_model(Singleton<PMDModel>::GetInstance())
	, m_effect(Singleton<EffekseerManager>::GetInstance())
	, m_sound(Singleton<Sound>::GetInstance())
	,m_isHit(false)
{
	//���a�f�[�^
	m_param.mCollision->m_data.radius = m_radiusData;
	//�Ńt�H���g�����ݒ�
	m_nowDirection = DEFAULT_DIRECTION;
	m_param.pos = XMFLOAT3(0, 0, 0);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
	//�I�u�W�F�N�g�v�[���݌v�̈׎g���܂킹��悤�A��{�I�Ȑݒ������������
	//�����t���O��ON
	//�����蔻���ON
	//�v���C���[�ɓ������Ă��邩�̃t���O��OFF
	m_isAlive = true;
	m_param.mCollision->m_isValidity = true;
	m_isHit = false;
}


void EnemyBase::Update(const DirectX::XMFLOAT3 _targetPos)
{
}

void EnemyBase::Draw()
{
	//�`��
	//�|�W�V����,�������v�Z,�`��^�C�v
	m_model.Draw(
		GetPosition(), 
		atan2(m_nowDirection.x, m_nowDirection.z), 
		m_modeltype);
}

void EnemyBase::LoadData(const EnemyType _enemyType)
{
}

void EnemyBase::Advent(DirectX::XMFLOAT3 _adventPosition)
{
	//�|�W�V������Enemy�}�l�[�W���[����󂯎��
	//�኱�o�����U�炷����
	auto randPos = XMFLOAT3(rand() % 10 - 10, 0, rand() % 10 - 10);
	m_param.pos = XMF3Math::AddXMFLOAT3(randPos,_adventPosition);
}

void EnemyBase::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//EnemyBase���p���������N���X�ɋL�q
}

void EnemyBase::AttackUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//EnemyBase���p���������N���X�ɋL�q
}

void EnemyBase::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//EnemyBase���p���������N���X�ɋL�q
}
void EnemyBase::OnCollisionEnter(Collision* otherCollision)
{
	//�������蔻��̃^�O��Enemy�������ꍇ
	if (otherCollision->GetTag() == CollisionTag::Enemy)
	{
		//���G�l�~�[�̈ʒu���擾
		XMFLOAT3 enemyPos = otherCollision->GetPosition();
		//���G�l�~�[�Ƃ̋����Z�o
		XMFLOAT3 otherToMe = XMF3Math::SubXMFLOAT3(m_param.pos, enemyPos);
		//����鋗��
		XMFLOAT3 awayVec;
		//���a�@+�@���a�@+�@�ׂ������ԋ���
		float awayRange = (m_param.mCollision->GetRadius() + otherCollision->GetRadius() + 0.01f);

		//���S�ɏd�Ȃ����ꍇ�̑΍�
		if (XMF3Math::LengthXMFLOAT3(otherToMe) == 0)
		{
			//�����_���ɎU�炷
			float numX = (rand() % 10) - 10;
			float numZ = (rand() % 10) - 10;
			awayVec = XMFLOAT3(numX, 0, numZ);
			awayVec = XMF3Math::SetMagnitude(awayVec, awayRange);
		}
		awayVec = XMF3Math::SetMagnitude(otherToMe, awayRange);
		//����
		m_param.pos = XMF3Math::AddXMFLOAT3(enemyPos, awayVec);

	}
	if (otherCollision->GetTag() == CollisionTag::PlayerBullet)
	{
		//�v���C���[�̒e�ɐڐG
		m_isHit = true;
	}
	//�h���N���X�ʂ̐ڐG����
	CollisionOriginal(otherCollision);
}

void EnemyBase::CollisionOriginal(Collision* otherCollision)
{
	//EnemyBase���p���������N���X�ɋL�q
}

