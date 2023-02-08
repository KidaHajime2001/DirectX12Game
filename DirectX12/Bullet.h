#pragma once
#include"Actor.h"
#include<time.h>
//プレイヤーの弾クラス
class Bullet : public Actor
{
public:
	//コンストラクタ、デストラクタ
	Bullet(CollisionTag _tag,const bool _alive);
	~Bullet();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw(); 
	//当たり判定
	void OnCollisionEnter(class Collision* otherCollision)override;
	//向きのセッター
	void SetDirection(XMFLOAT3 _newDirection) { m_directionVector = _newDirection; };
	/// <summary>
	/// ショット
	/// </summary>
	/// <param name="_setPosition">初期位置</param>
	/// <param name="_newDirection">弾の向き</param>
	/// <param name="_shotspeed">弾の速度</param>
	void Shot(const XMFLOAT3& _setPosition,const XMFLOAT3& _newDirection,const float& _shotspeed);
	/// <summary>
	/// 拡散ショット
	/// </summary>
	/// <param name="_setPosition">初期位置</param>
	/// <param name="_newDirection">弾の向き</param>
	/// <param name="_shotspeed">弾の速度</param>
	void SpreadShot(const XMFLOAT3& _setPosition, const XMFLOAT3& _newDirection, const float& _shotspeed);

	const bool IsAlive() { return m_isAlive; };
private:
	//  PMDモデルの管理
	class PMDModel& m_model;
	//当たり判定の大きさ
	const int RADIUS_NUM = 1;
	//弾の生存時間
	float m_aliveTime = 1;
	//
	XMFLOAT3 m_directionVector = { 0,0,0 };

	clock_t m_aliveTimeStart;
	float m_speed;
	bool m_isAlive;
};
