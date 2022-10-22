#pragma once
#include"Actor.h"
#include"ModelTypeData.h"

enum class EnemyType;

class EnemyBase:public Actor
{
public:
	EnemyBase(CollisionTag _tag, bool m_alive);
	virtual ~EnemyBase();
	void Init();
	//更新
	virtual void Update(const DirectX::XMFLOAT3 _targetPos);
	//描画
	void Draw();
	
	//データのロード
	void LoadData(const EnemyType _enemyType);

	const bool IsAlive() { return m_isAlive; }
	void Advent(DirectX::XMFLOAT3 _adventPosition);

	//当たり判定処理
	void OnCollisionEnter(class Collision* otherCollision)override;
	virtual void CollisionOriginal(class Collision* otherCollision);
protected:

	virtual void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);
	virtual void AttackUpdate(const DirectX::XMFLOAT3 _targetPos);
	virtual void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);

	//モデル
	class PMDModel& m_model;            //  PMDモデルの管理
	PMDModelType m_modeltype;
	
	//エフェクト
	class EffekseerManager& m_effect;

	//弾を打つクラス
	class EnemyShotDirector* m_enemyShotDirector;

	//サウンド
	class Sound& m_sound;

	//生存フラグ
	bool m_isAlive;



	//簡易AI用ステート
	enum class EnemyState
	{
		wait,
		attack,
		move,
	};
	EnemyState m_enemyState;

	//弾撃つときのフラグ管理
	struct AttackParam
	{
		float attackCoolTime;
		DirectX::XMFLOAT3 aimVec;
		void Init()
		{
			shotFlag = false;
		}
		bool shotFlag;
	};
	AttackParam m_attackParam;
	EnemyType m_enemyType;

	//向き
	DirectX::XMFLOAT3 m_nowDirection;
	const DirectX::XMFLOAT3 DEFAULT_DIRECTION = DirectX::XMFLOAT3(0,0,1);
	float m_direction;
	float m_speed;
	float m_radiusData;
};