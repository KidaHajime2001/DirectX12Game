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

	Collision(class Actor* _parent,const bool& _isValidity = true);
	~Collision();
	const bool Cheak( class Collision* _otherObj);
	void Update();
	const CollisionTag GetTag() { return m_tag; };
	const bool IsValidity() { return m_isValidity; };
	const DirectX::XMFLOAT3 GetPosition() { return m_data.pos; };
	const float GetRadius() { return m_data.radius;};

	
	 
	 void Hit(Collision* otherCollision);
	 bool m_isValidity;
	 CollisionData m_data;
private:
	 Actor* GetParent() { return m_parent; };
	CollisionTag m_tag;
	Actor* m_parent;
	DirectX::XMFLOAT3 m_parentPos;
};
