#pragma once
#include"EnemyAttackBase.h"
class StraightAttack:public EnemyAttackBase 
{
public:
	StraightAttack(const EnemyAttackType _type, const CollisionTag _tag);
	~StraightAttack();
	void Update(DirectX::XMFLOAT3 _targetPos);
	void Shot(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));

	void OnCollisionEnter(class Collision* otherCollision)override;
	void Draw();

private:
	//ïKê{
	DirectX::XMFLOAT3 m_position;
	class Time* m_timer;
	class PMDModel& m_model;            //  PMDÉÇÉfÉãÇÃä«óù
	DirectX::XMFLOAT3 m_direction;
	float m_speed;
	
};