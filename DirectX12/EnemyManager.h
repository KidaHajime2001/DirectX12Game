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
	void Advent90s();
	void Advent60s();
	void Advent30s();
	//EnemyÇÃåÇîjêîÇXMFLOAT2Ç…Ç‹Ç∆ÇﬂÇÈÅiLESSER,HIGHERÅj
	const DirectX::XMFLOAT2 GetEnemyDefeatScore() { return DirectX::XMFLOAT2(m_lesserNumScore, m_higherNumScore); };
	void SetGameLevel(int _level);
private:
	void AddScore(const EnemyType _enemyType);
	void CallEnemy();
	void AddEnemy(const EnemyType& _type, const int& _num,const DirectX::XMFLOAT3& _adventPosition);
	class EnemyPool& m_enemyPool;
	class EnemyAttackPool& m_enemyAttackPool;
	std::list<class EnemyBase*> m_nowAliveEnemyList;
	std::list<class EnemyBase*> m_deleteList;
	class Time* m_timer;
	float m_seriousDegree = 1.0f;
	const float DEFAULT_CALL_TIME = 10.0f;
	const float SERIOUS_COEFFICIENT = 4.0f;

	DirectX::XMFLOAT3 ADVENT_POSITION[4]=
	{
		DirectX::XMFLOAT3(  0,  0,-120),
		DirectX::XMFLOAT3(  0,  0, 120),
		DirectX::XMFLOAT3(-120,  0,  0),
		DirectX::XMFLOAT3( 120,  0,  0),
	};
	DirectX::XMFLOAT3 ADVENT_EVENT_POSITION[4] =
	{
		DirectX::XMFLOAT3(100,  0,100),
		DirectX::XMFLOAT3(100,  0, -100),
		DirectX::XMFLOAT3(-100,  0, 100),
		DirectX::XMFLOAT3(-100,  0,  -100),
	};
	
	
	int m_lesserNumScore=0;
	int m_higherNumScore=0;


};

