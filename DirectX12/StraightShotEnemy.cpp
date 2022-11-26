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
{
	m_radiusData = 2;
	m_param.mCollision->m_data.radius = m_radiusData;
	m_param.mCollision->m_isValidity = false;
	m_enemyShotDirector = new EnemyShotDirector();
	m_modeltype = PMDModelType::StraightEnemy;
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
	/*m_enemyShotDirector->Update(_targetPos);*/
	//¶‚«‚Ä‚¢‚ê‚Î
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


void StraightShotEnemy::CollisionOriginal(Collision* otherCollision)
{
	if (otherCollision->GetTag() == CollisionTag::PlayerBullet)
	{
		m_effect.PlayEffect(EffectType::DefeatRedEnemy, GetPosition(), false);
		m_param.mCollision->m_isValidity = false;
		m_sound.Play(SoundType::DefeatEnemySE, false, true);
		m_isAlive = false;
	}
}



void StraightShotEnemy::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	m_timer->SetTimer(2);
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::attack;
	}
}

void StraightShotEnemy::AttackUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);
	m_nowDirection = diff;
	m_timer->SetTimer(0.25f);

	if (m_timer->CheakTime())
	{
		m_enemyShotDirector->Shot(EnemyAttackType::StraightShot, m_param.pos, _targetPos, diff);
		m_shotNum++;
	}

	if (ATTACK_NUM_MAX<=m_shotNum)
	{
		m_shotNum = 0;
		m_enemyState = EnemyState::wait;
	}
}

void StraightShotEnemy::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);

	diff = XMF3Math::SetMagnitude(diff, m_speed);

	m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos, diff);
	m_nowDirection = diff;
	m_timer->SetTimer(5);
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::move;
	}
}
