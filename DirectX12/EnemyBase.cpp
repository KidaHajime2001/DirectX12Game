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
	,m_isHit(false)
{
	//半径データ
	m_param.mCollision->m_data.radius = m_radiusData;
	//でフォルト向き設定
	m_nowDirection = DEFAULT_DIRECTION;
	m_param.pos = XMFLOAT3(0, 0, 0);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
	//オブジェクトプール設計の為使いまわせるよう、基本的な設定を初期化する
	//生存フラグをON
	//当たり判定をON
	//プレイヤーに当たっているかのフラグをOFF
	m_isAlive = true;
	m_param.mCollision->m_isValidity = true;
	m_isHit = false;
}


void EnemyBase::Update(const DirectX::XMFLOAT3 _targetPos)
{
}

void EnemyBase::Draw()
{
	//描画
	//ポジション,向きを計算,描画タイプ
	m_model.Draw(
		GetPosition(), 
		atan2(m_nowDirection.x, m_nowDirection.z), 
		m_modeltype);
}

void EnemyBase::LoadData(const EnemyType _enemyType)
{
}

void EnemyBase::Advent(DirectX::XMFLOAT3 _adventPosition)
{
	//ポジションはEnemyマネージャーから受け取る
	//若干出現を散らす処理
	auto randPos = XMFLOAT3(rand() % 10 - 10, 0, rand() % 10 - 10);
	m_param.pos = XMF3Math::AddXMFLOAT3(randPos,_adventPosition);
}

void EnemyBase::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//EnemyBaseを継承した他クラスに記述
}

void EnemyBase::AttackUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//EnemyBaseを継承した他クラスに記述
}

void EnemyBase::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//EnemyBaseを継承した他クラスに記述
}
void EnemyBase::OnCollisionEnter(Collision* otherCollision)
{
	//他当たり判定のタグがEnemyだった場合
	if (otherCollision->GetTag() == CollisionTag::Enemy)
	{
		//他エネミーの位置を取得
		XMFLOAT3 enemyPos = otherCollision->GetPosition();
		//他エネミーとの距離算出
		XMFLOAT3 otherToMe = XMF3Math::SubXMFLOAT3(m_param.pos, enemyPos);
		//離れる距離
		XMFLOAT3 awayVec;
		//半径　+　半径　+　細かい隙間距離
		float awayRange = (m_param.mCollision->GetRadius() + otherCollision->GetRadius() + 0.01f);

		//完全に重なった場合の対策
		if (XMF3Math::LengthXMFLOAT3(otherToMe) == 0)
		{
			//ランダムに散らす
			float numX = (rand() % 10) - 10;
			float numZ = (rand() % 10) - 10;
			awayVec = XMFLOAT3(numX, 0, numZ);
			awayVec = XMF3Math::SetMagnitude(awayVec, awayRange);
		}
		awayVec = XMF3Math::SetMagnitude(otherToMe, awayRange);
		//離す
		m_param.pos = XMF3Math::AddXMFLOAT3(enemyPos, awayVec);

	}
	if (otherCollision->GetTag() == CollisionTag::PlayerBullet)
	{
		//プレイヤーの弾に接触
		m_isHit = true;
	}
	//派生クラス別の接触処理
	CollisionOriginal(otherCollision);
}

void EnemyBase::CollisionOriginal(Collision* otherCollision)
{
	//EnemyBaseを継承した他クラスに記述
}

