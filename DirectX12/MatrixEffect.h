#pragma once
#include"DirectXHelpers.h"
#include<unordered_map>
#include"SpriteType.h"
class MatrixEffect
{
public:
	MatrixEffect(int matSize);
	~MatrixEffect();
	//画面を上から下に落ちていく
	void Update();
	//
	void Draw();
private:
	void RandomSetting();
	void ClearMatrix();
	
	//画像濃度
	float m_effectConcentration = 1.0f;
	
	//文字の大きさ　0.1あたり
	const int MATRIX_SIZE=50;
	
	//位置
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
