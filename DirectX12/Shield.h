#pragma once
#include"Actor.h"
class Shield : public Actor
{
public:
	Shield(CollisionTag _tag);
	~Shield();
	void OnCollisionEnter(Collision* otherCollision);
	void Update(DirectX::XMFLOAT3 _pos);
	void Draw();
private:
	//コントローラー
	class Controller& m_controller;
	//モデル
	class PMDModel& m_model;


	bool m_shieldFlag = false;
	DirectX::XMFLOAT3 m_shieldRotate;
	float m_shieldRadian = 0;
	int m_shieldSpace = 15;
};
