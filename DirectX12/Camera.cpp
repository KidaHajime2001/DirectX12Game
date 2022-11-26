#include "Camera.h"
#include"Singleton.h"
#include"D12Device.h"
#include"Controller.h"

#include"XMF3Math.h"
Camera::Camera()
	:m_device(Singleton<D12Device>::GetInstance())
	, m_controller(Singleton<Controller>::GetInstance())
	, m_state(CameraState::MiddletoNear)
	, m_up(XMFLOAT3(0, 1, 0))
	, m_titleCameraPosition(XMFLOAT3(0, 20, 0))
	, m_titleTargetPosition(XMFLOAT3(0, 0, 0))
	, m_moveStartCameraComplete(false)
	, m_code(0,0.9f,0.0f)
	,m_shakePosition(0,0,0)
	,m_startCount(0)
{
	
}

Camera::~Camera()
{
}

void Camera::Update()
{
	m_cameraPosition = m_targetPosition;
	m_cameraPosition =XMF3Math::AddXMFLOAT3(m_cameraPosition, m_shakePosition);

	m_cameraPosition.y += CAMERA_ADJUST_Y_FAR;
	m_cameraPosition.z += CAMERA_ADJUST_Z_FAR;
	m_device.UpdateCameraPos(m_cameraPosition, m_targetPosition, m_up);
}

void Camera::TitleSetting()
{
	m_device.UpdateCameraPos(m_titleCameraPosition, m_titleTargetPosition, m_up);
}

void Camera::MoveGameStartCamera()
{
	if (m_startCount>=STARTCOUNT)
	{
		m_moveStartCameraComplete = true;

		return;
	}
	m_cameraPosition = XMF3Math::AddXMFLOAT3(m_cameraPosition,m_code);
	m_device.UpdateCameraPos(m_cameraPosition, m_targetPosition, m_up);
	m_startCount++;

	
}

void Camera::SetPlayerPosition(const XMFLOAT3& _playerPos)
{
	m_targetPosition = _playerPos;
}

void Camera::SetBackGroundColor(const XMFLOAT3& _colors)
{
	m_device.SetBackGroundColor(_colors);
}

void Camera::SetShakeCameraPosition(const XMFLOAT3& _pos)
{
	m_shakePosition = _pos;
}

void Camera::AdjustPosition()
{
	/*if (45 + CAMERA_ADJUST_Z_FAR >= m_cameraPosition.z||
		-45 + CAMERA_ADJUST_Z_FAR <= m_cameraPosition.z||
		45 >= m_cameraPosition.x||
		-45 <= m_cameraPosition.x)
	{
		return;
	}*/
	
}

void Camera::Reset()
{
	m_moveStartCameraComplete = false;
	m_startCount = 0;
	m_cameraPosition = DefaultCameraPosition;
	m_targetPosition = DefaultTargetPosition;;
	m_device.SetBackGroundColor(XMFLOAT3(0,0,0));
	m_device.UpdateCameraPos(DefaultCameraPosition, DefaultTargetPosition, m_up);
}
