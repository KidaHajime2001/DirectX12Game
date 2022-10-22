#pragma once

#include"ModelTypeData.h"
#include"Actor.h"
enum class EnemyType;
class Enemy:public Actor
{
public:
	Enemy(CollisionTag _tag, bool m_alive);
	~Enemy()override;
	//�X�V
	void Update(const DirectX::XMFLOAT3 _targetPos);
	//�`��
	void Draw();
	//������
	void CollisionInit()override;
	//�����蔻�菈��
	void OnCollisionEnter(class Collision* otherCollision)override;

	const bool IsAlive() { return m_isAlive;}
	const EnemyType GetEnemyType(std::string _typeName);
	void LoadData(const EnemyType _enemyType);
	const DirectX::XMFLOAT3 GetAimVec() { return m_nowVec; };
	
private:
	void Move();
	void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);
	void AttackUpdate(const DirectX::XMFLOAT3 _targetPos);
	void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);

	void TakeAim(const DirectX::XMFLOAT3 _targetPos);
	void RotateAim();
	
	//���f��
	class PMDModel& m_model;            //  PMD���f���̊Ǘ�
	class EffekseerManager& m_effect;
	class Sound& m_sound;
	class SupportJson& m_json;
	class EnemyShotDirector* m_enemyShotDirector;
	class Time* m_timer;

	//�e���Ƃ��̃t���O�Ǘ�
	struct ShotParam
	{
		void Init()
		{
			shotFlag = false;
		}
		bool shotFlag;
	};
	ShotParam m_shotParam;

	//����
	DirectX::XMFLOAT3 m_nowVec;
	float m_direction;

	//�ړ�����
	DirectX::XMFLOAT3 m_acceleration;
	DirectX::XMFLOAT3 m_velocity;

	//�Ȉ�AI�p�X�e�[�g
	enum class EnemyState
	{
		wait,
		attack,
		move,
	};
	EnemyState m_enemyState;

	//�����t���O
	bool m_isAlive;

	//json�œǂ񂾕����ǂ��H
	const float NEAR_DISTANCE = 5.0f;
	PMDModelType m_modeltype;
	EnemyType m_enemyType;
	float m_speed;

	int WaitStateTime		= 1;
	int MoveStateTime		= 3;
	int AttackStateTime		= 5;

	int EnemyAttackCoolTime = 1;
};