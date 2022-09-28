#pragma once
#include <DirectXTex.h>
#include"ActorTag.h"
#include"CollisionTag.h"

#include"Singleton.h"
#include"EffekseerMng.h"
#include "EffectType.h"
using namespace DirectX;
class Actor
{
public:
	Actor(CollisionTag _tag);
	virtual ~Actor();

	//������
	virtual void Init();
	//�ʒu�Z�b�g
	void SetPotision(XMFLOAT3 _pos) { m_param.pos = _pos; };
	
	//�ʒu�Q�b�g
	const XMFLOAT3 GetPosition() { return m_param.pos; };
	
	//�����蔻��^�O
	const CollisionTag GetTag() { return m_param.collisionTag; };
	//�����蔻�菈��
	virtual void OnCollisionEnter(class Collision* otherCollision);

	class Collision* GetCollision() { return m_param.mCollision; };
protected:
	//  �v���C���[�̃p�����[�^
	struct Param
	{
		XMFLOAT3 pos;
		class Collision* mCollision;
		CollisionTag collisionTag;
	};
	Param m_param;
	bool exists;

	class EffekseerManager& m_effect;
};


