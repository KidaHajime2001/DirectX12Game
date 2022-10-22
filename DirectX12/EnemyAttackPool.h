#pragma once
#include <iostream>
#include <vector>
#include <DirectXMath.h>
enum class EnemyAttackType;
//�V���O���g���N���X
class EnemyAttackPool
{
public:
	EnemyAttackPool();
	~EnemyAttackPool();
	void Update(const DirectX::XMFLOAT3 _targetPos);
	void Draw();
	class EnemyAttackBase* GetUnUsedEnemyAttack(const EnemyAttackType _type);

	void CreateAll();
	void DestroyAll();
private:
	void UpdateEnemyAttack(const EnemyAttackType _type,const DirectX::XMFLOAT3 _targetPos);
	void DrawEnemyAttack(const EnemyAttackType _type);

	void CreateAttackObj(const EnemyAttackType _type);
	std::vector<class EnemyAttackBase*> m_StraightPool;
	std::vector<class EnemyAttackBase*> m_HormingPool;
};

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    