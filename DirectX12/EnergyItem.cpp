#include "EnergyItem.h"
#include"PmdModel.h"
EnergyItem::EnergyItem(CollisionTag _tag, ItemTag _ItemTag)
	:ItemBase(_tag,_ItemTag)
{
	m_modeltype_Core = PMDModelType::EnergyItem;
}

EnergyItem::~EnergyItem()
{
}

void EnergyItem::Draw()
{
	m_model.Draw(
		GetPosition(),
		0,
		m_modeltype_Core);
}
