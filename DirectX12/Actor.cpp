#include "Actor.h"

Actor::Actor(CollisionTag _tag, bool Alive)
	:m_effect(Singleton<EffekseerManager>::GetInstance())
{
	m_param.pos= XMFLOAT3(0,0,0);
	m_param.collisionTag=_tag;
	m_param.IsAlive = Alive;
}

Actor::~Actor()
{
}

void Actor::Init()
{
}

void Actor::Update()
{
}

void Actor::Draw()
{
}

void Actor::OnCollisionEnter(Collision* otherCollision)
{
}
