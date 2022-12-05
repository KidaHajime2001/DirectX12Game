#pragma once
#include"Actor.h"
#include"ModelTypeData.h"
#include"EnemyType.h"
enum class EnemyType;

//エネミーの共通部分
class EnemyBase :public Actor
{
public:
	//コンストラクタ
	EnemyBase(CollisionTag _tag, bool m_alive);
	virtual ~EnemyBase();
	//初期化
	void Init();
	//更新
	virtual void Update(const DirectX::XMFLOAT3 _targetPos);
	//描画
	void Draw();

	//データのロード
	void LoadData(const EnemyType _enemyType);
	
	//生存フラグ
	const bool IsAlive() { return m_isAlive; }

	/// <summary>
	/// 設定した位置に出現
	/// </summary>
	/// <param name="_adventPosition">
	/// 出現するポジション
	/// </param>
	void Advent(DirectX::XMFLOAT3 _adventPosition);

	
	const EnemyType GetEnemyType() { return m_enemyType; };
	const bool GetDefeatFlag() { return m_isHit; };
protected:
	//当たり判定処理
	void OnCollisionEnter(class Collision* otherCollision);

	/// <summary>
	/// 固有の当たり判定アクション
	/// 共通の部分のコピペを減らせるのではないかと考えた結果こうなった
	/// 正解かは不明
	/// </summary>
	/// <param name="otherCollision">
	/// 当たった他オブジェクト 
	/// </param>
	virtual void CollisionOriginal(class Collision* otherCollision);

	

	/// <summary>
	/// 簡易AIの待機行動
	/// </summary>
	/// <param name="_targetPos">
	/// ターゲット（プレイヤー）の位置
	/// </param>
	virtual void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);

	/// <summary>
	/// 簡易AIの攻撃行動
	/// </summary>
	/// <param name="_targetPos">
	///ターゲットの位置
	/// </param>
	virtual void AttackUpdate(const DirectX::XMFLOAT3 _targetPos);

	/// <summary>
	/// 簡易AIの移動行動
	/// </summary>
	/// <param name="_targetPos">
	/// ターゲットの位置
	/// </param>
	virtual void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);

	//モデル
	class PMDModel& m_model;            //  PMDモデルの管理
	PMDModelType m_modeltype;			//　PMDモデルのタイプ
	
	//エフェクト
	class EffekseerManager& m_effect;

	//弾を撃つクラス
	class EnemyShotDirector* m_enemyShotDirector;

	//サウンド
	class Sound& m_sound;

	//生存フラグ
	bool m_isAlive;

	//プレイヤーの弾に当たったかどうか
	bool m_isHit;

	//簡易AI用ステート
	enum class EnemyState
	{
		wait,
		attack,
		move,
	};
	EnemyState m_enemyState;

	//enemyのタイプ
	EnemyType m_enemyType;

	//向き
	DirectX::XMFLOAT3 m_nowDirection;

	//最初に向いている方向
	const DirectX::XMFLOAT3 DEFAULT_DIRECTION = DirectX::XMFLOAT3(0,0,1);

	//移動速度
	float m_speed;
	//当たり判定の仮置き
	float m_radiusData;
};