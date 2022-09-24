#pragma once
#include<vector>
//�e�����������������Ȃ��悤���u���������̂��ė��p����
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
