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
	Actor(CollisionTag _tag,bool Alive);
	virtual ~Actor();

	//������
	virtual void Init();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();
	//�ʒu�Z�b�g
	void SetPotision(XMFLOAT3 _pos) { m_param.pos = _pos; };
	
	//�ʒu�Q�b�g
	const XMFLOAT3 GetPosition() { return m_param.pos; };
	
	//�����蔻��^�O
	const CollisionTag GetTag() { return m_param.collisionTag; };
	//�����蔻�菈��
	virtual void OnCollisionEnter(class Collision* otherCollision);

	class Collision* GetCollision() { return m_param.mCollision; };

	//�����Ă��邩�̃t���O�Q�b�g
	const bool GetAlive() { return m_param.IsAlive; };
	//�����Ă��邩�̃t���O�Z�b�g
	void SetAlive(bool _isAlive) { m_param.IsAlive = _isAlive; };
protected:
	//  �v���C���[�̃p�����[�^
	struct Param
	{
		XMFLOAT3 pos;
		bool IsAlive;
		class Collision* mCollision;
		CollisionTag collisionTag;
	};
	Param m_param;
	bool exists;

	class EffekseerManager& m_effect;
};


