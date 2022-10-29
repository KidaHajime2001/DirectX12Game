#include "SpreadShotEnemy.h"
#include"PmdModel.h"
#include"Collision.h"
#include"Time.h"
#include"XMF3Math.h"
#include"ModelTypeData.h"
#include"EnemyShotDirector.h"
SpreadShotEnemy::SpreadShotEnemy(CollisionTag _tag, bool m_alive)
	:EnemyBase(_tag, m_alive)
	, m_timer(new Time())
	, m_shotNum(0)
	
{
	m_radiusData = 2;
	m_param.mCollision->m_data.radius = m_radiusData;
	m_modeltype = PMDModelType::SpreadEnemy;
	m_param.mCollision->m_isValidity = false;
	m_enemyShotDirector = new EnemyShotDirector();
	m_speed = 0.1f;
}

SpreadShotEnemy::~SpreadShotEnemy()
{
	delete m_timer;
	delete m_enemyShotDirector;
}



void SpreadShotEnemy::Update(const DirectX::XMFLOAT3 _targetPos)
{
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



void SpreadShotEnemy::OnCollisionEnter(Collision* otherCollision)
{
	if (otherCollision->GetTag() == CollisionTag::PlayerBullet)
	{
		m_effect.PlayEffect(EffectType::DefeatRedEnemy, GetPosition(), false);
		m_param.mCollision->m_isValidity = false;
		m_isAlive = false;
	}/*
	OutputDebugString("SpreadShotEnemy‚Å‚·");*/
}

void SpreadShotEnemy::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	m_timer->SetTimer(2);
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::attack;
	}
}

void SpreadShotEnemy::AttackUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);
	m_nowDirection = diff;
	m_timer->SetTimer(1);

	if (m_timer->CheakTime())
	{
		m_enemyShotDirector->Shot(EnemyAttackType::SpreadShot, m_param.pos, _targetPos, diff);
		m_shotNum++;
	}

	if (ATTACK_NUM_MAX <= m_shotNum)
	{
		m_shotNum = 0;
		m_enemyState = EnemyState::move;
	}
}

void SpreadShotEnemy::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);

	diff = XMF3Math::SetMagnitude(diff, m_speed);

	m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos, diff);
	m_nowDirection = diff;
	m_timer->SetTimer(5);
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::wait;
	}
}
