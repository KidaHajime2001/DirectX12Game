#pragma once
#include<DirectXMath.h>
class PlayerShotDirector
{
public:
	PlayerShotDirector();
	~PlayerShotDirector();
	void Update(const bool& _isShot,const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT3& _direction,const float& _speed);
	void Draw();
private:
	//ÉvÉåÉCÉÑÅ[
	class BulletPool* m_bulletPool;
};
