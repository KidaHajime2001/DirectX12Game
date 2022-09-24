#pragma once

#include"ModelTypeData.h"
#include"Actor.h"
class Enemy:public Actor
{
public:
	Enemy(CollisionTag _tag, bool Alive);
	~Enemy()override;
	//更新
	void Update()override;
	//描画
	void Draw()override;
	//初期化
	void Init()override;
	//当たり判定処理
	void OnCollisionEnter(class Collision* otherCollision)override;
private:
	//モデル
	class PMDModel& m_model;            //  PMDモデルの管理
	class EffekseerManager& m_effect;
	float m_speed;
	class Sound& m_sound;
	class SupportJson& m_json;
	 PMDModelType modeltype;
};