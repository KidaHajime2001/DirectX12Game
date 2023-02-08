#include "ItemBase.h"
#include "PMDModel.h"
#include"Collision.h"

ItemBase::ItemBase(CollisionTag _tag, ItemTag _ItemTag)
	:Actor(_tag)
	,m_itemTag(_ItemTag)
	, m_model(Singleton<PMDModel>::GetInstance())
{
	m_param.mCollision->m_data.radius = m_radiusData;
	m_param.pos = XMFLOAT3(0, 0, 0);
	m_param.mCollision->m_isValidity = false;
	m_isAlive = false;

}

ItemBase::~ItemBase()
{
}

void ItemBase::Init(DirectX::XMFLOAT3 _dropPosition)
{
	m_param.pos = _dropPosition;
	m_isAlive = true;

	m_param.mCollision->m_isValidity = true;


}

void ItemBase::Draw()
{
}

void ItemBase::OnCollisionEnter(Collision* otherCollision)
{
	//‘¼“–‚½‚è”»’è‚Ìƒ^ƒO‚ªEnemy‚¾‚Á‚½ê‡
	if (otherCollision->GetTag() == CollisionTag::Player)
	{

		m_param.mCollision->m_isValidity = false;
		m_isAlive = false;	
	}
}

