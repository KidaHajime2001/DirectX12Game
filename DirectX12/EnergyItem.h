#pragma once
#include"ItemBase.h"
class EnergyItem:public ItemBase
{
public:
	EnergyItem(CollisionTag _tag, ItemTag _ItemTag);
	~EnergyItem();
	void Draw()override;
	
private:

};
