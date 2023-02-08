#include "Bullet.h"
#include"Singleton.h"
#include"PmdModel.h"
#include"Collision.h"
#include"XMF3Math.h"
#include "ModelTypeData.h"
Bullet::Bullet(CollisionTag _tag, const bool _alive)
	:m_model(Singleton<PMDModel>::GetInstance())
	,Actor(_tag)
	,m_isAlive(_alive)
{
	m_param.mCollision->m_data.radius = RADIUS_NUM;
	m_param.mCollision->m_isValidity = false;
	m_speed = 0.0f;//‰¼’u‚«
	Init();
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	m_isAlive = false;
	m_aliveTime = 1.0f;
	m_param.mCollision->m_isValidity = false;
}

void Bullet::Update()
{

	SetPotision(XMF3Math::AddXMFLOAT3(GetPosition(), XMF3Math::ScalarXMFLOAT3(m_directionVector, m_speed)));
	auto nowTime = clock();
	float time = (float)(nowTime - m_aliveTimeStart) / (float)CLOCKS_PER_SEC;
	if (time>=m_aliveTime)
	{
		Init();
	}

}

void Bullet::Draw()
{
	auto dir = atan2(m_directionVector.x, m_directionVector.z);
	m_model.Draw(GetPosition(),dir,PMDModelType::PlayerBullet);
}

void Bullet::OnCollisionEnter(Collision* otherCollision)
{
	Init();
}

void Bullet::Shot(const XMFLOAT3& _setPosition, const XMFLOAT3& _newDirection, const float& _shotspeed)
{
	SetPotision(_setPosition);
	SetDirection(_newDirection);
	m_speed=_shotspeed;
	m_isAlive = true;
	m_aliveTimeStart = clock();
	m_param.mCollision->m_isValidity = true;
	m_aliveTime = 0.7f;
}
void Bullet::SpreadShot(const XMFLOAT3& _setPosition, const XMFLOAT3& _newDirection, const float& _shotspeed)
{
	SetPotision(_setPosition);
	SetDirection(_newDirection);
	m_speed = _shotspeed;
	m_isAlive = true;
	m_aliveTimeStart = clock();
	m_param.mCollision->m_isValidity = true;
	m_aliveTime = 0.15f;
}