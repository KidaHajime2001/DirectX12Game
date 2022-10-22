#pragma once
#include<DirectXMath.h>
#include"Actor.h"
#include"EnemyAttackType.h"
class EnemyAttackBase:public Actor
{
public:
	EnemyAttackBase(const EnemyAttackType _type,const CollisionTag _tag);
	~EnemyAttackBase();

	//îhê∂êÊÇÕupdateÇåpè≥
	 void Init();
	 virtual void Update(const DirectX::XMFLOAT3 _targetPos);
	 virtual void Shot(const DirectX::XMFLOAT3 _position,const DirectX::XMFLOAT3 _targetPos,  const DirectX::XMFLOAT3 _aimVec);
	 virtual void Draw();
	 const bool IsAlive() { return m_isAlive; };

protected:
	EnemyAttackType m_enemyType;
	bool m_isAlive;
	float m_attackCollisionRadius=1;
};