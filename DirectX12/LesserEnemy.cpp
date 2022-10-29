#include "LesserEnemy.h"
#include"PmdModel.h"
#include"Collision.h"
#include"Time.h"
#include"XMF3Math.h"
#include"ModelTypeData.h"
LesserEnemy::LesserEnemy(CollisionTag _tag, bool m_alive)
	:EnemyBase(_tag,m_alive)
	,m_timer(new Time())
{
	m_radiusData = 2;
	m_param.mCollision->m_data.radius = m_radiusData;
	m_modeltype = PMDModelType::LesserEnemy;
	m_param.mCollision->m_isValidity = false;
	m_speed = 0.3f;

}
LesserEnemy::~LesserEnemy()
{
	delete m_timer;
}

void LesserEnemy::Init()
{
	m_param.mCollision->m_isValidity = true;
	m_isAlive = true;
	auto randPos=XMFLOAT3(rand()%10-10, 0, rand() % 10 - 10);
	m_param.pos = randPos;
}

void LesserEnemy::Update(const DirectX::XMFLOAT3 _targetPos)
{
	//生きていれば
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
		//雑魚エネミーは突進のみ
		/*if (m_enemyState == EnemyState::attack)
		{
			AttackUpdate(_targetPos);
		}*/
	}



}


void LesserEnemy::CollisionOriginal(Collision* otherCollision)
{
	if (otherCollision->GetTag()==CollisionTag::PlayerBullet)
	{
		m_effect.PlayEffect(EffectType::DefeatBlueEnemy, GetPosition(), false);
		m_param.mCollision->m_isValidity = false;
		m_isAlive = false;
	}
}


void LesserEnemy::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	m_timer->SetTimer(2);
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::move;
	}
}

void LesserEnemy::AttackUpdate(const DirectX::XMFLOAT3 _targetPos)
{

}

void LesserEnemy::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	auto diff = XMF3Math::SubXMFLOAT3(_targetPos,m_param.pos);
	m_nowDirection = diff;
	diff = XMF3Math::SetMagnitude(diff,m_speed);

	m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos,diff);

	m_timer->SetTimer(5);
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::wait;
	}
}
