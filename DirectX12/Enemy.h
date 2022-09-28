#pragma once

#include"ModelTypeData.h"
#include"Actor.h"
class Enemy:public Actor
{
public:
	Enemy(CollisionTag _tag, bool m_alive);
	~Enemy()override;
	//�X�V
	void Update();
	//�`��
	void Draw();
	//������
	void Init()override;
	//�����蔻�菈��
	void OnCollisionEnter(class Collision* otherCollision)override;

	const bool IsAlive() { return m_isAlive;}
private:
	//���f��
	class PMDModel& m_model;            //  PMD���f���̊Ǘ�
	class EffekseerManager& m_effect;
	float m_speed;
	class Sound& m_sound;
	class SupportJson& m_json;
	bool m_isAlive;
	 PMDModelType modeltype;
};