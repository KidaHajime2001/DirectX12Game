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
Enemy::Enemy(CollisionTag _tag, bool Alive)
	:m_model(Singleton<PMDModel>::GetInstance())
	, Actor(_tag, Alive)
	, m_effect(Singleton<EffekseerManager>::GetInstance())
	, m_sound(Singleton<Sound>::GetInstance())
	, m_json(Singleton<SupportJson>::GetInstance())
{

	m_param.mCollision = new Collision(this, m_json.GetInt(JsonDataType::Enemy,"Radius","EnemyData", 1));	
	modeltype = m_model.GetModelType(m_json.GetString(JsonDataType::Enemy, "VisualPattern", "EnemyData", 1));
	Init();
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	m_param.mCollision->Update();
	
}
void Enemy::Draw()
{
	m_model.Draw(GetPosition(), 0, modeltype);
}

void Enemy::Init()
{
	
}

void Enemy::OnCollisionEnter(Collision* otherCollision)
{
	
	if (otherCollision->GetTag()==CollisionTag::PlayerBullet)
	{
		OutputDebugString("Hit.\n");
		m_param.IsAlive = false;
		m_sound.Play(SoundType::DefeatEnemySE,false,true);
		m_effect.PlayEffect(EffectType::DefeatRedEnemy, GetPosition(), false);
	}
}


