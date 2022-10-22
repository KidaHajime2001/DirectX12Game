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
{

	m_param.mCollision->m_data.radius = m_radiusData;
	m_nowDirection = DEFAULT_DIRECTION;
	m_param.pos = XMFLOAT3(0, 0, 0);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
	m_isAlive = true;
	m_param.mCollision->m_isValidity = true;
}


void EnemyBase::Update(const DirectX::XMFLOAT3 _targetPos)
{
}

void EnemyBase::Draw()
{
	
	m_direction = atan2(m_nowDirection.x, m_nowDirection.z);
	m_model.Draw(GetPosition(), m_direction, m_modeltype);
}

void EnemyBase::LoadData(const EnemyType _enemyType)
{
}

void EnemyBase::Advent(DirectX::XMFLOAT3 _adventPosition)
{
	auto randPos = XMFLOAT3(rand() % 10 - 10, 0, rand() % 10 - 10);
	m_param.pos = XMF3Math::AddXMFLOAT3(randPos,_adventPosition);
}

void EnemyBase::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
}

void EnemyBase::AttackUpdate(const DirectX::XMFLOAT3 _targetPos)
{
}

void EnemyBase::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
{
}
void EnemyBase::OnCollisionEnter(Collision* otherCollision)
{
	if (otherCollision->GetTag() == CollisionTag::Enemy)
	{
		XMFLOAT3 enemyPos = otherCollision->GetPosition();
		XMFLOAT3 otherToMe = XMF3Math::SubXMFLOAT3(m_param.pos, enemyPos);
		XMFLOAT3 awayVec;

		//半径　+　半径　+　細かい隙間距離
		float awayRange = (m_param.mCollision->GetRadius() + otherCollision->GetRadius() + 0.01f);

		//完全に重なった場合の対策
		if (XMF3Math::LengthXMFLOAT3(otherToMe) == 0)
		{
			float numX = (rand() % 10) - 10;
			float numZ = (rand() % 10) - 10;
			awayVec = XMFLOAT3(numX, 0, numZ);
			awayVec = XMF3Math::SetMagnitude(awayVec, awayRange);
			m_param.pos = XMF3Math::AddXMFLOAT3(enemyPos, awayVec);
			return;
		}

		awayVec = XMF3Math::SetMagnitude(otherToMe, awayRange);
		m_param.pos = XMF3Math::AddXMFLOAT3(enemyPos, awayVec);

	}
	CollisionOriginal(otherCollision);
}

void EnemyBase::CollisionOriginal(Collision* otherCollision)
{
}

