#include "LesserEnemy.h"
#include"PmdModel.h"
#include"Collision.h"
#include"Time.h"
#include"XMF3Math.h"
#include"ModelTypeData.h"
#include"Sound.h"
#include"SoundType.h"
LesserEnemy::LesserEnemy(CollisionTag _tag, bool m_alive)
	:EnemyBase(_tag,m_alive)
	,m_timer(new Time())
{
	//当たり判定
	//外部データから持ってきたい
	m_radiusData = 2;
	m_param.mCollision->m_data.radius = m_radiusData;
	//描画するデータ
	m_modeltype = PMDModelType::LesserEnemy;
	//オブジェクトプール登録して一旦当たり判定をOFF
	m_param.mCollision->m_isValidity = false;
	
	//移動速度
	//外部データから持ってきたい
	m_speed = 0.3f;
	m_enemyType = EnemyType::LesserEnemy;
	
}
LesserEnemy::~LesserEnemy()
{
	delete m_timer;
}

void LesserEnemy::Init()
{
	//オブジェクトプール設計の為使いまわせるよう、基本的な設定を初期化する
	//生存フラグをON
	//当たり判定をON
	//プレイヤーに当たっているかのフラグをOFF
	//たくさん出現するのでこいつだけ特別な処理
	m_param.mCollision->m_isValidity = true;
	m_isAlive = true;
	auto randPos=XMFLOAT3(rand()%10-10, 0, rand() % 10 - 10);
	m_param.pos = randPos;
}

void LesserEnemy::Update(const DirectX::XMFLOAT3 _targetPos)
{
	//生きていれば
	if (m_isAlive)
	{
		if (m_enemyState == EnemyState::wait)
		{
			WaitUpdate(_targetPos);
		}
		if (m_enemyState == EnemyState::move)
		{
			MoveUpdate(_targetPos);
		}
	}



}


void LesserEnemy::CollisionOriginal(Collision* otherCollision)
{
	if (otherCollision->GetTag()==CollisionTag::PlayerBullet)
	{
		//死亡演出
		m_effect.PlayEffect(EffectType::DefeatLesserEnemy, GetPosition(), false);
		m_sound.Play(SoundType::DefeatLesserEnemySE, false, true);

		//当たり判定OFF
		m_param.mCollision->m_isValidity = false;
		//生存フラグOFF
		m_isAlive = false;
	}
}


void LesserEnemy::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//待機時間二秒
	m_timer->SetTimer(2);
	//時間が来たら次状態に遷移
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::move;
	}
}

void LesserEnemy::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//プレイヤーと自分との距離を算出
	auto diff = XMF3Math::SubXMFLOAT3(_targetPos,m_param.pos);
	//向き
	m_nowDirection = diff;
	//移動ベクトル作成
	diff = XMF3Math::SetMagnitude(diff,m_speed);
	m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos,diff);
	//五秒間移動
	m_timer->SetTimer(5);
	//待機状態に遷移
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::wait;
	}
}
