#pragma once
#include<DirectXMath.h>
#include "EnemyAttackType.h"
#include<iostream>
#include<list>

class EnemyShotDirector
{
public:
	EnemyShotDirector();
	~EnemyShotDirector();
	void Shot(const EnemyAttackType _type, const DirectX::XMFLOAT3 _pos,const DirectX::XMFLOAT3 _targetPos,DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0,0,0));

private:

	void AimShot( const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));
	void StraightShot(const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));
	void SpreadShot(const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));
	std::list<class EnemyAttackBase*> m_attackList;
	std::list<class EnemyAttackBase*> m_deleteList;
	class EnemyAttackPool& m_enemyAttackPool;
	const int SPREAD_SHOT_NUM=3;

};

