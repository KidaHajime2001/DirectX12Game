#pragma once
#include"Actor.h"
class Player:public Actor
{
public:
	Player(CollisionTag _tag, const bool _alive);
	~Player()override;
	//�X�V
	void Update();
	void RestrictionsPosition();
	//�`��
	void Draw();
	//������
	void Init()override;
	//�����蔻�菈��
	void OnCollisionEnter(class Collision* otherCollision)override;
	
	const bool IsShotFlag() { return m_shotStatus.shotFlag; };
	const XMFLOAT3 GetShotDirection() { return m_shotStatus.shotDirection; };
	const float GetShotSpeed() { return m_shotStatus.shotSpeed; };
	const XMFLOAT3 GetInputVec() { return m_shotStatus.shotDirection; };
	const bool IsAlive() { return m_isAlive; };
private:
	//�ړ��n�̏���update�̒��œ����Ăق����̂Ńv���C�x�[�g
	void Move();
	void TakeAim( );
	void MoveEffect(const float _inputSize);
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

	const int SHOT_COOL_FLAME = 3;
	const float DEADZONE = 0.3f;
	struct JumpStatus
	{
		float JumpPower = 2.0f;
		float JumpPrev = 0;
		float Gravity = 0.10f;;
		bool JumpFlag = false;
		void Init()
		{
			 JumpPower = 2.0f;
			 JumpPrev = 0;
			 Gravity = 0.10f;
			JumpFlag = false;
		}
	};
	JumpStatus m_jumpStatus;
	//���f��
	class PMDModel& m_model;            //  PMD���f���̊Ǘ�
	class Controller& m_controller;
	class Camera& m_camera;
	class Sound& m_sound;
	class SupportJson& m_json;
	int RADIUS_NUM = 1;
	bool m_isAlive;
	int m_cubeRotate;

	int m_inputFlameCount;
	bool m_inputFlameFlag;
	const float EFFECT_INTERVAL=30;


	//float RotateAngle;
	//float UpAngle;
	//float Length = 100;
	//float CameraSpeed = 2;
};

