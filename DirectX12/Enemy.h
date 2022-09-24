#pragma once

#include"ModelTypeData.h"
#include"Actor.h"
class Enemy:public Actor
{
public:
	Enemy(CollisionTag _tag, bool Alive);
	~Enemy()override;
	//�X�V
	void Update()override;
	//�`��
	void Draw()override;
	//������
	void Init()override;
	//�����蔻�菈��
	void OnCollisionEnter(class Collision* otherCollision)override;
private:
	//���f��
	class PMDModel& m_model;            //  PMD���f���̊Ǘ�
	class EffekseerManager& m_effect;
	float m_speed;
	class Sound& m_sound;
	class SupportJson& m_json;
	 PMDModelType modeltype;
};