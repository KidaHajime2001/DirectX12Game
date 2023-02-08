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
	//���f��
	class PMDModel& m_model;            //  PMD���f���̊Ǘ�
	PMDModelType m_modeltype_Core;			//�@PMD���f���̃^�C�v
	PMDModelType m_modeltype_Shell;			//�@PMD���f���̃^�C�v
	ItemTag m_itemTag;
	bool m_isAlive;
	//�����蔻��̉��u��
	float m_radiusData=3;
};