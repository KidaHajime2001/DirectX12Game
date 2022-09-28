#include "Ground.h"
#include"Singleton.h"
#include"PmdModel.h"
#include"ModelTypeData.h"
Ground::Ground(CollisionTag _tag)
	:m_model(Singleton<PMDModel>::GetInstance())
	, Actor(_tag)
	, m_secondGround(0, 0, 300)
	, m_thirdGround(0,0,150)
{
}

Ground::~Ground()
{
}

void Ground::Update()
{
}

void Ground::Draw()
{
	m_model.Draw(GetPosition(), 0, PMDModelType::Ground);
}
