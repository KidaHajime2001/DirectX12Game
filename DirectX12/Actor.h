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

	//初期化
	virtual void Init();
	//更新
	virtual void Update();
	//描画
	virtual void Draw();
	//位置セット
	void SetPotision(XMFLOAT3 _pos) { m_param.pos = _pos; };
	
	//位置ゲット
	const XMFLOAT3 GetPosition() { return m_param.pos; };
	
	//当たり判定タグ
	const CollisionTag GetTag() { return m_param.collisionTag; };
	//当たり判定処理
	virtual void OnCollisionEnter(class Collision* otherCollision);

	class Collision* GetCollision() { return m_param.mCollision; };

	//生きているかのフラグゲット
	const bool GetAlive() { return m_param.IsAlive; };
	//生きているかのフラグセット
	void SetAlive(bool _isAlive) { m_param.IsAlive = _isAlive; };
protected:
	//  プレイヤーのパラメータ
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


