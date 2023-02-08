#include"SnakeEnemy.h"
#include"PmdModel.h"
#include"Collision.h"
#include"Time.h"
#include"XMF3Math.h"
#include"ModelTypeData.h"
#include"EnemyShotDirector.h"
#include"Sound.h"
#include"SoundType.h"
#include"SnakeTail.h"
SnakeEnemy::SnakeEnemy(CollisionTag _tag, bool m_alive)
	:EnemyBase(_tag, m_alive)
	, m_timer(new Time())
	, m_shotNum(0)
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
	m_modeltype = PMDModelType::Player;
	//初期位置
	m_param.pos = XMFLOAT3(0,1000,0);
	//移動速度
	//外部データから持ってきたい
	m_speed = 0.5f;

	m_enemyType = EnemyType::StraightShotEnemy;
	
	for (int i = 0; i < TAIL_NUMBER; i++)
	{
		m_snakeTails.push_back(new SnakeTail(_tag, m_alive, m_nowDirection));
	}
	for (int i = 0; i < TAIL_NUMBER; i++)
	{
		m_tailsPosition.push_back(GetPosition());
	}
	for (int i = 0; i < TAIL_NUMBER; i++)
	{
		m_beforeTailsPosition.push_back(GetPosition());
	}
	for (int i = 0; i < TAIL_NUMBER; i++)
	{
		m_tailsDirection.push_back(m_nowDirection);
	}
	for (int i = 0; i < TAIL_NUMBER; i++)
	{
		m_beforeTailsDirection.push_back(m_nowDirection);
	}
}

SnakeEnemy::~SnakeEnemy()
{
	delete m_enemyShotDirector;
	delete m_timer;
}

void SnakeEnemy::Init()
{
	//オブジェクトプール設計の為使いまわせるよう、基本的な設定を初期化する
	//生存フラグをON
	//当たり判定をON
	//プレイヤーに当たっているかのフラグをOFF
	m_isAlive = true;
	m_param.mCollision->m_isValidity = true;
	m_isHit = false;

	for (int i = 0; i < TAIL_NUMBER; i++)
	{
		m_tailsPosition[i] = XMFLOAT3(0, 1000, 0);
	}
	for (int i = 0; i < TAIL_NUMBER; i++)
	{
		m_beforeTailsPosition[i]= XMFLOAT3(0, 1000, 0);
	}
}

void SnakeEnemy::Update(const DirectX::XMFLOAT3 _targetPos)
{

	if (m_isAlive)
	{
		m_chaseFlame++;
		int i = 0;
		for (auto tail : m_snakeTails)
		{
			tail->Update(m_tailsPosition[i], m_tailsDirection[i]);
			i++;
		}
		MoveUpdate(_targetPos);
		if (m_chaseFlame % CHASE_TIME == 0)
		{
			SetTailPosition();
			SetTailDirection();
		}
	}
}

void SnakeEnemy::Draw()
{
	if (m_isAlive)
	{

		//描画
		//ポジション,向きを計算,描画タイプ
		m_model.Draw(
			GetPosition(),
			atan2(m_nowDirection.x, m_nowDirection.z),
			m_modeltype);
		for (auto tail : m_snakeTails)
		{
			tail->Draw();
		}
	}
}


void SnakeEnemy::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
}

void SnakeEnemy::AttackUpdate(const DirectX::XMFLOAT3 _targetPos)
{
}

void SnakeEnemy::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//ターゲットまでの位置
	XMFLOAT3 acc = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);

	//速度の制限
	float speed = 1.0f;
	acc = XMF3Math::SetMagnitude(acc, speed);

	acc = XMF3Math::SubXMFLOAT3(acc, m_velocity);

	if (XMF3Math::LengthXMFLOAT3(acc) > 0.02f)
	{
		acc = XMF3Math::SetMagnitude(acc, 0.02f);
	};


	m_acceleration = XMF3Math::AddXMFLOAT3(m_acceleration, acc);

	m_velocity = XMF3Math::AddXMFLOAT3(m_velocity, m_acceleration);
	m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos, m_velocity);
	m_acceleration = XMF3Math::ScalarXMFLOAT3(m_acceleration, 0);

	////プレイヤーと自分との距離を算出
	//auto diff = XMF3Math::SubXMFLOAT3(_targetPos, m_param.pos);
	////向き
	m_nowDirection = m_velocity;
	////移動ベクトル作成
	//diff = XMF3Math::SetMagnitude(diff, m_speed);
	//m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos, diff);
}

void SnakeEnemy::CollisionOriginal(Collision* otherCollision)
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


void SnakeEnemy::SetTailPosition()
{
	for (int i=0; i<TAIL_NUMBER;i++)
	{
		m_beforeTailsPosition[i] = m_tailsPosition[i];
	}

	for (int i = 1; i < TAIL_NUMBER; i++)
	{
		m_tailsPosition[i] = m_beforeTailsPosition[i - 1];
		
	}

	m_tailsPosition[0] = GetPosition();

}

void SnakeEnemy::SetTailDirection()
{
	for (int i = 0; i < TAIL_NUMBER; i++)
	{
		m_beforeTailsDirection[i] = m_tailsDirection[i];
	}

	for (int i = 1; i < TAIL_NUMBER; i++)
	{
		m_tailsDirection[i] = m_beforeTailsDirection[i - 1];

	}

	m_tailsDirection[0] = m_nowDirection;
}
