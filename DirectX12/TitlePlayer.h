#pragma once

#include <DirectXTex.h>
class TitlePlayer
{
public:
	TitlePlayer();
	~TitlePlayer();
	void Draw();
	void DrawString();
	void Update();
private:
	//ƒ‚ƒfƒ‹
	class PMDModel& m_model;            //  PMDƒ‚ƒfƒ‹‚ÌŠÇ—
	class Controller& m_controller;
	class Camera& m_camera;
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotate;
	class StringDrawer& m_drawer;
	bool Goleft=false;
	int code=1;
};
