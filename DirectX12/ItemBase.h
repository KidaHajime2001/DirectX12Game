#pragma once
#include"Actor.h"
#include "ModelTypeData.h"
#include"ItemTag.h"
class ItemBase: public Actor
{
public:
	ItemBase(CollisionTag _tag,ItemTag _ItemTag);
	virtual ~ItemBase();
	void Init(DirectX::XMFLOAT3 _dropPosition);
	void Update();
	virtual void Draw();
	void OnCollisionEnter(class Collision* otherCollision);
	const bool IsAlive() { return m_isAlive; };
	const ItemTag GetItemTag() { return m_itemTag; };
	void OverAlive() { m_isAlive = false; };

protected:
	//モデル
	class PMDModel& m_model;            //  PMDモデルの管理
	PMDModelType m_modeltype_Core;			//　PMDモデルのタイプ
	PMDModelType m_modeltype_Shell;			//　PMDモデルのタイプ
	ItemTag m_itemTag;
	bool m_isAlive;
	//当たり判定の仮置き
	float m_radiusData=3;
};