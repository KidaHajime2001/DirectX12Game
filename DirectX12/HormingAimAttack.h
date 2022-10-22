#pragma once
#include"EnemyAttackBase.h"
class HormingAimAttack:public EnemyAttackBase
{
public:
	HormingAimAttack(const EnemyAttackType _type, const CollisionTag _tag);
	~HormingAimAttack();
	void Update(DirectX::XMFLOAT3 _targetPos);
	void Shot(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));
	
	void Draw();
private:
	void Move();
	DirectX::XMFLOAT3 m_position;
	class Time* m_timer;

	class PMDModel& m_model;            //  PMDÉÇÉfÉãÇÃä«óù
	DirectX::XMFLOAT3 m_acceleration;
	DirectX::XMFLOAT3 m_velocity;
	//å¸Ç´
	DirectX::XMFLOAT3 m_aimvec;
	float m_direction;

	

};
