#pragma once
#include<DirectXMath.h>
#include"Actor.h"
#include"EnemyAttackType.h"
class EnemyAttackBase:public Actor
{
public:
	
	EnemyAttackBase(const EnemyAttackType _type,const CollisionTag _tag);
	~EnemyAttackBase();


	 void Init();

	 //派生先はupdateを継承
	 virtual void Update(const DirectX::XMFLOAT3 _targetPos);
	 /// <summary>
	 /// 弾を撃つクラス
	 /// </summary>
	 /// <param name="_position">発射位置</param>
	 /// <param name="_targetPos">目標位置</param>
	 /// <param name="_aimVec">撃ちたい方向ベクトル</param>
	 virtual void Shot(const DirectX::XMFLOAT3 _position,const DirectX::XMFLOAT3 _targetPos,  const DirectX::XMFLOAT3 _aimVec);
	 //描画
	 virtual void Draw();
	 //生存しているか
	 const bool IsAlive() { return m_isAlive; };

protected:
	//弾の種類
	EnemyAttackType m_enemyType;

	//弾が生存しているか？
	bool m_isAlive;

	//外部fileからよみたい
	float m_attackCollisionRadius=1;
};