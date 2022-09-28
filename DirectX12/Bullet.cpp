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
	m_param.mCollision = new Collision(this, RADIUS_NUM);
	m_speed = 0.0f;//‰¼’u‚«
	Init();
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	
}

void Bullet::Update()
{
	/*m_effect.PlayEffect(EffectType::BlackObstacle, GetPosition(), false);*/
	m_param.mCollision->Update();
	auto NextPosition = XMF3Math::AddXMFLOAT3( GetPosition() , XMF3Math::ScalarXMFLOAT3(m_directionVector,m_speed));
	SetPotision(NextPosition);
	auto nowTime = clock();
	int time = (int)(nowTime - m_aliveTimeStart) / (int)CLOCKS_PER_SEC;
	if (time>=ALIVE_TIME_MAX)
	{
		m_isAlive = false;
	}

}

void Bullet::Draw()
{
	m_model.Draw(GetPosition(),PMDModelType::AimingBullet);
}

void Bullet::OnCollisionEnter(Collision* otherCollision)
{
	m_isAlive = false;
}

void Bullet::Shot(const XMFLOAT3& _setPosition, const XMFLOAT3& _newDirection, const float& _shotspeed)
{
	SetPotision(_setPosition);
	SetDirection(_newDirection);
	m_speed=_shotspeed;
	m_isAlive = true;
	m_aliveTimeStart = clock();
}
