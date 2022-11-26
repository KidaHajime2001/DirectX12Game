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
	float x, y,z;
	//���f��
	class StringDrawer& m_drawer;
	class PMDModel& m_model;            //  PMD���f���̊Ǘ�
	class Controller& m_controller;
	class Camera& m_camera;
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotate;
	DirectX::XMFLOAT3 m_playerRotate;
	const DirectX::XMFLOAT3 CUBE_POSITION = { 120, -40, 350 };
	DirectX::XMFLOAT3 m_cubeRotate;
	class Time* m_timer;
	bool Goleft=false;
	int code=1;
};
