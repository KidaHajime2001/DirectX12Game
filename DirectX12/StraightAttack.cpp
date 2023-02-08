#include "StraightAttack.h"
#include"Time.h"
#include"PmdModel.h"
#include"ModelTypeData.h"
#include "XMF3Math.h"
#include"Collision.h"
StraightAttack::StraightAttack(const EnemyAttackType _type, const CollisionTag _tag)
	:EnemyAttackBase(_type, _tag)
	, m_timer(new Time())
	, m_model(Singleton<PMDModel>::GetInstance())
	, m_speed(1.0f)
{
	//弾当たり判定の大きさ
	m_param.mCollision->m_data.radius = m_attackCollisionRadius;
}

StraightAttack::~StraightAttack()
{
	delete m_timer;
}

void StraightAttack::Update(DirectX::XMFLOAT3 _targetPos)
{
	if (m_isAlive)
	{
		//移動分の計算
		m_direction = XMF3Math::NormalizeXMFLOAT3(m_direction);
		auto vel = XMF3Math::ScalarXMFLOAT3(m_direction,m_speed);
		m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos,vel);
	}
	if (m_timer->CheakTime())
	{
		//時間経過でリセット
		Init();
	}
}

void StraightAttack::Shot(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec)
{
	//発射時の初期化処理
	m_param.pos = _pos;
	m_timer->SetTimer(5);
	m_direction = _aimVec;
	m_isAlive = true;
	m_param.mCollision->m_isValidity = true;
}



void StraightAttack::OnCollisionEnter(Collision* otherCollision)
{
	if (otherCollision->GetTag() == CollisionTag::Player)
	{
		OutputDebugString("プレイヤーに当たりました。");
	}
	if (otherCollision->GetTag() == CollisionTag::Shield)
	{
		Init();
	}
}

void StraightAttack::Draw()
{
	if (m_isAlive)
	{
		//Defaultの角度が90度ずれているので調整
		auto direction = XMF3Math::RotateVec2_XZ(m_direction,90.0f);
		auto dir = atan2(direction.x, direction.z);
		//角度を合わせて描画
		m_model.Draw(GetPosition(), dir, PMDModelType::AimingBullet);
	}
}
