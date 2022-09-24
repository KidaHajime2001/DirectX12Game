#pragma once
class ShootDirector
{
public:
	ShootDirector();
	~ShootDirector();
	void Update( class Player* _player);
	void Draw();
private:

	class BulletPool* m_bulletPool;
};
