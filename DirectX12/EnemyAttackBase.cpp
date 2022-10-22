
#include "EnemyAttackBase.h"
#include"EnemyType.h"
#include"Time.h"
#include"Collision.h"
EnemyAttackBase::EnemyAttackBase(const EnemyAttackType _type, const CollisionTag _tag)
	: m_enemyType(_type)
	, Actor(_tag)
	, m_isAlive(false)
{
	Init();
}

EnemyAttackBase::~EnemyAttackBase()
{
}

void EnemyAttackBase::Init()
{
	m_param.mCollision->m_data.pos = m_param.pos;

	m_param.mCollision->m_isValidity = false;
	m_isAlive = false;

}

void EnemyAttackBase::Update(const DirectX::XMFLOAT3 _targetPos)
{

	
}

void EnemyAttackBase::Shot(const DirectX::XMFLOAT3 _position, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec )
{
	
}

void EnemyAttackBase::Draw()
{
}

