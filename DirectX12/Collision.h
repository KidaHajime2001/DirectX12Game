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

	Collision(class Actor* _parent, const float _radius,const bool _isValidity = true);
	~Collision();
	bool Cheak( class Collision* _otherObj);
	void Update();
	const CollisionTag GetTag() { return m_tag; };
	Actor* GetParent() { return m_parent; };
	const bool IsValidity() { return m_isValidity; };
private:
	CollisionTag m_tag;
	CollisionData m_data;
	Actor* m_parent;
	bool m_isValidity;
};
