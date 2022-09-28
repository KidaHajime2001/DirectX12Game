#pragma once
#include"Actor.h"
class Player:public Actor
{
public:
	Player(CollisionTag _tag, const bool _alive);
	~Player()override;
	//更新
	void Update();
	//描画
	void Draw();
	//初期化
	void Init()override;
	//当たり判定処理
	void OnCollisionEnter(class Collision* otherCollision)override;
	
	const bool IsShotFlag() { return m_shotStatus.shotFlag; };
	const XMFLOAT3 GetShotDirection() { return m_shotStatus.shotDirection; };
	const float GetShotSpeed() { return m_shotStatus.shotSpeed; };
	const XMFLOAT3 GetInputVec() { return m_shotStatus.shotDirection; };
	const bool IsAlive() { return m_isAlive; };
private:
	//移動系の処理updateの中で動いてほしいのでプライベート
	void Move();
	void TakeAim();
	
	struct ShotStatus 
	{
		bool shotFlag		=false;
		int	 shotInterval	=0;
		XMFLOAT3 shotDirection = {0,0,1};
		float shotSpeed=4.0f;
		float cosDirection=0.0f;
		XMFLOAT3 TmpShotDirection=shotDirection;
	};
	ShotStatus m_shotStatus;
	class PlayerShotDirector* m_shotDirector;

	const int SHOT_COOL_FLAME = 3;

	struct JumpStatus
	{
		float JumpPower = 2.0f;
		float JumpPrev = 0;
		float Gravity = 0.10f;;
		bool JumpFlag = false;
		void Init()
		{
			 JumpPower = 2.0f;
			 JumpPrev = 0;
			 Gravity = 0.10f;
			JumpFlag = false;
		}
	};
	JumpStatus m_jumpStatus;
	//モデル
	class PMDModel& m_model;            //  PMDモデルの管理
	class Controller& m_controller;
	class Camera& m_camera;
	class Sound& m_sound;
	class SupportJson& m_json;
	int RADIUS_NUM = 1;
	bool m_isAlive;
};

