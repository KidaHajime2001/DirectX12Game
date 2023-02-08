#pragma once
#include"EnemyBase.h"
class StraightShotEnemy:public EnemyBase
{
public:
	//コンストラクタ
	StraightShotEnemy(CollisionTag _tag, bool m_alive);
	~StraightShotEnemy();
	//更新
	void Update(const DirectX::XMFLOAT3 _targetPos);
	void Draw()override;
	
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
	enum SEState
	{
		Attack,
		SpecialAT,
	};
	SEState seState;
	enum SpecialState
	{
		Aiming,
		CircleMove,
	};
	SpecialState m_specialState;
	const DirectX::XMFLOAT3 TARGET_SPACE = XMFLOAT3(1,0,0);
	float m_specialrotate=0.0f;

};