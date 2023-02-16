#pragma once
#include<DirectXMath.h>
#include "EnemyAttackType.h"
#include<iostream>
#include<list>
//�G�l�~�[�̍U���N���X
class EnemyShotDirector
{
public:

	EnemyShotDirector();
	~EnemyShotDirector();
	/// <summary>
	/// �G�l�~�[�N���X�̍U��
	/// </summary>
	/// <param name="_type">�U���̃^�C�v</param>
	/// <param name="_pos">�U���ʒu</param>
	/// <param name="_targetPos">�U���̑_����</param>
	/// <param name="_aimVec">
	/// �����x�N�g��
	/// �i�w������邱�ƂōU���̎��R�x���グ��ړI������F�����đ_�����͂����Ȃǁj
	/// </param>
	void Shot(const EnemyAttackType _type, const DirectX::XMFLOAT3 _pos,const DirectX::XMFLOAT3 _targetPos,DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0,0,0));

private:

	/// <summary>
	/// �z�[�~���O�e������
	/// </summary>
	/// <param name="_pos">���ˈʒu</param>
	/// <param name="_targetPos">�_���G</param>
	/// <param name="_aimVec">�����x�N�g��</param>
	void HormingShot( const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));
	/// <summary>
	/// �܂������e������
	/// </summary>
	/// <param name="_pos">���ˈʒu</param>
	/// <param name="_targetPos">�_���G</param>
	/// <param name="_aimVec">�����x�N�g��</param>
	void StraightShot(const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));

	/// <summary>
	/// ���������ɂ܂������Ȓe������
	/// </summary>
	/// <param name="_pos">���ˈʒu</param>
	/// <param name="_targetPos">�_���G</param>
	/// <param name="_aimVec">�����x�N�g��</param>
	void SpreadShot(const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));

	/// <summary>
	/// �����Ă���U���N���X���܂Ƃ߂郊�X�g
	/// </summary>
	std::list<class EnemyAttackBase*> m_attackList;

	/// <summary>
	/// �����Ȃǂō폜����U���N���X���܂Ƃ߂郊�X�g
	/// </summary>
	std::list<class EnemyAttackBase*> m_deleteList;

	/// <summary>
	/// �G�l�~�[�̍U���v�[��
	/// </summary>
	class EnemyAttackPool& m_enemyAttackPool;

	/// <summary>
	/// �g�U�e�̐�
	/// </summary>
	const int SPREAD_SHOT_NUM=3;

};

