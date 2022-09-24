#pragma once

#include"DirectXTex.h"
using namespace DirectX;
class Camera
{
public:
	Camera();
	~Camera();
	void Update();
	void SetPlayerPosition(const XMFLOAT3& _playerPos);
	void ChangeState();
	void AdjustPosition();
	const DirectX::XMFLOAT3 GetPosition() { return m_cameraPosition; };
private:

	class D12Device& m_device;
	class Controller& m_controller;
	enum class CameraState
	{
		NeartoMillde,
		MiddletoFar,
		MiddletoNear,
		FartoMiddle,
	};
	CameraState m_state;
	CameraState m_beforeState;
	XMFLOAT3 m_cameraPosition;
	XMFLOAT3 m_targetPosition;
	const float CAMERA_ADJUST_Y_MIDDLE	= 50;
	const float CAMERA_ADJUST_Z_MIDDLE	=-50;
	const float CAMERA_ADJUST_Y_NEAR	= 30;
	const float CAMERA_ADJUST_Z_NEAR	=-30;
	const float CAMERA_ADJUST_Y_FAR		= 70;
	const float CAMERA_ADJUST_Z_FAR		=-70;
};
