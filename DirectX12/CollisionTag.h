#pragma once
#include <string>
#include <stdexcept>
#include <iterator>
enum class CollisionTag
{

	Player=0,
	BackGround,
	Enemy,
	EnergyItem,
	Shield,
	ReinforceShotInterval,
	ReinforceAddtoShot,
	PlayerBullet,
	EnemyBullet,
	End,
};
