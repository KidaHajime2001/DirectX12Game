#pragma once
#include"Actor.h"
class Ground:public Actor
{
public:
	Ground(CollisionTag _tag);
	~Ground();
	void Update();
	void Draw();
	void DrawBackCircle();
	const XMFLOAT3 GetSecondPosition() { return m_secondGround; };
private:
	class PMDModel& m_model;            //  PMDÉÇÉfÉãÇÃä«óù
	XMFLOAT3 m_secondGround;
	XMFLOAT3 m_thirdGround;
	float m_rotateRate;
};
