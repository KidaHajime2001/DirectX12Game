#pragma once
#include"EnemyBase.h"
class SnakeEnemy :public EnemyBase
{
public:
	//コンストラクタ
	SnakeEnemy(CollisionTag _tag, bool m_alive);
	~SnakeEnemy();
	void Init()override;
	//更新
	void Update(const DirectX::XMFLOAT3 _targetPos);
	void Draw()override;
	void SetTailPosition();
	void SetTailDirection();
private:
	/// <summary>
   /// 簡易AIの待機行動
   /// </summary>
   /// <param name="_targetPos">
   /// ターゲット（プレイヤー）の位置
   /// </param>
	void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);
	/// <summary>
   /// 簡易AIの攻撃行動
   /// </summary>
   /// <param name="_targetPos">
   /// ターゲット（プレイヤー）の位置
   /// </param>
	void AttackUpdate(const DirectX::XMFLOAT3 _targetPos);
	/// <summary>
   /// 簡易AIの移動行動
   /// </summary>
   /// <param name="_targetPos">
   /// ターゲット（プレイヤー）の位置
   /// </param>
	void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);
	/// <summary>
   /// 固有の動き、
   /// </summary>
   /// <param name="otherCollision">
   ///　接触した他当たり判定情報
   /// </param>
	void CollisionOriginal(class Collision* otherCollision);
	//弾を撃つクラス
	class EnemyShotDirector* m_enemyShotDirector;

	//時間を図るクラス
	class Time* m_timer;
	//ショット数
	int m_shotNum;
	//攻撃回数の最大値
	const int ATTACK_NUM_MAX = 3;

	std::vector<class SnakeTail*> m_snakeTails;
	std::vector<XMFLOAT3> m_tailsPosition;
	std::vector<XMFLOAT3> m_beforeTailsPosition;

	std::vector<XMFLOAT3> m_tailsDirection;
	std::vector<XMFLOAT3> m_beforeTailsDirection;
	DirectX::XMFLOAT3 m_acceleration;
	DirectX::XMFLOAT3 m_velocity;

	const int TAIL_NUMBER=10;
	const int CHASE_TIME = 10;
	int m_chaseFlame=0;
};