#pragma once
#include<vector>
#include <unordered_map>
#include"ItemTag.h"
class ItemBase;
class ItemPool
{
public:
	ItemPool();
	~ItemPool();
	void Create();
	void Destroy();
	ItemBase* GetUnUsedItem(const ItemTag _tag);
private:
	std::unordered_map<ItemTag, std::vector<ItemBase*>> m_itemPools;
	const int INITIAL_ENERGY_ITEM = 100;//EnergyItemÇÃê∂ê¨êî
	const int INITIAL_REINFORCE_ITEM = 20;
};
