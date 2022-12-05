#include "Camera.h"
#include"Singleton.h"
#include"D12Device.h"
#include"Controller.h"

#include"XMF3Math.h"
Camera::Camera()
	:m_device(Singleton<D12Device>::GetInstance())
	, m_controller(Singleton<Controller>::GetInstance())
	, m_titleCameraPosition(XMFLOAT3(0, 20, 0))
	, m_titleTargetPosition(XMFLOAT3(0, 0, 0))
	, m_isMoveComplete(false)
	, m_code(0,0.9f,0.0f)
	,m_startCount(0)
{
	
}

Camera::~Camera()
{
}

void Camera::Update()
{
	//ターゲット+補正位置＝カメラポジション
	m_cameraPosition = m_targetPosition;
	m_cameraPosition.y += CAMERA_ADJUST_POSITION_Y;
	m_cameraPosition.z += CAMERA_ADJUST_POSITION_Z;

	//カメラ位置の更新
	m_device.UpdateCameraPos(m_cameraPosition, m_targetPosition, m_up);
}

void Camera::TitleSetting()
{
	//タイトル用のカメラ位置に設定
	m_device.UpdateCameraPos(m_titleCameraPosition, m_titleTargetPosition, m_up);
}

void Camera::MovementGameStart()
{
	//移動完了しているか
	if (m_startCount>=STARTCOUNT)
	{
		//完了のフラグを立てて
		m_isMoveComplete = true;
		//これ以上の処理は不要
		return;
	}
	//カメラを目標まで移動
	m_cameraPosition = XMF3Math::AddXMFLOAT3(m_cameraPosition,m_code);
	//カメラ更新
	m_device.UpdateCameraPos(m_cameraPosition, m_targetPosition, m_up);
	//カウントを増やす
	m_startCount++;
}

void Camera::SetPlayerPosition(const XMFLOAT3& _playerPos)
{
	//ターゲットを設定
	m_targetPosition = _playerPos;
}

void Camera::SetBackGroundColor(const XMFLOAT3& _colors)
{
	m_device.SetBackGroundColor(_colors);
}


void Camera::Reset()
{
	//設定の初期化
	m_isMoveComplete = false;
	m_startCount = 0;
	m_cameraPosition = DefaultCameraPosition;
	m_targetPosition = DefaultTargetPosition;;
	m_device.SetBackGroundColor(XMFLOAT3(0,0,0));
	m_device.UpdateCameraPos(DefaultCameraPosition, DefaultTargetPosition, m_up);
}
