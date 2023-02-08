#pragma once
#include"Actor.h"
#include<time.h>
//�v���C���[�̒e�N���X
class Bullet : public Actor
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	Bullet(CollisionTag _tag,const bool _alive);
	~Bullet();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw(); 
	//�����蔻��
	void OnCollisionEnter(class Collision* otherCollision)override;
	//�����̃Z�b�^�[
	void SetDirection(XMFLOAT3 _newDirection) { m_directionVector = _newDirection; };
	/// <summary>
	/// �V���b�g
	/// </summary>
	/// <param name="_setPosition">�����ʒu</param>
	/// <param name="_newDirection">�e�̌���</param>
	/// <param name="_shotspeed">�e�̑��x</param>
	void Shot(const XMFLOAT3& _setPosition,const XMFLOAT3& _newDirection,const float& _shotspeed);
	/// <summary>
	/// �g�U�V���b�g
	/// </summary>
	/// <param name="_setPosition">�����ʒu</param>
	/// <param name="_newDirection">�e�̌���</param>
	/// <param name="_shotspeed">�e�̑��x</param>
	void SpreadShot(const XMFLOAT3& _setPosition, const XMFLOAT3& _newDirection, const float& _shotspeed);

	const bool IsAlive() { return m_isAlive; };
private:
	//  PMD���f���̊Ǘ�
	class PMDModel& m_model;
	//�����蔻��̑傫��
	const int RADIUS_NUM = 1;
	//�e�̐�������
	float m_aliveTime = 1;
	//
	XMFLOAT3 m_directionVector = { 0,0,0 };

	clock_t m_aliveTimeStart;
	float m_speed;
	bool m_isAlive;
};
