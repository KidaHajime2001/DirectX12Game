#pragma once
#include <DirectXMath.h>
#include <list>
enum class EnemyType;
class EnemyManager
{
public:
	//�R���X�g���N�^
	EnemyManager();

	//�f�X�g���N�^
	~EnemyManager();

	//�X�V
	void Update(const DirectX::XMFLOAT3& _targetPos);
	
	//�`��
	void Draw();

	//90�b���_����̏o���C�x���g
	void Advent90s();
	//60�b���_����̏o���C�x���g
	void Advent60s();
	//30�b���_����̏o���C�x���g
	void Advent30s();

	//Enemy�̌��j����XMFLOAT2�ɂ܂Ƃ߂�iLESSER,HIGHER�j
	const DirectX::XMFLOAT2 GetEnemyDefeatScore() { return DirectX::XMFLOAT2(m_lesserNumScore, m_higherNumScore); };

	//�Q�[�����x�����󂯎��
	void SetGameLevel(int _level);
private:
	//�G���j�������Z
	void AddScore(const EnemyType _enemyType);
	//�G�l�~�[���o��
	void CallEnemy();

	/// <summary>
	/// �G��ǉ�����
	/// CallEnemy���ȂǂŌĂ΂�����Ŏw�肳�ꂽ�ꏊ�ɓG���o��������
	/// </summary>
	/// <param name="_type">�Ăяo���G�̃^�C�v</param>
	/// <param name="_num">�Ăяo����</param>
	/// <param name="_adventPosition">�Ăяo���|�W�V����</param>
	void AddEnemy(const EnemyType& _type, const int& _num,const DirectX::XMFLOAT3& _adventPosition);
	
	//�G�v�[��
	class EnemyPool& m_enemyPool;

	//�G�̍U���v�[��
	class EnemyAttackPool& m_enemyAttackPool;

	//�������Ă���G�̃��X�g
	std::list<class EnemyBase*> m_nowAliveEnemyList;
	//�����Ă��郊�X�g���珜������G�̃��X�g
	std::list<class EnemyBase*> m_deleteList;

	//���Ԃ�}��N���X
	class Time* m_timer;
	
	//��Փx
	float m_seriousDegree = 1.0f;
	//��Փx���l�����Ȃ��G�o���̎���
	const float DEFAULT_CALL_TIME = 10.0f;
	//��Փx�œG�o���𒲐�����ۂ̌W��
	const float SERIOUS_COEFFICIENT = 4.0f;

	//�o������|�C���g
	DirectX::XMFLOAT3 ADVENT_POSITION[4]=
	{
		DirectX::XMFLOAT3(  0,  0,-120),
		DirectX::XMFLOAT3(  0,  0, 120),
		DirectX::XMFLOAT3(-120,  0,  0),
		DirectX::XMFLOAT3( 120,  0,  0),
	};
	//�C�x���g�ŏo������|�C���g
	DirectX::XMFLOAT3 ADVENT_EVENT_POSITION[4] =
	{
		DirectX::XMFLOAT3(100,  0,100),
		DirectX::XMFLOAT3(100,  0, -100),
		DirectX::XMFLOAT3(-100,  0, 100),
		DirectX::XMFLOAT3(-100,  0,  -100),
	};
	
	//�G���̌��j��
	int m_lesserNumScore=0;
	//�G���ȊO�̌��j��
	int m_higherNumScore=0;


};

