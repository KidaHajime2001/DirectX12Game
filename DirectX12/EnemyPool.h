#pragma once

#include<vector>
#include<unordered_map>
enum class EnemyType;
class EnemyPool
{
public:
	EnemyPool();
	~EnemyPool();
	
	class EnemyBase* UnUsedEnemyAdvent(const EnemyType _type);
	void AddCollision( class CollisionManager* _mng);
	void DeleteCollision(class CollisionManager* _mng);

	void CreateAll();
	void DestroyAll();
private:
	void Create(const EnemyType _type);
	std::unordered_map<EnemyType,std::vector<EnemyBase*>> m_enemyPool;
	int m_enemyTypeSize=0;
	const int ADVENT_MAX = 10;
	const int LESSER_POOL_MAX = 300;
};
