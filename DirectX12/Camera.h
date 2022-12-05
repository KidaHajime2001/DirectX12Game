#pragma once

#include"DirectXTex.h"
using namespace DirectX;
class Camera
{
public:
	//�R���X�g���N�^
	Camera();
	//�f�X�g���N�^
	~Camera();
	
	/// <summary>
	/// ���t���[���̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �^�C�g���p�̐ݒ�ɕύX����
	//�^�C�g�����͓����Ȃ��̂ň�x�Ăяo�������ł悢
	/// </summary>
	void TitleSetting();

	/// <summary>
	/// �Q�[���X�^�[�g�̍ۂ̃J�����̓���
	/// </summary>
	void MovementGameStart();

	/// <summary>
	/// �J�����̓v���C���[�ɂ��Ă܂��̂ŕK�v
	/// </summary>
	/// <param name="_playerPos">
	/// �v���C���[�̈ʒu
	/// </param>
	void SetPlayerPosition(const XMFLOAT3& _playerPos);

	/// <summary>
	/// ��ʃN���A�̐F��ݒ�
	/// </summary>
	/// <param name="_colors">
	/// ��ʂ��N���A����F
	/// </param>
	void SetBackGroundColor(const XMFLOAT3& _colors);

	/// <summary>
	/// �V���O���g���Ƃ��ăQ�[�����܂����ő��݂��邽��
	/// �蓮�Ń��Z�b�g���|����K�v������
	/// </summary>
	void Reset();

	/// <summary>
	/// �J�����ƃv���C���[�̈ʒu����O�ς��o���ۂɎg��
	/// </summary>
	/// <returns>
	/// �ʒu��Ԃ�(x,y,z)
	/// </returns>
	const DirectX::XMFLOAT3 GetPosition() { return m_cameraPosition; };

	/// <summary>
	/// �J�����̏����ړ��������������H
	/// </summary>
	const bool GetCompleteFlag() { return m_isMoveComplete; };
private:
	//�f�o�C�X
	class D12Device& m_device;
	//�R���g���[���[
	class Controller& m_controller;

	//�J�����̃C�x���g�ړ�������������
	bool m_isMoveComplete;
	//�J�����̈ʒu
	XMFLOAT3 m_cameraPosition;
	//�J�����̃^�[�Q�b�g�̈ʒu��Ƀv���C���[
	XMFLOAT3 m_targetPosition;

	//�J�������v���C���[���痣��Ă��鋗��
	const float CAMERA_ADJUST_POSITION_Y		= 100;
	//�J�������v���C���[���痣��Ă��鋗��
	const float CAMERA_ADJUST_POSITION_Z		=-100;

	//�^�C�g���̍ۂ̃^�[�Q�b�g�|�W�V����
	const XMFLOAT3 m_titleTargetPosition;
	//�^�C�g���̍ۂ̃J�����̃|�W�V����
	const XMFLOAT3 m_titleCameraPosition;

	//�J�����̏�����͓����Ȃ��̂�y=1
	const XMFLOAT3 m_up = XMFLOAT3(0,1,0);

	//���Z�b�g�̍ۂ̏����J�����|�W�V����
	const XMFLOAT3 DefaultCameraPosition = XMFLOAT3(0, 10, -100);
	//���Z�b�g�̍ۂ̃^�[�Q�b�g�|�W�V����
	const XMFLOAT3 DefaultTargetPosition = XMFLOAT3(0, 0, 0);
	//���Z�b�g�̍ۂ̃C�x���g�ړ��I���̃J�����|�W�V����
	const XMFLOAT3 DefaultGameCameraPosition = XMFLOAT3(0, 100, -100);

	//�C�x���g�ŃJ�����������Ƃ��A���t���[���ǂꂾ���ړ�����̂�
	XMFLOAT3 m_code;

	//100��ڂ̃J�E���g�ł��傤�ǃJ�����̈ړ�����������
	const int STARTCOUNT = 100;
	//�ړ��I���܂ł̃J�E���g�A���J�p
	int m_startCount;

};
