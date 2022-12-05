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
	//�^�[�Q�b�g+�␳�ʒu���J�����|�W�V����
	m_cameraPosition = m_targetPosition;
	m_cameraPosition.y += CAMERA_ADJUST_POSITION_Y;
	m_cameraPosition.z += CAMERA_ADJUST_POSITION_Z;

	//�J�����ʒu�̍X�V
	m_device.UpdateCameraPos(m_cameraPosition, m_targetPosition, m_up);
}

void Camera::TitleSetting()
{
	//�^�C�g���p�̃J�����ʒu�ɐݒ�
	m_device.UpdateCameraPos(m_titleCameraPosition, m_titleTargetPosition, m_up);
}

void Camera::MovementGameStart()
{
	//�ړ��������Ă��邩
	if (m_startCount>=STARTCOUNT)
	{
		//�����̃t���O�𗧂Ă�
		m_isMoveComplete = true;
		//����ȏ�̏����͕s�v
		return;
	}
	//�J������ڕW�܂ňړ�
	m_cameraPosition = XMF3Math::AddXMFLOAT3(m_cameraPosition,m_code);
	//�J�����X�V
	m_device.UpdateCameraPos(m_cameraPosition, m_targetPosition, m_up);
	//�J�E���g�𑝂₷
	m_startCount++;
}

void Camera::SetPlayerPosition(const XMFLOAT3& _playerPos)
{
	//�^�[�Q�b�g��ݒ�
	m_targetPosition = _playerPos;
}

void Camera::SetBackGroundColor(const XMFLOAT3& _colors)
{
	m_device.SetBackGroundColor(_colors);
}


void Camera::Reset()
{
	//�ݒ�̏�����
	m_isMoveComplete = false;
	m_startCount = 0;
	m_cameraPosition = DefaultCameraPosition;
	m_targetPosition = DefaultTargetPosition;;
	m_device.SetBackGroundColor(XMFLOAT3(0,0,0));
	m_device.UpdateCameraPos(DefaultCameraPosition, DefaultTargetPosition, m_up);
}
