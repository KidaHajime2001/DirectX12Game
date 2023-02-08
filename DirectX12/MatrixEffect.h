#pragma once
#include"DirectXHelpers.h"
#include<unordered_map>
#include"SpriteType.h"
class MatrixEffect
{
public:
	MatrixEffect(int matSize);
	~MatrixEffect();
	//��ʂ��ォ�牺�ɗ����Ă���
	void Update();
	//
	void Draw();
private:
	void RandomSetting();
	void ClearMatrix();
	
	//�摜�Z�x
	float m_effectConcentration = 1.0f;
	
	//�����̑傫���@0.1������
	const int MATRIX_SIZE=50;
	
	//�ʒu
	DirectX::XMFLOAT2 m_position;
	std::vector<bool> m_drawType;
	class SpriteDrawer& m_sprite;

	std::unordered_map<int, SpriteType> m_spriteMap;

	int randTiming;
	int m_randSize = 1;
	int type0 = 0;
	int type1 = 1;
	class Time* m_timer;
};
