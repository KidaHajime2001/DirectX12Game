#pragma once
#include<DirectXMath.h>
#include"Actor.h"
#include"EnemyAttackType.h"
class EnemyAttackBase:public Actor
{
public:
	
	EnemyAttackBase(const EnemyAttackType _type,const CollisionTag _tag);
	~EnemyAttackBase();


	 void Init();

	 //�h�����update���p��
	 virtual void Update(const DirectX::XMFLOAT3 _targetPos);
	 /// <summary>
	 /// �e�����N���X
	 /// </summary>
	 /// <param name="_position">���ˈʒu</param>
	 /// <param name="_targetPos">�ڕW�ʒu</param>
	 /// <param name="_aimVec">�������������x�N�g��</param>
	 virtual void Shot(const DirectX::XMFLOAT3 _position,const DirectX::XMFLOAT3 _targetPos,  const DirectX::XMFLOAT3 _aimVec);
	 //�`��
	 virtual void Draw();
	 //�������Ă��邩
	 const bool IsAlive() { return m_isAlive; };

protected:
	//�e�̎��
	EnemyAttackType m_enemyType;

	//�e���������Ă��邩�H
	bool m_isAlive;

	//�O��file�����݂���
	float m_attackCollisionRadius=1;
};