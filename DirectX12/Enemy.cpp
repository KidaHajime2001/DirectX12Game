#include "Enemy.h"
#include"Singleton.h"
#include"Controller.h"
#include "ModelTypeData.h"
#include "PMDModel.h"
#include"Collision.h"
#include<random>
#include"EffekseerMng.h"
#include"EffectType.h"
#include"Sound.h"
#include"SoundType.h"
#include"SupportJSON.h"
#include"EnemyType.h"
#include"XMF3Math.h"
#include"Time.h"
#include"EnemyShotDirector.h"
#include "EnemyAttackType.h"
Enemy::Enemy(CollisionTag _tag, bool m_alive)
	:m_model(Singleton<PMDModel>::GetInstance())
	, m_effect(Singleton<EffekseerManager>::GetInstance())
	, m_sound(Singleton<Sound>::GetInstance())
	, Actor(_tag)
	, m_json(Singleton<SupportJson>::GetInstance())
	, m_isAlive(m_alive)
	, m_speed(1.0f)
	, m_timer(new Time())
	, m_enemyState(EnemyState::wait)
	,m_enemyShotDirector(new EnemyShotDirector())
	,m_direction(3.14)
{
	LoadData(EnemyType::AimShotEnemy);
	Init();
	m_shotParam.Init();
}


Enemy::~Enemy()
{
	delete m_timer;
	delete m_enemyShotDirector;
}

void Enemy::Update(const DirectX::XMFLOAT3 _targetPos)
{
	m_param.mCollision->Update();
	m_enemyShotDirector->Update(_targetPos);
	//¶‚«‚Ä‚¢‚ê‚Î
	if (m_isAlive)
	{
		if (m_enemyState==EnemyState::wait)
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
		else
		{
			TakeAim(_targetPos);
		}
		m_timer->SetTimer(5);
		Move();
	}


}
void Enemy::Draw()
{
	m_enemyShotDirector->Draw();
	m_model.Draw(GetPosition(), m_direction, m_modeltype);
}

void Enemy::Init()
{
	m_param.pos = XMFLOAT3(0,0,50);
}

void Enemy::OnCollisionEnter(Collision* otherCollision)
{
	
	if (otherCollision->GetTag()==CollisionTag::PlayerBullet)
	{
		OutputDebugString("Hit.\n");
		m_isAlive = false;
		m_sound.Play(SoundType::DefeatEnemySE,false,true);
		m_effect.PlayEffect(EffectType::DefeatRedEnemy, GetPosition(), false);
	}
}


void Enemy::LoadData(const EnemyType _enemyType)
{
	int typeNum = (int)_enemyType;

	m_param.mCollision = new Collision(this, m_json.GetInt(JsonDataType::Enemy, "Radius", "EnemyData", typeNum));
	m_modeltype = m_model.GetModelType(m_json.GetString(JsonDataType::Enemy, "VisualPattern", "EnemyData", typeNum));
	
	m_enemyType = GetEnemyType(m_json.GetString(JsonDataType::Enemy, "EnemyType", "EnemyData", typeNum));
}



void Enemy::Move()
{

	m_velocity = XMF3Math::AddXMFLOAT3(m_velocity, m_acceleration);
	m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos, m_velocity);
	m_acceleration = XMF3Math::ScalarXMFLOAT3(m_acceleration,0);

	
}

void Enemy::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	


	
	//Ž~‚Ü‚é‚æ‚¤‚É

	m_timer->SetTimer(1);
	if (m_timer->CheakTime())
	{

		m_enemyState = EnemyState::move;
	}
	
}
void Enemy::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
{

	XMFLOAT3 acc = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);
	//•’Ê‚É’Ç‚Á‚©‚¯‚é‚Æ‚«
	/*m_velocity = XMF3Math::ScalarXMFLOAT3(m_velocity,0);
	acc=XMF3Math::SetMagnitude(acc,m_speed);
	m_velocity = XMF3Math::AddXMFLOAT3(m_velocity,acc);*/

	//‰Á‘¬“xž‚Ý
	
	float distance = XMF3Math::LengthXMFLOAT3(acc);
	float speed = m_speed;
	float distanceRate;
	if (NEAR_DISTANCE>distance)
	{

		m_velocity = XMF3Math::ScalarXMFLOAT3(m_velocity, 0.7f);
		/* distanceRate = (distance / NEAR_DISTANCE);

		 speed *= distanceRate;*/
	}

	acc=XMF3Math::SetMagnitude(acc,speed);
	acc = XMF3Math::SubXMFLOAT3(acc,m_velocity);

	if (XMF3Math::LengthXMFLOAT3(acc)>0.02f)
	{
		acc=XMF3Math::SetMagnitude(acc,0.02f);
	};


	m_acceleration = XMF3Math::AddXMFLOAT3(m_acceleration,acc);

	m_timer->SetTimer(5);
	

	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::attack;
	}
}
void Enemy::AttackUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	auto Foward = XMF3Math::SubXMFLOAT3(_targetPos,m_param.pos);/*
	auto Right = XMF3Math::CrossXMFLOAT3(Foward, XMFLOAT3(0, 1, 0));*/

	m_enemyShotDirector->Shot(EnemyAttackType::StraightShot,m_param.pos,_targetPos,Foward);

	RotateAim();

	m_velocity = XMF3Math::ScalarXMFLOAT3(m_velocity, 0.7f);


	m_timer->SetTimer(5);
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::wait;
	}
}



void Enemy::TakeAim(const DirectX::XMFLOAT3 _targetPos)
{

	DirectX::XMFLOAT3 m_aimvec;
	m_aimvec = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);
	m_nowVec = m_aimvec;
	m_direction = atan2(m_aimvec.x, m_aimvec.z);
}

void Enemy::RotateAim()
{
	float x, y;
	x = m_nowVec.x * cos(1) - m_nowVec.z * sin(1);
	y = m_nowVec.x * sin(1) - m_nowVec.z * cos(1);
	
	m_direction = atan2(x,y);
	m_nowVec.x=x;
	m_nowVec.z=y;
}

const EnemyType Enemy::GetEnemyType(std::string _typeName)
{
	if (_typeName == "LesserEnemy")
	{
		return EnemyType::LesserEnemy;
	}
	else if (_typeName == "AimShotEnemy")
	{
		return EnemyType::AimShotEnemy;
	}
}

