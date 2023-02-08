#include "SnakeTail.h"
#include"Collision.h"
#include"Singleton.h"
#include"PmdModel.h"
#include "XMF3Math.h"
SnakeTail::SnakeTail(CollisionTag _tag, bool m_alive, DirectX::XMFLOAT3 _nowDirection)
	: Actor(_tag)
	,m_nowDirection(_nowDirection)
	, m_model(Singleton<PMDModel>::GetInstance())
{
	//半径データ
	m_param.mCollision->m_data.radius = m_radiusData;
	m_param.pos = XMFLOAT3(0, 1000, 0);
	m_modeltype = PMDModelType::Player;
}

SnakeTail::~SnakeTail()
{
}

void SnakeTail::Init()
{
	m_isAlive = true;
	m_param.mCollision->m_isValidity = true;
}

void SnakeTail::Update(DirectX::XMFLOAT3 _frontPos,DirectX::XMFLOAT3 _frontDirection)
{
	SetPotision(_frontPos);
	m_nowDirection = _frontDirection;
}

void SnakeTail::Draw()
{

		//描画
		//ポジション,向きを計算,描画タイプ
		m_model.Draw(
			GetPosition(),
			atan2(m_nowDirection.x, m_nowDirection.z),
			m_modeltype);
}

void SnakeTail::OnCollisionEnter(Collision* otherCollision)
{
}

void SnakeTail::SetVisible(bool _isVisible)
{
	m_isVisible = _isVisible;
}
