#pragma once
#include"CollisionTag.h"
#include"Actor.h"
#include<vector>
//こいつのポインターをメンバーにする
class Collision
{
public:

	//縦と横の幅
	struct CollisionData
	{
		XMFLOAT3 pos;
		float radius;
	};

	Collision(class Actor* parent, float radius);
	~Collision();
	bool Cheak(class Collision* otherObj);
	void Update();
	CollisionTag GetTag() { return mTag; };
	Actor* GetParent() { return mParent; };
	CollisionTag mTag;
	CollisionData mData;
	Actor* mParent;
};
