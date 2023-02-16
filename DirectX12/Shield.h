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
	float GetShieldGauge() { return m_shieldGauge; };
	void Charge();
private:
	//コントローラー
	class Controller& m_controller;
	//モデル
	class PMDModel& m_model;

	class Time* m_timer;
	bool m_shieldFlag = false;
	DirectX::XMFLOAT3 m_shieldRotate;
	float m_shieldRadian = 0;
	int m_shieldSpace = 15;

	
	float m_shieldGauge=1.0f;
};
