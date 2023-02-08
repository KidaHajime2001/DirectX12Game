#pragma once
#include"EnemyBase.h"
class StraightShotEnemy:public EnemyBase
{
public:
	//�R���X�g���N�^
	StraightShotEnemy(CollisionTag _tag, bool m_alive);
	~StraightShotEnemy();
	//�X�V
	void Update(const DirectX::XMFLOAT3 _targetPos);
	void Draw()override;
	
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
	enum SEState
	{
		Attack,
		SpecialAT,
	};
	SEState seState;
	enum SpecialState
	{
		Aiming,
		CircleMove,
	};
	SpecialState m_specialState;
	const DirectX::XMFLOAT3 TARGET_SPACE = XMFLOAT3(1,0,0);
	float m_specialrotate=0.0f;

};