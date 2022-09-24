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

	m_param.mCollision = new Collision(this, 2/*m_json.GetInt(JsonDataType::Enemy)*/);
	Init();
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	m_param.mCollision->Update();
	auto newpos = GetPosition();
	SetPotision(XMFLOAT3(newpos.x, newpos.y, newpos.z - m_speed));
	if (GetPosition().z < -100||!GetAlive())
	{
		Init();
	}
}
void Enemy::Draw()
{
	m_model.Draw(GetPosition(), 0, PMDModelType::RedEnemy);
}

void Enemy::Init()
{
	//ランダムに初期化一の値を生成
	float randInitNumber=(rand()%100)-50;
	
	float randSpeedNumber = (rand() % 6 + 1);

	m_param.IsAlive = true;
	m_speed=randSpeedNumber;
	//  取得したデータを元に初
	SetPotision(XMFLOAT3(randInitNumber,0, 450));
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


