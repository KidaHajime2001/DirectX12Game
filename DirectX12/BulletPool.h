#pragma once
#include<vector>
//’e‚ğ‚¢‚¿‚¢‚¿¶¬‚µ‚È‚¢‚æ‚¤ì‚è’u‚«‚µ‚½‚à‚Ì‚ğÄ—˜—p‚·‚é
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
