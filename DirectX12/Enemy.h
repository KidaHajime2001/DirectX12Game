#pragma once

#include"ModelTypeData.h"
#include"Actor.h"
class Enemy:public Actor
{
public:
	Enemy(CollisionTag _tag, bool m_alive);
	~Enemy()override;
	//更新
	void Update();
	//描画
	void Draw();
	//初期化
	void Init()override;
	//当たり判定処理
	void OnCollisionEnter(class Collision* otherCollision)override;

	const bool IsAlive() { return m_isAlive;}
private:
	//モデル
	class PMDModel& m_model;            //  PMDモデルの管理
	class EffekseerManager& m_effect;
	float m_speed;
	class Sound& m_sound;
	class SupportJson& m_json;
	bool m_isAlive;
	 PMDModelType modeltype;
};