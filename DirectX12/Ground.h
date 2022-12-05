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
	void SetGround(XMFLOAT3 _set);
	const XMFLOAT3 GetSecondPosition() { return m_secondGround; };
private:
	class PMDModel& m_model;            //  PMDÉÇÉfÉãÇÃä«óù
	XMFLOAT3 m_secondGround;
	XMFLOAT3 m_thirdGround;
	XMFLOAT3 m_rotateRing1;
	XMFLOAT3 m_rotateRing2;
	XMFLOAT3 m_rotateRing3;
	float m_rotateRate;
	float x, y,z;
};
