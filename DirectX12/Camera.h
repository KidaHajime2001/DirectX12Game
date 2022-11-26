#pragma once

#include"DirectXTex.h"
using namespace DirectX;
class Camera
{
public:
	Camera();
	~Camera();
	void Update();
	void TitleSetting();
	void MoveGameStartCamera();
	void SetPlayerPosition(const XMFLOAT3& _playerPos);
	void SetBackGroundColor(const XMFLOAT3& _colors);
	void SetShakeCameraPosition(const XMFLOAT3& _pos);

	void AdjustPosition();
	void Reset();
	const DirectX::XMFLOAT3 GetPosition() { return m_cameraPosition; };
	const bool GetCompleteFlag() { return m_moveStartCameraComplete; };
private:

	class D12Device& m_device;
	class Controller& m_controller;
	bool m_moveStartCameraComplete;
	enum class CameraState
	{
		NeartoMillde,
		MiddletoFar,
		MiddletoNear,
		FartoMiddle,
		Zero,
	};
	CameraState m_state;
	CameraState m_beforeState;
	XMFLOAT3 m_shakePosition;
	XMFLOAT3 m_cameraPosition;
	XMFLOAT3 m_targetPosition;
	XMFLOAT3 m_changePosition;
	/*const float CAMERA_ADJUST_Y_MIDDLE	= 100;
	const float CAMERA_ADJUST_Z_MIDDLE	=-100;
	const float CAMERA_ADJUST_Y_NEAR	= 30;
	const float CAMERA_ADJUST_Z_NEAR	=-30;*/
	const float CAMERA_ADJUST_Y_FAR		= 100;
	const float CAMERA_ADJUST_Z_FAR		=-100;

	const XMFLOAT3 m_titleTargetPosition;
	const XMFLOAT3 m_titleCameraPosition;
	const XMFLOAT3 m_up;

	const XMFLOAT3 DefaultCameraPosition = XMFLOAT3(0, 10, -100);
	const XMFLOAT3 DefaultTargetPosition = XMFLOAT3(0, 0, 0);
	const XMFLOAT3 DefaultGameCameraPosition = XMFLOAT3(0, 100, -100);
	XMFLOAT3 m_code;
	const int STARTCOUNT = 100;//è\âÒ
	int m_startCount;

};
