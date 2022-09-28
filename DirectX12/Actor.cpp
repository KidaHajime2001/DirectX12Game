#include "Actor.h"

Actor::Actor(CollisionTag _tag)
	:m_effect(Singleton<EffekseerManager>::GetInstance())
{
	m_param.pos= XMFLOAT3(0,0,0);
	m_param.collisionTag=_tag;
}

Actor::~Actor()
{
}

void Actor::Init()
{
}


void Actor::OnCollisionEnter(Collision* otherCollision)
{
}
