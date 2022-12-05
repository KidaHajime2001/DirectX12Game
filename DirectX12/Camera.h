#pragma once

#include"DirectXTex.h"
using namespace DirectX;
class Camera
{
public:
	//コンストラクタ
	Camera();
	//デストラクタ
	~Camera();
	
	/// <summary>
	/// 毎フレームの更新
	/// </summary>
	void Update();

	/// <summary>
	/// タイトル用の設定に変更する
	//タイトル中は動かないので一度呼び出すだけでよい
	/// </summary>
	void TitleSetting();

	/// <summary>
	/// ゲームスタートの際のカメラの動き
	/// </summary>
	void MovementGameStart();

	/// <summary>
	/// カメラはプレイヤーについてまわるので必要
	/// </summary>
	/// <param name="_playerPos">
	/// プレイヤーの位置
	/// </param>
	void SetPlayerPosition(const XMFLOAT3& _playerPos);

	/// <summary>
	/// 画面クリアの色を設定
	/// </summary>
	/// <param name="_colors">
	/// 画面をクリアする色
	/// </param>
	void SetBackGroundColor(const XMFLOAT3& _colors);

	/// <summary>
	/// シングルトンとしてゲームをまたいで存在するため
	/// 手動でリセットを掛ける必要がある
	/// </summary>
	void Reset();

	/// <summary>
	/// カメラとプレイヤーの位置から外積を出す際に使う
	/// </summary>
	/// <returns>
	/// 位置を返す(x,y,z)
	/// </returns>
	const DirectX::XMFLOAT3 GetPosition() { return m_cameraPosition; };

	/// <summary>
	/// カメラの初期移動が完了したか？
	/// </summary>
	const bool GetCompleteFlag() { return m_isMoveComplete; };
private:
	//デバイス
	class D12Device& m_device;
	//コントローラー
	class Controller& m_controller;

	//カメラのイベント移動が完了したか
	bool m_isMoveComplete;
	//カメラの位置
	XMFLOAT3 m_cameraPosition;
	//カメラのターゲットの位置主にプレイヤー
	XMFLOAT3 m_targetPosition;

	//カメラがプレイヤーから離れている距離
	const float CAMERA_ADJUST_POSITION_Y		= 100;
	//カメラがプレイヤーから離れている距離
	const float CAMERA_ADJUST_POSITION_Z		=-100;

	//タイトルの際のターゲットポジション
	const XMFLOAT3 m_titleTargetPosition;
	//タイトルの際のカメラのポジション
	const XMFLOAT3 m_titleCameraPosition;

	//カメラの上方向は動かないのでy=1
	const XMFLOAT3 m_up = XMFLOAT3(0,1,0);

	//リセットの際の初期カメラポジション
	const XMFLOAT3 DefaultCameraPosition = XMFLOAT3(0, 10, -100);
	//リセットの際のターゲットポジション
	const XMFLOAT3 DefaultTargetPosition = XMFLOAT3(0, 0, 0);
	//リセットの際のイベント移動終わりのカメラポジション
	const XMFLOAT3 DefaultGameCameraPosition = XMFLOAT3(0, 100, -100);

	//イベントでカメラが動くとき、毎フレームどれだけ移動するのか
	XMFLOAT3 m_code;

	//100回目のカウントでちょうどカメラの移動が完了する
	const int STARTCOUNT = 100;
	//移動終わりまでのカウント、増カ用
	int m_startCount;

};
