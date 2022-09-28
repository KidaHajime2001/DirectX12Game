#pragma once
#include"EnemyAttackBase.h"
class HormingAimShot:public EnemyAttackBase
{
public:
	void Update(DirectX::XMFLOAT3 _targetPos);
	void Shot(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _aimVec);
private:
	DirectX::XMFLOAT3 m_position;
};
