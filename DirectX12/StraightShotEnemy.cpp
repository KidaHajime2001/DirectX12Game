#include "StraightShotEnemy.h"
#include"PmdModel.h"
#include"Collision.h"
#include"Time.h"
#include"XMF3Math.h"
#include"ModelTypeData.h"
#include"EnemyShotDirector.h"
#include"Sound.h"
#include"SoundType.h"
StraightShotEnemy::StraightShotEnemy(CollisionTag _tag, bool m_alive)
	:EnemyBase(_tag, m_alive)
	, m_timer(new Time())
	,m_shotNum(0)
	,seState(SEState::Attack)
	,m_specialState(SpecialState::CircleMove)
{
	//�����蔻��
	//�O���f�[�^���玝���Ă�����
	m_radiusData = 2;
	m_param.mCollision->m_data.radius = m_radiusData;

	//�I�u�W�F�N�g�v�[���o�^���Ĉ�U�����蔻���OFF
	m_param.mCollision->m_isValidity = false;

	//�V���b�g�N���X�쐬
	m_enemyShotDirector = new EnemyShotDirector();

	//�`�悷��f�[�^
	m_modeltype = PMDModelType::StraightEnemy;

	//�ړ����x
	//�O���f�[�^���玝���Ă�����
	m_speed = 0.1f;

	m_enemyType=EnemyType::StraightShotEnemy;
}

StraightShotEnemy::~StraightShotEnemy()
{
	delete m_enemyShotDirector;
	delete m_timer;
}



void StraightShotEnemy::Update(const DirectX::XMFLOAT3 _targetPos)
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

void StraightShotEnemy::Draw()
{
	//�`��
	//�|�W�V����,�������v�Z,�`��^�C�v
	m_model.Draw(
		GetPosition(),
		atan2(m_nowDirection.x,m_nowDirection.z),
		m_modeltype);
}




void StraightShotEnemy::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//�ҋ@���ԓ�b
	m_timer->SetTimer(2);
	//���Ԃ������玟��ԂɑJ��
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::attack;
		if (rand() % 3==0)
		{
			seState = SEState::SpecialAT;
		}
		else
		{
			seState = SEState::Attack;
		}
		
	}
}

void StraightShotEnemy::AttackUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	switch (seState)
	{
	case SEState::Attack:
		//�v���C���[�Ǝ����Ƃ̋������Z�o
		auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);

		//����
		m_nowDirection = diff;

		//���ˊԊu
		m_timer->SetTimer(0.25f);

		//�V���b�g������
		if (m_timer->CheakTime())
		{
			m_enemyShotDirector->Shot(EnemyAttackType::StraightShot, m_param.pos, _targetPos, diff);
			m_shotNum++;
		}
		//�U���̉񐔂����̐��𒴂�����
		if (ATTACK_NUM_MAX <= m_shotNum)
		{
			//�V���b�g�̃��Z�b�g�Ə�Ԃ̑J��
			m_shotNum = 0;
			m_enemyState = EnemyState::wait;
		}
		break;
	case SEState::SpecialAT:
		if (m_specialState== SpecialState::CircleMove)
		{
			auto aimPos = XMF3Math::AddXMFLOAT3(
				XMF3Math::SetMagnitude( TARGET_SPACE,50.0f), _targetPos);
			//�v���C���[�Ǝ����Ƃ̋������Z�o
			auto diff = XMF3Math::SubXMFLOAT3(aimPos, m_param.pos);
			

			//����
			m_nowDirection = diff;
			diff = XMF3Math::SetMagnitude(diff, m_speed*10);
			//�ړ�
			m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos, diff);
			if (XMF3Math::LengthXMFLOAT3(XMF3Math::SubXMFLOAT3(aimPos, m_param.pos))<5.0f)
			{
				m_specialState = SpecialState::Aiming;
			}
			
		}
		else if (m_specialState == SpecialState::Aiming)
		{
			auto vec = XMF3Math::RotateVec2_XZ(TARGET_SPACE, m_specialrotate++);
 			m_param.pos = XMF3Math::AddXMFLOAT3(GetPosition(),vec);
			//���ˊԊu
			m_timer->SetTimer(0.5f);

			auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);
			//�V���b�g������
			if (m_timer->CheakTime())
			{
				m_enemyShotDirector->Shot(EnemyAttackType::StraightShot, m_param.pos, _targetPos, diff);
				m_shotNum++;
			}
			if (m_shotNum>15)
			{
				m_enemyState = EnemyState::move;
			}
		}
		break;
	default:
		break;
	}
	
	
}

void StraightShotEnemy::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
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
		m_enemyState = EnemyState::move;
	}
}

void StraightShotEnemy::CollisionOriginal(Collision* otherCollision)
{
	if (otherCollision->GetTag() == CollisionTag::PlayerBullet)
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
