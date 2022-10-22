#pragma once
#include"EnemyBase.h"
class StraightShotEnemy:public EnemyBase
{
public:
	StraightShotEnemy(CollisionTag _tag, bool m_alive);
	~StraightShotEnemy();
	void Update(const DirectX::XMFLOAT3 _targetPos);
	void CollisionOriginal(class Collision* otherCollision);
	void ShotDraw();
private:
	void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);
	void AttackUpdate(const DirectX::XMFLOAT3 _targetPos);
	void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);

	//弾を打つクラス
	class EnemyShotDirector* m_enemyShotDirector;

	//時間を図るクラス
	class Time* m_timer;
	int m_shotNum;
	const int ATTACK_NUM_MAX = 5;

};