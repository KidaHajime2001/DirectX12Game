#pragma once
#include"Actor.h"

#include"ModelTypeData.h"
class SnakeTail: public Actor
{
public:
	SnakeTail(CollisionTag _tag, bool m_alive, DirectX::XMFLOAT3 _nowDirection);
	virtual ~SnakeTail();
	//初期化
	void Init();
	void Update(DirectX::XMFLOAT3 _frontPos, DirectX::XMFLOAT3 _frontDirection);
	void Draw();
	//当たり判定処理
	void OnCollisionEnter(class Collision* otherCollision);
	void SetVisible(bool _isVisible);
private:
	//生存フラグ
	bool m_isAlive;
	//向き
	DirectX::XMFLOAT3 m_nowDirection;
	//当たり判定の仮置き
	float m_radiusData=2;
	//モデル
	class PMDModel& m_model;            //  PMDモデルの管理
	PMDModelType m_modeltype;			//　PMDモデルのタイプ
	bool m_isVisible;
};