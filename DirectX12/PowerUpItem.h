#pragma once
#include"ItemBase.h"
class PowerUpItem:public ItemBase
{
public:
	PowerUpItem(CollisionTag _tag, ItemTag _ItemTag);
	virtual ~PowerUpItem();
	virtual void Draw();
private:
	float test;
};
