#pragma once
#include<DirectXTex.h>
class ScoreUI
{
public:
	ScoreUI();
	~ScoreUI();
	void DrawString();
	void DrawSprite();
	void Update();

private:
	class SpriteDrawer& m_sprite;
	class StringDrawer& m_drawer; 
	class Controller& m_controller;
	int Score;
	const int POINT_LESSER=10;
	const int POINT_HIGHER=500; 
	DirectX::XMFLOAT2 m_pos ;
};
