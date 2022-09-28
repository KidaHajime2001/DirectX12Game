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

	//初期化
	virtual void Init();
	//位置セット
	void SetPotision(XMFLOAT3 _pos) { m_param.pos = _pos; };
	
	//位置ゲット
	const XMFLOAT3 GetPosition() { return m_param.pos; };
	
	//当たり判定タグ
	const CollisionTag GetTag() { return m_param.collisionTag; };
	//当たり判定処理
	virtual void OnCollisionEnter(class Collision* otherCollision);

	class Collision* GetCollision() { return m_param.mCollision; };
protected:
	//  プレイヤーのパラメータ
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


