#pragma once
#include<vector>
//弾をいちいち生成しないよう作り置きしたものを再利用する
class BulletPool
{
public:
	BulletPool();
	~BulletPool();
	void CreatePool(int _size);
	void DestroyPool();
	class Bullet* GetUnUsedBullet();
	void AddCollisionManager(class CollisionManager* _mng);
	void Update();
	void Draw();
private:
	int m_poolSize;
	std::vector<Bullet*> m_bulletPool;
};
