#include "EnemyShotDirector.h"
#include"EnemyAttackPool.h"
#include"Singleton.h"
#include"EnemyAttackType.h"
#include <windows.h>
#include"EnemyAttackBase.h"
#include"XMF3Math.h"
EnemyShotDirector::EnemyShotDirector()
	:m_enemyAttackPool(Singleton<EnemyAttackPool>::GetInstance())
{
	m_enemyAttackPool.CreateAll();
}
EnemyShotDirector::~EnemyShotDirector()
{
	m_enemyAttackPool.DestroyAll();
	m_deleteList.clear();
	m_attackList.clear();
}



void EnemyShotDirector::Shot(const EnemyAttackType _type, const  DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec)
{

	switch (_type)
	{
	case EnemyAttackType::SpreadShot:

		SpreadShot(_pos, _targetPos, _aimVec);
		break;
	case EnemyAttackType::StraightShot:
		StraightShot(_pos, _targetPos, _aimVec);
		break;
	case EnemyAttackType::HormingShot:

		HormingShot(_pos, _targetPos);
		break;
	default:
		break;
	}
}


void EnemyShotDirector::HormingShot(const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec)
{
	auto shot = m_enemyAttackPool.GetUnUsedEnemyAttack(EnemyAttackType::HormingShot);
	if (!shot)
	{

		OutputDebugString("‚Í‚¸‚ê\n");
		return ;
	}
	m_attackList.emplace_back(shot);
	m_attackList.back()->Shot(_pos,_targetPos,_aimVec);
}

void EnemyShotDirector::StraightShot(const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec)
{
	auto shot = m_enemyAttackPool.GetUnUsedEnemyAttack(EnemyAttackType::StraightShot);
	if (!shot)
	{

		OutputDebugString("‚Í‚¸‚ê\n");
		return;
	}
	m_attackList.emplace_back(shot);
	m_attackList.back()->Shot(_pos, _targetPos, _aimVec);
}

void EnemyShotDirector::SpreadShot(const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec)
{
	XMFLOAT3 RightVec = XMFLOAT3(0,0,0);
	XMFLOAT3 LeftVec = XMFLOAT3(0,0,0);

	RightVec = XMF3Math::RotateVec2_XZ(_aimVec,15);
	
	LeftVec = XMF3Math::RotateVec2_XZ(_aimVec, -15);
	

	auto middleShot = m_enemyAttackPool.GetUnUsedEnemyAttack(EnemyAttackType::StraightShot);
	if (!middleShot)
	{
		OutputDebugString("‚Í‚¸‚ê\n");
		return;
	}

	m_attackList.emplace_back(middleShot);
	m_attackList.back()->Shot(_pos, _targetPos, _aimVec);

	auto rightShot = m_enemyAttackPool.GetUnUsedEnemyAttack(EnemyAttackType::StraightShot);

	if (!rightShot)
	{
		OutputDebugString("‚Í‚¸‚ê\n");
		return;
	}
	m_attackList.emplace_back(rightShot);
	m_attackList.back()->Shot(_pos, _targetPos, RightVec);


	auto leftShot = m_enemyAttackPool.GetUnUsedEnemyAttack(EnemyAttackType::StraightShot);

	if (!leftShot)
	{
		OutputDebugString("‚Í‚¸‚ê\n");
		return;
	}

	m_attackList.emplace_back(leftShot);
	m_attackList.back()->Shot(_pos, _targetPos, LeftVec);

	
}
