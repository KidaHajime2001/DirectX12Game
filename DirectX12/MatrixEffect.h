#pragma once
#include"DirectXHelpers.h"
#include<unordered_map>
#include"SpriteType.h"
class MatrixEffect
{
public:
	MatrixEffect(int matSize);
	~MatrixEffect();
	//‰æ–Ê‚ğã‚©‚ç‰º‚É—‚¿‚Ä‚¢‚­
	void Update();
	//
	void Draw();
private:
	void RandomSetting();
	void ClearMatrix();
	
	//‰æ‘œ”Z“x
	float m_effectConcentration = 1.0f;
	
	//•¶š‚Ì‘å‚«‚³@0.1‚ ‚½‚è
	const int MATRIX_SIZE=50;
	
	//ˆÊ’u
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
