#include "SpreadShotEnemy.h"
#include"PmdModel.h"
#include"Collision.h"
#include"Time.h"
#include"XMF3Math.h"
#include"ModelTypeData.h"
#include"EnemyShotDirector.h"
#include"Sound.h"
#include"SoundType.h"

SpreadShotEnemy::SpreadShotEnemy(CollisionTag _tag, bool m_alive)
	:EnemyBase(_tag, m_alive)
	, m_timer(new Time())
	, m_shotNum(0)
	
{
	//�����蔻��
	//�O���f�[�^���玝���Ă�����
	m_radiusData = 2;
	m_param.mCollision->m_data.radius = m_radiusData;

	//�`�悷��f�[�^
	m_modeltype = PMDModelType::SpreadEnemy;

	//�I�u�W�F�N�g�v�[���o�^���Ĉ�U�����蔻���OFF
	m_param.mCollision->m_isValidity = false;

	//�V���b�g�N���X�쐬
	m_enemyShotDirector = new EnemyShotDirector();

	//�ړ����x
	//�O���f�[�^���玝���Ă�����
	m_speed = 0.1f;

	m_enemyType = EnemyType::SpreadShotEnemy;
}

SpreadShotEnemy::~SpreadShotEnemy()
{
	delete m_timer;
	delete m_enemyShotDirector;
}



void SpreadShotEnemy::Update(const DirectX::XMFLOAT3 _targetPos)
{
	//�����Ă����
	if (m_isAlive)
	{
		if (m_enemyState == EnemyState::wait)
		{
			WaitUpdate(_targetPos);
		}
		if (m_enemyState == EnemyState::move)
		{
			MoveUpdate(_targetPos);
		}
		if (m_enemyState == EnemyState::attack)
		{
			AttackUpdate(_targetPos);
		}
		
	}

}



void SpreadShotEnemy::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//�ҋ@���ԓ�b
	m_timer->SetTimer(2);
	//���Ԃ������玟��ԂɑJ��
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::attack;
	}
}

void SpreadShotEnemy::AttackUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//�v���C���[�Ǝ����Ƃ̋������Z�o
	auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);
	//����
	m_nowDirection = diff;
	//���ˊԊu
	m_timer->SetTimer(1);

	//�V���b�g�����v
	if (m_timer->CheakTime())
	{
		m_enemyShotDirector->Shot(EnemyAttackType::SpreadShot, m_param.pos, _targetPos, diff);
		m_shotNum++;
	}

	//�U���̉񐔂����̐��𒴂�����
	if (ATTACK_NUM_MAX <= m_shotNum)
	{
		//�V���b�g�̃��Z�b�g�Ə�Ԃ̑J��
		m_shotNum = 0;
		m_enemyState = EnemyState::move;
	}
}

void SpreadShotEnemy::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//�v���C���[�Ǝ����Ƃ̋������Z�o
	auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);
	//����
	m_nowDirection = diff;
	diff = XMF3Math::SetMagnitude(diff, m_speed);
	//�ړ�
	m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos, diff);

	m_timer->SetTimer(5);
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::wait;
	}
}

void SpreadShotEnemy::CollisionOriginal(Collision* otherCollision)
{
	if (otherCollision->GetTag() == CollisionTag::PlayerBullet
		)
	{
		//���S���o
		m_effect.PlayEffect(EffectType::DefeatHigherEnemy, GetPosition(), false);
		m_sound.Play(SoundType::DefeatEnemySE, false, true);

		//�����蔻��OFF
		m_param.mCollision->m_isValidity = false;
		//�����t���OOFF
		m_isAlive = false;
	}
}
