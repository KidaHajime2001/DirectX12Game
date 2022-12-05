#pragma once
#include"EnemyAttackBase.h"
class StraightAttack:public EnemyAttackBase 
{
public:
	StraightAttack(const EnemyAttackType _type, const CollisionTag _tag);
	~StraightAttack();
	//�X�V
	void Update(DirectX::XMFLOAT3 _targetPos);
	
	/// <summary>
	/// �e�̔���
	/// </summary>
	/// <param name="_pos">�ł��o���|�W�V����</param>
	/// <param name="_targetPos">�_���|�W�V����</param>
	/// <param name="_aimVec">�e�̕���</param>
	void Shot(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));
	//�����蔻��
	void OnCollisionEnter(class Collision* otherCollision)override;
	//�`��
	void Draw();

private:

	//�ʒu
	DirectX::XMFLOAT3 m_position;

	//����
	class Time* m_timer;

	//  PMD���f���̊Ǘ�
	class PMDModel& m_model;

	//�ړ��x�N�g��
	DirectX::XMFLOAT3 m_direction;

	//���x
	float m_speed;
	
};