#include "Collision.h"
Collision::Collision(Actor* parent, const float _radius, const bool _isValidity)
	:m_parent(parent)
{
	m_data.radius = _radius;
	m_data.pos = parent->GetPosition();
	m_tag = m_parent->GetTag();
	m_isValidity = _isValidity;
}

Collision::~Collision()
{
}

bool Collision::Cheak(Collision* otherObj)
{
	if (!otherObj->IsValidity() || !IsValidity())
	{
		return false;
	}
	CollisionData otherData = otherObj->m_data;


	XMFLOAT3 subVector;
	subVector.x= otherData.pos.x - this->m_data.pos.x;
	subVector.y = otherData.pos.y - this->m_data.pos.y;
	subVector.z = otherData.pos.z - this->m_data.pos.z;

	sqrtf(subVector.x* subVector.x+ subVector.y* subVector.y+ subVector.z* subVector.z);

	if (otherData.radius + this->m_data.radius > sqrtf(subVector.x * subVector.x + subVector.y * subVector.y + subVector.z * subVector.z))
	{
		return true;
	}


	return false;
}

void Collision::Update()
{
	m_data.pos = m_parent->GetPosition();
}
