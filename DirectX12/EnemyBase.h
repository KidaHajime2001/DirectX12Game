#pragma once
#include"Actor.h"
#include"ModelTypeData.h"

enum class EnemyType;

class EnemyBase:public Actor
{
public:
	EnemyBase(CollisionTag _tag, bool m_alive);
	virtual ~EnemyBase();
	void Init();
	//�X�V
	virtual void Update(const DirectX::XMFLOAT3 _targetPos);
	//�`��
	void Draw();
	
	//�f�[�^�̃��[�h
	void LoadData(const EnemyType _enemyType);

	const bool IsAlive() { return m_isAlive; }
	void Advent(DirectX::XMFLOAT3 _adventPosition);

	//�����蔻�菈��
	void OnCollisionEnter(class Collision* otherCollision)override;
	virtual void CollisionOriginal(class Collision* otherCollision);
protected:

	virtual void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);
	virtual void AttackUpdate(const DirectX::XMFLOAT3 _targetPos);
	virtual void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);

	//���f��
	class PMDModel& m_model;            //  PMD���f���̊Ǘ�
	PMDModelType m_modeltype;
	
	//�G�t�F�N�g
	class EffekseerManager& m_effect;

	//�e��łN���X
	class EnemyShotDirector* m_enemyShotDirector;

	//�T�E���h
	class Sound& m_sound;

	//�����t���O
	bool m_isAlive;



	//�Ȉ�AI�p�X�e�[�g
	enum class EnemyState
	{
		wait,
		attack,
		move,
	};
	EnemyState m_enemyState;

	//�e���Ƃ��̃t���O�Ǘ�
	struct AttackParam
	{
		float attackCoolTime;
		DirectX::XMFLOAT3 aimVec;
		void Init()
		{
			shotFlag = false;
		}
		bool shotFlag;
	};
	AttackParam m_attackParam;
	EnemyType m_enemyType;

	//����
	DirectX::XMFLOAT3 m_nowDirection;
	const DirectX::XMFLOAT3 DEFAULT_DIRECTION = DirectX::XMFLOAT3(0,0,1);
	float m_direction;
	float m_speed;
	float m_radiusData;
};