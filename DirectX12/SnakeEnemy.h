#pragma once
#include"EnemyBase.h"
class SnakeEnemy :public EnemyBase
{
public:
	//�R���X�g���N�^
	SnakeEnemy(CollisionTag _tag, bool m_alive);
	~SnakeEnemy();
	void Init()override;
	//�X�V
	void Update(const DirectX::XMFLOAT3 _targetPos);
	void Draw()override;
	void SetTailPosition();
	void SetTailDirection();
private:
	/// <summary>
   /// �Ȉ�AI�̑ҋ@�s��
   /// </summary>
   /// <param name="_targetPos">
   /// �^�[�Q�b�g�i�v���C���[�j�̈ʒu
   /// </param>
	void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);
	/// <summary>
   /// �Ȉ�AI�̍U���s��
   /// </summary>
   /// <param name="_targetPos">
   /// �^�[�Q�b�g�i�v���C���[�j�̈ʒu
   /// </param>
	void AttackUpdate(const DirectX::XMFLOAT3 _targetPos);
	/// <summary>
   /// �Ȉ�AI�̈ړ��s��
   /// </summary>
   /// <param name="_targetPos">
   /// �^�[�Q�b�g�i�v���C���[�j�̈ʒu
   /// </param>
	void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);
	/// <summary>
   /// �ŗL�̓����A
   /// </summary>
   /// <param name="otherCollision">
   ///�@�ڐG�����������蔻����
   /// </param>
	void CollisionOriginal(class Collision* otherCollision);
	//�e�����N���X
	class EnemyShotDirector* m_enemyShotDirector;

	//���Ԃ�}��N���X
	class Time* m_timer;
	//�V���b�g��
	int m_shotNum;
	//�U���񐔂̍ő�l
	const int ATTACK_NUM_MAX = 3;

	std::vector<class SnakeTail*> m_snakeTails;
	std::vector<XMFLOAT3> m_tailsPosition;
	std::vector<XMFLOAT3> m_beforeTailsPosition;

	std::vector<XMFLOAT3> m_tailsDirection;
	std::vector<XMFLOAT3> m_beforeTailsDirection;
	DirectX::XMFLOAT3 m_acceleration;
	DirectX::XMFLOAT3 m_velocity;

	const int TAIL_NUMBER=10;
	const int CHASE_TIME = 10;
	int m_chaseFlame=0;
};