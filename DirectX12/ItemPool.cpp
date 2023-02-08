#include"ItemPool.h"
#include"EnergyItem.h"
#include"PowerUpItem.h"
ItemPool::ItemPool()
{
}

ItemPool::~ItemPool()
{
}

void ItemPool::Create()
{
	//ItemÇÃê∂ê¨
	for (int i = 0; i<INITIAL_ENERGY_ITEM;i++)
	{
		m_itemPools[ItemTag::Energy].push_back(new EnergyItem(CollisionTag::EnergyItem, ItemTag::Energy));
	}
	//ItemÇÃê∂ê¨
	for (int i = 0; i < INITIAL_REINFORCE_ITEM; i++)
	{
		m_itemPools[ItemTag::ReinforceShotInterval].push_back(new PowerUpItem(CollisionTag::ReinforceShotInterval,ItemTag::ReinforceShotInterval));
	}
	for (int i = 0; i < INITIAL_REINFORCE_ITEM; i++)
	{
		m_itemPools[ItemTag::ReinforceAddtoShot].push_back(new PowerUpItem(CollisionTag::ReinforceAddtoShot, ItemTag::ReinforceAddtoShot));
	}
}

void ItemPool::Destroy()
{
	for (auto itr : m_itemPools[ItemTag::Energy])
	{
		if (itr)
		{
			delete itr;
		}
	}
	m_itemPools[ItemTag::Energy].clear();
	m_itemPools[ItemTag::Energy].shrink_to_fit();
	for (auto itr : m_itemPools[ItemTag::ReinforceShotInterval])
	{
		if (itr)
		{
			delete itr;
		}
	}
	m_itemPools[ItemTag::ReinforceShotInterval].clear();
	m_itemPools[ItemTag::ReinforceShotInterval].shrink_to_fit();
	for (auto itr : m_itemPools[ItemTag::ReinforceAddtoShot])
	{
		if (itr)
		{
			delete itr;
		}
	}
	m_itemPools[ItemTag::ReinforceAddtoShot].clear();
	m_itemPools[ItemTag::ReinforceAddtoShot].shrink_to_fit();
}

ItemBase* ItemPool::GetUnUsedItem(const ItemTag _tag)
{
	for (auto itr : m_itemPools[_tag])
	{
		if (!itr->IsAlive())
		{
			return itr;
		}
	}
	return nullptr;
}
