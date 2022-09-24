#pragma once
#include"Actor.h"
class Ground:public Actor
{
public:
	Ground(CollisionTag _tag, bool Alive);
	~Ground();
	void Update()override;
	void Draw()override;
private:
	class PMDModel& m_model;            //  PMDモデルの管理
	XMFLOAT3 m_secondGround;
	XMFLOAT3 m_thirdGround;
};
