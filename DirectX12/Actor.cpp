#include "Actor.h"
#include"CollisionManager.h"
#include"Collision.h"
Actor::Actor(CollisionTag _tag)
	:m_effect(Singleton<EffekseerManager>::GetInstance())
{
	m_param.pos= XMFLOAT3(0,0,0);
	m_param.collisionTag=_tag;
	CollisionManager& m_collisionManager = Singleton<CollisionManager>::GetInstance();
	m_param.mCollision = new Collision(this);
	m_collisionManager.AddCollision(this->m_param.mCollision);
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
