#include "StraightShotEnemy.h"
#include"PmdModel.h"
#include"Collision.h"
#include"Time.h"
#include"XMF3Math.h"
#include"ModelTypeData.h"
#include"EnemyShotDirector.h"
#include"Sound.h"
#include"SoundType.h"
StraightShotEnemy::StraightShotEnemy(CollisionTag _tag, bool m_alive)
	:EnemyBase(_tag, m_alive)
	, m_timer(new Time())
	,m_shotNum(0)
	,seState(SEState::Attack)
	,m_specialState(SpecialState::CircleMove)
{
	//当たり判定
	//外部データから持ってきたい
	m_radiusData = 2;
	m_param.mCollision->m_data.radius = m_radiusData;

	//オブジェクトプール登録して一旦当たり判定をOFF
	m_param.mCollision->m_isValidity = false;

	//ショットクラス作成
	m_enemyShotDirector = new EnemyShotDirector();

	//描画するデータ
	m_modeltype = PMDModelType::StraightEnemy;

	//移動速度
	//外部データから持ってきたい
	m_speed = 0.1f;

	m_enemyType=EnemyType::StraightShotEnemy;
}

StraightShotEnemy::~StraightShotEnemy()
{
	delete m_enemyShotDirector;
	delete m_timer;
}



void StraightShotEnemy::Update(const DirectX::XMFLOAT3 _targetPos)
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

void StraightShotEnemy::Draw()
{
	//描画
	//ポジション,向きを計算,描画タイプ
	m_model.Draw(
		GetPosition(),
		atan2(m_nowDirection.x,m_nowDirection.z),
		m_modeltype);
}




void StraightShotEnemy::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//待機時間二秒
	m_timer->SetTimer(2);
	//時間が来たら次状態に遷移
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::attack;
		if (rand() % 3==0)
		{
			seState = SEState::SpecialAT;
		}
		else
		{
			seState = SEState::Attack;
		}
		
	}
}

void StraightShotEnemy::AttackUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	switch (seState)
	{
	case SEState::Attack:
		//プレイヤーと自分との距離を算出
		auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);

		//向き
		m_nowDirection = diff;

		//発射間隔
		m_timer->SetTimer(0.25f);

		//ショットを撃つ
		if (m_timer->CheakTime())
		{
			m_enemyShotDirector->Shot(EnemyAttackType::StraightShot, m_param.pos, _targetPos, diff);
			m_shotNum++;
		}
		//攻撃の回数が基底の数を超えたら
		if (ATTACK_NUM_MAX <= m_shotNum)
		{
			//ショットのリセットと状態の遷移
			m_shotNum = 0;
			m_enemyState = EnemyState::wait;
		}
		break;
	case SEState::SpecialAT:
		if (m_specialState== SpecialState::CircleMove)
		{
			auto aimPos = XMF3Math::AddXMFLOAT3(
				XMF3Math::SetMagnitude( TARGET_SPACE,50.0f), _targetPos);
			//プレイヤーと自分との距離を算出
			auto diff = XMF3Math::SubXMFLOAT3(aimPos, m_param.pos);
			

			//向き
			m_nowDirection = diff;
			diff = XMF3Math::SetMagnitude(diff, m_speed*10);
			//移動
			m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos, diff);
			if (XMF3Math::LengthXMFLOAT3(XMF3Math::SubXMFLOAT3(aimPos, m_param.pos))<5.0f)
			{
				m_specialState = SpecialState::Aiming;
			}
			
		}
		else if (m_specialState == SpecialState::Aiming)
		{
			auto vec = XMF3Math::RotateVec2_XZ(TARGET_SPACE, m_specialrotate++);
 			m_param.pos = XMF3Math::AddXMFLOAT3(GetPosition(),vec);
			//発射間隔
			m_timer->SetTimer(0.5f);

			auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);
			//ショットを撃つ
			if (m_timer->CheakTime())
			{
				m_enemyShotDirector->Shot(EnemyAttackType::StraightShot, m_param.pos, _targetPos, diff);
				m_shotNum++;
			}
			if (m_shotNum>15)
			{
				m_enemyState = EnemyState::move;
			}
		}
		break;
	default:
		break;
	}
	
	
}

void StraightShotEnemy::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
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
		m_enemyState = EnemyState::move;
	}
}

void StraightShotEnemy::CollisionOriginal(Collision* otherCollision)
{
	if (otherCollision->GetTag() == CollisionTag::PlayerBullet)
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
