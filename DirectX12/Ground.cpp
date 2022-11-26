#include "Ground.h"
#include"Singleton.h"
#include"PmdModel.h"
#include"ModelTypeData.h"
#include"XMF3Math.h"
Ground::Ground(CollisionTag _tag)
	:m_model(Singleton<PMDModel>::GetInstance())
	, Actor(_tag)
	,m_secondGround(0,0,0)
	, m_thirdGround(0, 0, 1100)
	,m_rotateRate(0.0f)
	,m_rotate(XMFLOAT3(90.0f,0.0f,0.0f))
	,x(0)
	,y(0)
	,z(0)
{
	m_param.pos = XMFLOAT3(0,-3,0);
}

Ground::~Ground()
{
}

void Ground::Update()
{
}

void Ground::Draw()
{
	/*
	m_model.Draw(XMFLOAT3(x, y, z), 0, PMDModelType::GroundCube);*/
	m_model.Draw(GetPosition(), 0, PMDModelType::Ground);
	/*m_model.Draw(GetPosition(), 0, PMDModelType::Ground);*/
}

void Ground::DrawBackCircle()
{
	if (m_rotateRate>=360)
	{
		m_rotateRate = 0;
	}
	m_rotateRate += 0.1f;
	if (m_secondGround.z <= -1100)
	{
		m_secondGround = XMFLOAT3(0,0,1100);
	}
	else if(m_thirdGround.z <= -1100)
	{
		m_thirdGround = XMFLOAT3(0, 0, 1100);
	}
	m_secondGround = XMF3Math::AddXMFLOAT3(m_secondGround, XMFLOAT3(0, 0, -5));
	m_thirdGround = XMF3Math::AddXMFLOAT3(m_thirdGround, XMFLOAT3(0, 0, -5));

	m_rotate.x = 30.0f;

	m_model.Draw(m_secondGround, m_rotate, PMDModelType::BackGround);
	m_model.Draw(m_thirdGround, 0, PMDModelType::BackGround);
}

void Ground::SetGround(XMFLOAT3 _set)
{
	x = _set.x;
	y = _set.y;
	z = _set.z;
}

