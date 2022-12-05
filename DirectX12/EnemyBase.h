#pragma once
#include"Actor.h"
#include"ModelTypeData.h"
#include"EnemyType.h"
enum class EnemyType;

//�G�l�~�[�̋��ʕ���
class EnemyBase :public Actor
{
public:
	//�R���X�g���N�^
	EnemyBase(CollisionTag _tag, bool m_alive);
	virtual ~EnemyBase();
	//������
	void Init();
	//�X�V
	virtual void Update(const DirectX::XMFLOAT3 _targetPos);
	//�`��
	void Draw();

	//�f�[�^�̃��[�h
	void LoadData(const EnemyType _enemyType);
	
	//�����t���O
	const bool IsAlive() { return m_isAlive; }

	/// <summary>
	/// �ݒ肵���ʒu�ɏo��
	/// </summary>
	/// <param name="_adventPosition">
	/// �o������|�W�V����
	/// </param>
	void Advent(DirectX::XMFLOAT3 _adventPosition);

	
	const EnemyType GetEnemyType() { return m_enemyType; };
	const bool GetDefeatFlag() { return m_isHit; };
protected:
	//�����蔻�菈��
	void OnCollisionEnter(class Collision* otherCollision);

	/// <summary>
	/// �ŗL�̓����蔻��A�N�V����
	/// ���ʂ̕����̃R�s�y�����点��̂ł͂Ȃ����ƍl�������ʂ����Ȃ���
	/// �������͕s��
	/// </summary>
	/// <param name="otherCollision">
	/// �����������I�u�W�F�N�g 
	/// </param>
	virtual void CollisionOriginal(class Collision* otherCollision);

	

	/// <summary>
	/// �Ȉ�AI�̑ҋ@�s��
	/// </summary>
	/// <param name="_targetPos">
	/// �^�[�Q�b�g�i�v���C���[�j�̈ʒu
	/// </param>
	virtual void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);

	/// <summary>
	/// �Ȉ�AI�̍U���s��
	/// </summary>
	/// <param name="_targetPos">
	///�^�[�Q�b�g�̈ʒu
	/// </param>
	virtual void AttackUpdate(const DirectX::XMFLOAT3 _targetPos);

	/// <summary>
	/// �Ȉ�AI�̈ړ��s��
	/// </summary>
	/// <param name="_targetPos">
	/// �^�[�Q�b�g�̈ʒu
	/// </param>
	virtual void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);

	//���f��
	class PMDModel& m_model;            //  PMD���f���̊Ǘ�
	PMDModelType m_modeltype;			//�@PMD���f���̃^�C�v
	
	//�G�t�F�N�g
	class EffekseerManager& m_effect;

	//�e�����N���X
	class EnemyShotDirector* m_enemyShotDirector;

	//�T�E���h
	class Sound& m_sound;

	//�����t���O
	bool m_isAlive;

	//�v���C���[�̒e�ɓ����������ǂ���
	bool m_isHit;

	//�Ȉ�AI�p�X�e�[�g
	enum class EnemyState
	{
		wait,
		attack,
		move,
	};
	EnemyState m_enemyState;

	//enemy�̃^�C�v
	EnemyType m_enemyType;

	//����
	DirectX::XMFLOAT3 m_nowDirection;

	//�ŏ��Ɍ����Ă������
	const DirectX::XMFLOAT3 DEFAULT_DIRECTION = DirectX::XMFLOAT3(0,0,1);

	//�ړ����x
	float m_speed;
	//�����蔻��̉��u��
	float m_radiusData;
};