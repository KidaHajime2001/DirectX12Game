#include "Collision.h"
Collision::Collision(Actor* parent, float radius)
	:mParent(parent)
{
	mData.radius = radius;
	mData.pos = parent->GetPosition();
	mTag = mParent->GetTag();
}

Collision::~Collision()
{
}

bool Collision::Cheak(Collision* otherObj)
{
	if (!otherObj->GetParent()->GetAlive()||!GetParent()->GetAlive())
	{
		return false;
	}
	CollisionData otherData = otherObj->mData;


	XMFLOAT3 subVector;
	subVector.x= otherData.pos.x - this->mData.pos.x;
	subVector.y = otherData.pos.y - this->mData.pos.y;
	subVector.z = otherData.pos.z - this->mData.pos.z;

	sqrtf(subVector.x* subVector.x+ subVector.y* subVector.y+ subVector.z* subVector.z);

	if (otherData.radius + this->mData.radius > sqrtf(subVector.x * subVector.x + subVector.y * subVector.y + subVector.z * subVector.z))
	{
		return true;
	}


	return false;
}

void Collision::Update()
{
	mData.pos = mParent->GetPosition();
}
