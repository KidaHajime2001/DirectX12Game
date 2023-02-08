#include"PowerUpItem.h"
#include"PmdModel.h"
#include"XMF3Math.h"
PowerUpItem::PowerUpItem(CollisionTag _tag, ItemTag _ItemTag)
	:ItemBase(_tag, _ItemTag)
{
	m_modeltype_Core = PMDModelType::PowerUpItemCore;
	m_modeltype_Shell= PMDModelType::PowerUpItemShell;
	test = 0;
}

PowerUpItem::~PowerUpItem()
{
}

void PowerUpItem::Draw()
{
	m_model.Draw(
		XMF3Math::AddXMFLOAT3(GetPosition(),XMFLOAT3(0,sin(test++/10)*0.5f,0)),
		XMFLOAT3(
			XMF3Math::DegreeForRadian(0)
			, XMF3Math::DegreeForRadian(90)
			, XMF3Math::DegreeForRadian(0)),
		m_modeltype_Core);
	m_model.Draw(
		XMF3Math::AddXMFLOAT3(GetPosition(), XMFLOAT3(0, sin(test++ / 10) * 0.3f, 0)),
		XMFLOAT3(
			XMF3Math::DegreeForRadian(0)
			, XMF3Math::DegreeForRadian(90)
			, XMF3Math::DegreeForRadian(0)),
		m_modeltype_Shell);
}
