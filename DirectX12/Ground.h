#pragma once
#include"Actor.h"
class Ground:public Actor
{
public:
	Ground(CollisionTag _tag);
	~Ground();
	void Update();
	void Draw();
private:
	class PMDModel& m_model;            //  PMD���f���̊Ǘ�
	XMFLOAT3 m_secondGround;
	XMFLOAT3 m_thirdGround;
};
