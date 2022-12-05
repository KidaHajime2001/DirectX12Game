#include "LesserEnemy.h"
#include"PmdModel.h"
#include"Collision.h"
#include"Time.h"
#include"XMF3Math.h"
#include"ModelTypeData.h"
#include"Sound.h"
#include"SoundType.h"
LesserEnemy::LesserEnemy(CollisionTag _tag, bool m_alive)
	:EnemyBase(_tag,m_alive)
	,m_timer(new Time())
{
	//�����蔻��
	//�O���f�[�^���玝���Ă�����
	m_radiusData = 2;
	m_param.mCollision->m_data.radius = m_radiusData;
	//�`�悷��f�[�^
	m_modeltype = PMDModelType::LesserEnemy;
	//�I�u�W�F�N�g�v�[���o�^���Ĉ�U�����蔻���OFF
	m_param.mCollision->m_isValidity = false;
	
	//�ړ����x
	//�O���f�[�^���玝���Ă�����
	m_speed = 0.3f;
	m_enemyType = EnemyType::LesserEnemy;
	
}
LesserEnemy::~LesserEnemy()
{
	delete m_timer;
}

void LesserEnemy::Init()
{
	//�I�u�W�F�N�g�v�[���݌v�̈׎g���܂킹��悤�A��{�I�Ȑݒ������������
	//�����t���O��ON
	//�����蔻���ON
	//�v���C���[�ɓ������Ă��邩�̃t���O��OFF
	//��������o������̂ł����������ʂȏ���
	m_param.mCollision->m_isValidity = true;
	m_isAlive = true;
	auto randPos=XMFLOAT3(rand()%10-10, 0, rand() % 10 - 10);
	m_param.pos = randPos;
}

void LesserEnemy::Update(const DirectX::XMFLOAT3 _targetPos)
{
	//�����Ă����
	if (m_isAlive)
	{
		if (m_enemyState == EnemyState::wait)
		{
			WaitUpdate(_targetPos);
		}
		if (m_enemyState == EnemyState::move)
		{
			MoveUpdate(_targetPos);
		}
	}



}


void LesserEnemy::CollisionOriginal(Collision* otherCollision)
{
	if (otherCollision->GetTag()==CollisionTag::PlayerBullet)
	{
		//���S���o
		m_effect.PlayEffect(EffectType::DefeatLesserEnemy, GetPosition(), false);
		m_sound.Play(SoundType::DefeatLesserEnemySE, false, true);

		//�����蔻��OFF
		m_param.mCollision->m_isValidity = false;
		//�����t���OOFF
		m_isAlive = false;
	}
}


void LesserEnemy::WaitUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//�ҋ@���ԓ�b
	m_timer->SetTimer(2);
	//���Ԃ������玟��ԂɑJ��
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::move;
	}
}

void LesserEnemy::MoveUpdate(const DirectX::XMFLOAT3 _targetPos)
{
	//�v���C���[�Ǝ����Ƃ̋������Z�o
	auto diff = XMF3Math::SubXMFLOAT3(_targetPos,m_param.pos);
	//����
	m_nowDirection = diff;
	//�ړ��x�N�g���쐬
	diff = XMF3Math::SetMagnitude(diff,m_speed);
	m_param.pos = XMF3Math::AddXMFLOAT3(m_param.pos,diff);
	//�ܕb�Ԉړ�
	m_timer->SetTimer(5);
	//�ҋ@��ԂɑJ��
	if (m_timer->CheakTime())
	{
		m_enemyState = EnemyState::wait;
	}
}
