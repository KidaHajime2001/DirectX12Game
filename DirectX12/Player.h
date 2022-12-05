#pragma once
#include"Actor.h"
class Player:public Actor
{
public:
	//コンストラクタ、デストラクタ
	Player(CollisionTag _tag, const bool _alive);
	~Player()override;

	//更新
	void Update();

	//ゲーム内移動制限
	void RestrictionsPosition();

	//描画
	void Draw();

	//初期化
	void Init()override;

	//当たり判定処理
	void OnCollisionEnter(class Collision* otherCollision)override;

	const bool IsAlive() { return m_isAlive; };
private:
	
	//移動系の処理updateの中で動いてほしいのでプライベート
	void Move();
	void TakeAim( );
	void MoveEffect(const float _inputSize);

	//射撃関連の変数多いのでまとめる
	struct ShotStatus 
	{
		bool shotFlag		=false;
		int	 shotInterval	=0;
		XMFLOAT3 shotDirection = {0,0,1};
		float shotSpeed=4.0f;
		float cosDirection=0.0f;
	};
	ShotStatus m_shotStatus;
	class PlayerShotDirector* m_shotDirector;
	//射撃のクールタイム
	const int SHOT_COOL_FLAME = 3;

	//入力のデッドゾーン
	const float DEADZONE = 0.3f;

	//モデル
	class PMDModel& m_model;
	//コントローラー
	class Controller& m_controller;
	//カメラ
	class Camera& m_camera;
	//サウンド
	class Sound& m_sound;
	//json読み込み
	class SupportJson& m_json;
	//フレーム管理
	class Fps& m_fps;
	//タイマー
	class Time* m_timer;
	//当たり判定半径
	int RADIUS_NUM = 1;

	//生存フラグ
	bool m_isAlive;

	//中心のキューブのアニメーション用
	int m_cubeRotate;

	//移動時のエフェクト用変数
	int m_inputFlameCount;
	bool m_inputFlameFlag;
};

