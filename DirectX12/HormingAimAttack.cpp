#include "HormingAimAttack.h"
#include"Time.h"
#include"PmdModel.h"
#include"ModelTypeData.h"
#include "XMF3Math.h"
HormingAimAttack::HormingAimAttack(const EnemyAttackType _type, const CollisionTag _tag)
	:EnemyAttackBase(_type,_tag)
	,m_timer(new Time())
	,m_model(Singleton<PMDModel>::GetInstance())
{
}

HormingAimAttack::~HormingAimAttack()
{
	delete m_timer;
}

void HormingAimAttack::Update(DirectX::XMFLOAT3 _targetPos)
{
	if (m_isAlive)
	{
		//ターゲットまでの位置
		XMFLOAT3 acc = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);

		//速度の制限
		float speed = 3.0f;
		acc = XMF3Math::SetMagnitude(acc,speed);

		acc = XMF3Math::SubXMFLOAT3(acc, m_velocity);

		if (XMF3Math::LengthXMFLOAT3(acc) > 0.01f)
		{
			acc = XMF3Math::SetMagnitude(acc, 0.01f);
		};


		m_acceleration = XMF3Math::AddXMFLOAT3(m_acceleration, acc);
		Move();
	}
	if (m_timer->CheakTime())
	{
		m_isAlive = false;
	}
}

void HormingAimAttack::Shot(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec)
{
	m_param.pos = _pos;
	m_timer->SetTimer(3);
	m_isAlive = true;
	
	auto diff = XMF3Math::SubXMFLOAT3(_targetPos,_pos);
	diff= XMF3Math::SetMagnitude(diff,-1.0f);
	m_velocity = XMF3Math::AddXMFLOAT3(m_velocity,diff);
}

void HormingAimAttack::Draw()
{
	if (m_isAlive)
	{
		m_model.Draw(m_param.pos, PMDModelType::AimingBullet);
	}
}

void HormingAimAttack::Move()
{
	m_velocity = XMF3Math::AddXMFLOAT3(m_velocity, m_acceleration);
	m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos, m_velocity);
	m_acceleration = XMF3Math::ScalarXMFLOAT3(m_acceleration, 0);
}
