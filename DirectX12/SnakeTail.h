#pragma once
#include"Actor.h"

#include"ModelTypeData.h"
class SnakeTail: public Actor
{
public:
	SnakeTail(CollisionTag _tag, bool m_alive, DirectX::XMFLOAT3 _nowDirection);
	virtual ~SnakeTail();
	//������
	void Init();
	void Update(DirectX::XMFLOAT3 _frontPos, DirectX::XMFLOAT3 _frontDirection);
	void Draw();
	//�����蔻�菈��
	void OnCollisionEnter(class Collision* otherCollision);
	void SetVisible(bool _isVisible);
private:
	//�����t���O
	bool m_isAlive;
	//����
	DirectX::XMFLOAT3 m_nowDirection;
	//�����蔻��̉��u��
	float m_radiusData=2;
	//���f��
	class PMDModel& m_model;            //  PMD���f���̊Ǘ�
	PMDModelType m_modeltype;			//�@PMD���f���̃^�C�v
	bool m_isVisible;
};