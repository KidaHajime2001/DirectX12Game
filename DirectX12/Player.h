#pragma once
#include"Actor.h"
class Player:public Actor
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	Player(CollisionTag _tag, const bool _alive);
	~Player()override;

	//�X�V
	void Update();

	//�Q�[�����ړ�����
	void RestrictionsPosition();

	//�`��
	void Draw();

	//������
	void Init()override;

	//�����蔻�菈��
	void OnCollisionEnter(class Collision* otherCollision)override;

	const bool IsAlive() { return m_isAlive; };
private:
	
	//�ړ��n�̏���update�̒��œ����Ăق����̂Ńv���C�x�[�g
	void Move();
	void TakeAim( );
	void MoveEffect(const float _inputSize);

	//�ˌ��֘A�̕ϐ������̂ł܂Ƃ߂�
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
	//�ˌ��̃N�[���^�C��
	const int SHOT_COOL_FLAME = 3;

	//���͂̃f�b�h�]�[��
	const float DEADZONE = 0.3f;

	//���f��
	class PMDModel& m_model;
	//�R���g���[���[
	class Controller& m_controller;
	//�J����
	class Camera& m_camera;
	//�T�E���h
	class Sound& m_sound;
	//json�ǂݍ���
	class SupportJson& m_json;
	//�t���[���Ǘ�
	class Fps& m_fps;
	//�^�C�}�[
	class Time* m_timer;
	//�����蔻�蔼�a
	int RADIUS_NUM = 1;

	//�����t���O
	bool m_isAlive;

	//���S�̃L���[�u�̃A�j���[�V�����p
	int m_cubeRotate;

	//�ړ����̃G�t�F�N�g�p�ϐ�
	int m_inputFlameCount;
	bool m_inputFlameFlag;
};

