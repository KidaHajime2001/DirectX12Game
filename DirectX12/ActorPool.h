#pragma once
#include"Actor.h"
#include<vector>
#include"ActorTag.h"
#include <unordered_map>
class Pool
{
public:
	//コンストラクタ
	Pool();
	//デストラクタ
	~Pool();
	//_size分　生成
	void Create(int _size, ActorTag _actorTag);
	//
	void AddCollisionManager(class CollisionManager* _mng);
	//削除
	void Destroy();
	//全エネミー更新
	void Update();
	//全エネミー描画
	void Draw();
	//使われていないエネミーを返す
	Actor* GetUnUsedActor();
	//今使われているエネミーカウント
	int NowAliveCount();
private:
	//エネミー数
	int m_PoolSize;
	struct PoolState
	{
		int poolSize = 0;
		std::vector<Actor*> pool;
	};

	//Vectorをまとめたい
	std::vector<PoolState> m_poolVec;
	//エネミープール
	PoolState m_enemypool;
};

