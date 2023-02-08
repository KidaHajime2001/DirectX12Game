#include "SpreadShotEnemy.h"
#include"PmdModel.h"
#include"Collision.h"
#include"Time.h"
#include"XMF3Math.h"
#include"ModelTypeData.h"
#include"EnemyShotDirector.h"
#include"Sound.h"
#include"SoundType.h"

SpreadShotEnemy::SpreadShotEnemy(CollisionTag _tag, bool m_alive)
	:EnemyBase(_tag, m_alive)
	, m_timer(new Time())
	, m_shotNum(0)
	
{
	//当たり判定
	//外部データから持ってきたい
	m_radiusData = 2;
	m_param.mCollision->m_data.radius = m_radiusData;

	//描画するデータ
	m_modeltype = PMDModelType::SpreadEnemy;

	//オブジェクトプール登録して一旦当たり判定をOFF
	m_param.mCollision->m_isValidity = false;

	//ショットクラス作成
	m_enemyShotDirector = new EnemyShotDirector();

	//移動速度
	//外部データから持ってきたい
	m_speed = 0.1f;

	m_enemyType = EnemyType::SpreadShotEnemy;
}

SpreadShotEnemy::~SpreadShotEnemy()
{
	delete m_timer;
	delete m_enemyShotDirector;
}



void SpreadShotEnemy::Update(const DirectX::XMFLOAT3 _targetPos)
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
		if (m_enemyState == EnemyState::attack)
		{
			AttackUpdate(_targetPos);
		}
		
	}

}



void SpreadShotEnemy::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//待機時間二秒
	m_timer->SetTimer(2);
	//時間が来たら次状態に遷移
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::attack;
	}
}

void SpreadShotEnemy::AttackUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//プレイヤーと自分との距離を算出
	auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);
	//向き
	m_nowDirection = diff;
	//発射間隔
	m_timer->SetTimer(1);

	//ショットを撃つ」
	if (m_timer->CheakTime())
	{
		m_enemyShotDirector->Shot(EnemyAttackType::SpreadShot, m_param.pos, _targetPos, diff);
		m_shotNum++;
	}

	//攻撃の回数が基底の数を超えたら
	if (ATTACK_NUM_MAX <= m_shotNum)
	{
		//ショットのリセットと状態の遷移
		m_shotNum = 0;
		m_enemyState = EnemyState::move;
	}
}

void SpreadShotEnemy::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//プレイヤーと自分との距離を算出
	auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);
	//向き
	m_nowDirection = diff;
	diff = XMF3Math::SetMagnitude(diff, m_speed);
	//移動
	m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos, diff);

	m_timer->SetTimer(5);
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::wait;
	}
}

void SpreadShotEnemy::CollisionOriginal(Collision* otherCollision)
{
	if (otherCollision->GetTag() == CollisionTag::PlayerBullet
		)
	{
		//死亡演出
		m_effect.PlayEffect(EffectType::DefeatHigherEnemy, GetPosition(), false);
		m_sound.Play(SoundType::DefeatEnemySE, false, true);

		//当たり判定OFF
		m_param.mCollision->m_isValidity = false;
		//生存フラグOFF
		m_isAlive = false;
	}
}
