#pragma once
#include"Actor.h"
#include<time.h>
class Bullet : public Actor
{
public:
	Bullet(CollisionTag _tag, bool Alive);
	~Bullet();
	void Init()override;
	void Update()override;
	void Draw()override; 
	void OnCollisionEnter(class Collision* otherCollision)override;
	void SetDirection(XMFLOAT3 _newDirection) { m_directionVector = _newDirection; };
	void Shot(const XMFLOAT3& _setPosition,const XMFLOAT3& _newDirection,const float& _shotspeed);
private:
	//ÉÇÉfÉã

	class PMDModel& m_model;            //  PMDÉÇÉfÉãÇÃä«óù
	const int RADIUS_NUM = 1;
	XMFLOAT3 m_directionVector = { 0,0,0 };
	clock_t AliveTimeStart;
	const int ALIVE_TIME_MAX=1;
 float m_speed;
};
