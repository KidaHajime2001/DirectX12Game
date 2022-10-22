#pragma once
#include "EnemyBase.h"
class SpreadShotEnemy :
    public EnemyBase
{
public:
	SpreadShotEnemy(CollisionTag _tag, bool m_alive);
	~SpreadShotEnemy();

	void Update(const DirectX::XMFLOAT3 _targetPos);
	void ShotDraw();
	//�����蔻�菈��
	void OnCollisionEnter(class Collision* otherCollision)override;
private:
	void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);
	void AttackUpdate(const DirectX::XMFLOAT3 _targetPos);
	void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);

	//�e��łN���X
	class EnemyShotDirector* m_enemyShotDirector;

	//���Ԃ�}��N���X
	class Time* m_timer;
	int m_shotNum;
	const int ATTACK_NUM_MAX = 5;
};

