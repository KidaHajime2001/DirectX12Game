#pragma once
#include <iostream>
#include <vector>
#include <DirectXMath.h>
#include<unordered_map>
enum class EnemyAttackType;
//�V���O���g���N���X
class EnemyAttackPool
{
public:
	EnemyAttackPool();
	~EnemyAttackPool();
	//�e�̍X�V
	void Update(const DirectX::XMFLOAT3 _targetPos);
	//�e�̕`��
	void Draw();
	/// <summary>
	/// ���g�p�̓G�U���N���X��Ԃ�
	/// </summary>
	class EnemyAttackBase* GetUnUsedEnemyAttack(const EnemyAttackType _type);

	//�e�̃I�u�W�F�N�g�v�[���쐬
	void CreateAll();
	//�I�u�W�F�N�g�v�[���폜
	void DestroyAll();
private:
	//�^�C�v�ʍX�V
	void UpdateEnemyAttack(const EnemyAttackType _type,const DirectX::XMFLOAT3 _targetPos);
	//�^�C�v�ʕ`��
	void DrawEnemyAttack(const EnemyAttackType _type);

	//�I�u�W�F�N�g�v�[��
	std::vector<class EnemyAttackBase*> m_StraightPool;
	//�I�u�W�F�N�g�v�[��
	std::vector<class EnemyAttackBase*> m_HormingPool;
	//�^�C�v�ƃI�u�W�F�N�g�v�[����R�Â����}�b�v
	std::unordered_map<EnemyAttackType, std::vector<class EnemyAttackBase*>> m_poolMap;
};

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    