#pragma once
#include<DirectXMath.h>
#include"Actor.h"
enum class EnemyType;
class EnemyAttackBase:public Actor
{
public:
	EnemyAttackBase();
	virtual ~EnemyAttackBase();

	//îhê∂êÊÇÕupdateÇåpè≥
	virtual void Update(const DirectX::XMFLOAT3 _targetPos)=0;
	virtual void Shot(const DirectX::XMFLOAT3 _position,const DirectX::XMFLOAT3 _aimVec)=0;
	//ï`âÊ
	void Draw();

private:

};