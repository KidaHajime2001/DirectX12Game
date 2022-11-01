#pragma once
#include <DirectXMath.h>
#include <list>
enum class EnemyType;
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void Update(const DirectX::XMFLOAT3& _targetPos);
	void Draw();
private:
	void CallEnemy();
	void AddEnemy(const EnemyType& _type, const int& _num,const DirectX::XMFLOAT3& _adventPosition);
	const DirectX::XMFLOAT3 RandomPositionSelect();
	class EnemyPool& m_enemyPool;
	class EnemyAttackPool& m_enemyAttackPool;
	std::list<class EnemyBase*> m_nowAliveEnemyList;
	std::list<class EnemyBase*> m_deleteList;
	class Time* m_timer;
	float m_seriousDegree = 1.0f;
	const float DEFAULT_CALL_TIME = 10.0f;
	const float SERIOUS_COEFFICIENT = 7.0f;
	
	DirectX::XMFLOAT3 ADVENT_POSITION[4]=
	{
		DirectX::XMFLOAT3(  0,  0,-120),
		DirectX::XMFLOAT3(  0,  0, 120),
		DirectX::XMFLOAT3(-120,  0,  0),
		DirectX::XMFLOAT3( 120,  0,  0),
	};
};

