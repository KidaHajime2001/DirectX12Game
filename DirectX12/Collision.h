#pragma once
#include"CollisionTag.h"
#include"Actor.h"
#include<vector>
//�����̃|�C���^�[�������o�[�ɂ���
class Collision
{
public:

	//�c�Ɖ��̕�
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
