#include "TitlePlayer.h"
#include"Singleton.h"
#include"PmdModel.h"
#include"PmdDrawer.h"
#include"Controller.h"
#include"ModelTypeData.h"
#include"Camera.h"
#include"XMF3Math.h"
#include"SpriteDrawer.h"
#include"StringDrawer.h"
TitlePlayer::TitlePlayer()
	:m_model(Singleton<PMDModel>::GetInstance())
	, m_controller(Singleton<Controller>::GetInstance())
	, m_camera(Singleton<Camera>::GetInstance())
	,m_position(XMFLOAT3(-90,-30,0))
	,m_rotate(XMFLOAT3(90, 0, 90))
	, m_drawer(Singleton<StringDrawer>::GetInstance())
{
	
}

TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::Draw()
{/*
	m_camera.TitleSetting();*/
	XMFLOAT3 _rotate = XMFLOAT3(XMF3Math::DegreeForRadian(m_rotate.x), XMF3Math::DegreeForRadian(m_rotate.y), XMF3Math::DegreeForRadian(m_rotate.z));
	m_model.Draw(m_position,_rotate, PMDModelType::Player);
	m_model.Draw(m_position, _rotate, PMDModelType::PlayerCube);

	m_model.Draw(XMF3Math::AddXMFLOAT3( m_position,XMFLOAT3(code*20,0,0)), _rotate, PMDModelType::LesserEnemy);
	m_model.Draw(XMF3Math::AddXMFLOAT3(m_position, XMFLOAT3(code*30, 0, 0)), _rotate, PMDModelType::LesserEnemy);
	
}

void TitlePlayer::DrawString()
{
	m_drawer.DrawStringBlackAndYellowForNumber(m_position.x, XMFLOAT2(0, 0), 0.5f);
	m_drawer.DrawStringBlackAndYellowForNumber(m_position.y, XMFLOAT2(0, 50), 0.5f);
	m_drawer.DrawStringBlackAndYellowForNumber(m_position.z, XMFLOAT2(0, 100), 0.5f);
}

void TitlePlayer::Update()
{
	/*if (m_position.x >= 100)
	{
		Goleft = false;
	}*/
	if (m_position.x >= 100 && !Goleft)
	{
		Goleft = true;
		code = -1;
		m_position.y = -30;
		m_rotate = XMFLOAT3(90, 0, -90);
	}
	if (m_position.x <= -100 && Goleft)
	{
		Goleft = false;
		code =  1;
		m_position.y = 30;
		m_rotate = XMFLOAT3(90, 0, 90);
	}
	m_position.x += code;
	
}
