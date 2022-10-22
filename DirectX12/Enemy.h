#pragma once

#include"ModelTypeData.h"
#include"Actor.h"
enum class EnemyType;
class Enemy:public Actor
{
public:
	Enemy(CollisionTag _tag, bool m_alive);
	~Enemy()override;
	//更新
	void Update(const DirectX::XMFLOAT3 _targetPos);
	//描画
	void Draw();
	//初期化
	void CollisionInit()override;
	//当たり判定処理
	void OnCollisionEnter(class Collision* otherCollision)override;

	const bool IsAlive() { return m_isAlive;}
	const EnemyType GetEnemyType(std::string _typeName);
	void LoadData(const EnemyType _enemyType);
	const DirectX::XMFLOAT3 GetAimVec() { return m_nowVec; };
	
private:
	void Move();
	void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);
	void AttackUpdate(const DirectX::XMFLOAT3 _targetPos);
	void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);

	void TakeAim(const DirectX::XMFLOAT3 _targetPos);
	void RotateAim();
	
	//モデル
	class PMDModel& m_model;            //  PMDモデルの管理
	class EffekseerManager& m_effect;
	class Sound& m_sound;
	class SupportJson& m_json;
	class EnemyShotDirector* m_enemyShotDirector;
	class Time* m_timer;

	//弾撃つときのフラグ管理
	struct ShotParam
	{
		void Init()
		{
			shotFlag = false;
		}
		bool shotFlag;
	};
	ShotParam m_shotParam;

	//向き
	DirectX::XMFLOAT3 m_nowVec;
	float m_direction;

	//移動慣性
	DirectX::XMFLOAT3 m_acceleration;
	DirectX::XMFLOAT3 m_velocity;

	//簡易AI用ステート
	enum class EnemyState
	{
		wait,
		attack,
		move,
	};
	EnemyState m_enemyState;

	//生存フラグ
	bool m_isAlive;

	//jsonで読んだ方が良い？
	const float NEAR_DISTANCE = 5.0f;
	PMDModelType m_modeltype;
	EnemyType m_enemyType;
	float m_speed;

	int WaitStateTime		= 1;
	int MoveStateTime		= 3;
	int AttackStateTime		= 5;

	int EnemyAttackCoolTime = 1;
};