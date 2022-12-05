#pragma once
#include"EnemyAttackBase.h"
class StraightAttack:public EnemyAttackBase 
{
public:
	StraightAttack(const EnemyAttackType _type, const CollisionTag _tag);
	~StraightAttack();
	//更新
	void Update(DirectX::XMFLOAT3 _targetPos);
	
	/// <summary>
	/// 弾の発射
	/// </summary>
	/// <param name="_pos">打ち出すポジション</param>
	/// <param name="_targetPos">狙うポジション</param>
	/// <param name="_aimVec">弾の方向</param>
	void Shot(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));
	//当たり判定
	void OnCollisionEnter(class Collision* otherCollision)override;
	//描画
	void Draw();

private:

	//位置
	DirectX::XMFLOAT3 m_position;

	//時間
	class Time* m_timer;

	//  PMDモデルの管理
	class PMDModel& m_model;

	//移動ベクトル
	DirectX::XMFLOAT3 m_direction;

	//速度
	float m_speed;
	
};