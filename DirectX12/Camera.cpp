#include "Camera.h"
#include"Singleton.h"
#include"D12Device.h"
#include"Controller.h"
Camera::Camera()
	:m_device(Singleton<D12Device>::GetInstance())
	, m_controller(Singleton<Controller>::GetInstance())
	, m_state(CameraState::MiddletoNear)
	, m_up(XMFLOAT3(0, 1, 0))
	,m_titleCameraPosition(XMFLOAT3(0, 20, 0))
	,m_titleTargetPosition(XMFLOAT3(0, 0, 0))
{
	
}

Camera::~Camera()
{
}

void Camera::Update()
{

	if (m_controller.IsPushEnter(ButtonName::GAMEPAD_RIGHT_THUMB))
	{
		ChangeState();
	}
	AdjustPosition();



	m_beforeState = m_state;
}

void Camera::TitleSetting()
{
	m_device.UpdateCameraPos(m_titleCameraPosition, m_titleTargetPosition, m_up);
}

void Camera::SetPlayerPosition(const XMFLOAT3& _playerPos)
{
	m_targetPosition = _playerPos;
}

void Camera::ChangeState()
{
	switch (m_state)
	{
	case CameraState::NeartoMillde:
		m_state = CameraState::MiddletoFar;
		break;
	case CameraState::MiddletoFar:
		m_state = CameraState::FartoMiddle;
		break;
	case CameraState::FartoMiddle:
		m_state = CameraState::MiddletoNear;
		break;
	case CameraState::MiddletoNear:
		m_state = CameraState::NeartoMillde;
		break;
	}
}

void Camera::AdjustPosition()
{
	m_cameraPosition=m_targetPosition;
	switch (m_state)
	{
	case CameraState::NeartoMillde:
		m_cameraPosition.y += CAMERA_ADJUST_Y_NEAR;
		m_cameraPosition.z += CAMERA_ADJUST_Z_NEAR;
		break;
	case CameraState::MiddletoFar:
		m_cameraPosition.y += CAMERA_ADJUST_Y_MIDDLE;
		m_cameraPosition.z += CAMERA_ADJUST_Z_MIDDLE;
		break;
	case CameraState::FartoMiddle:
		m_cameraPosition.y += CAMERA_ADJUST_Y_MIDDLE;
		m_cameraPosition.z += CAMERA_ADJUST_Z_MIDDLE;
		break;
	case CameraState::MiddletoNear:
		m_cameraPosition.y += CAMERA_ADJUST_Y_FAR;
		m_cameraPosition.z += CAMERA_ADJUST_Z_FAR;
		break;
	}
	m_device.UpdateCameraPos(m_cameraPosition,m_targetPosition,m_up);
}