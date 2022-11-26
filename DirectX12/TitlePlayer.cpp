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
#include"Time.h"
TitlePlayer::TitlePlayer()
	:m_model(Singleton<PMDModel>::GetInstance())
	, m_controller(Singleton<Controller>::GetInstance())
	, m_camera(Singleton<Camera>::GetInstance())
	,m_position(XMFLOAT3(-90,-30,0))
	,m_rotate(XMFLOAT3(90, 0, 90))
	,m_playerRotate(XMFLOAT3(0, 0, 0))
	, m_cubeRotate(XMFLOAT3(0, 0, 0))
	, m_drawer(Singleton<StringDrawer>::GetInstance())
	,m_timer(new Time())
{

	x = y = 0;
}

TitlePlayer::~TitlePlayer()
{
	delete m_timer;
}

void TitlePlayer::Draw()
{
	

	m_cubeRotate.x += 1;
	m_cubeRotate.y += 1;
	m_cubeRotate.z += 1;

	//XMFLOAT3 _crotate = XMFLOAT3(XMF3Math::DegreeForRadian(m_cubeRotate.x), XMF3Math::DegreeForRadian(m_cubeRotate.y), XMF3Math::DegreeForRadian(m_cubeRotate.z));
	//m_model.Draw(CUBE_POSITION,_crotate , PMDModelType::GroundCube);
	m_playerRotate = XMF3Math::AddXMFLOAT3(m_playerRotate, XMFLOAT3(0, XMF3Math::DegreeForRadian(3),0));

	XMFLOAT3 _rotate = XMFLOAT3(XMF3Math::DegreeForRadian(m_rotate.x), XMF3Math::DegreeForRadian(m_rotate.y), XMF3Math::DegreeForRadian(m_rotate.z));
	m_model.Draw(m_position, XMF3Math::AddXMFLOAT3(_rotate, m_playerRotate), PMDModelType::Player);
	m_model.Draw(m_position, XMF3Math::AddXMFLOAT3(_rotate, m_playerRotate), PMDModelType::PlayerCube);

	m_model.Draw(XMF3Math::AddXMFLOAT3( m_position,XMFLOAT3(code*20,0,0)), _rotate, PMDModelType::LesserEnemy);
	m_model.Draw(XMF3Math::AddXMFLOAT3( m_position, XMFLOAT3(code*30, 0, 0)), _rotate, PMDModelType::LesserEnemy);
	
}

void TitlePlayer::DrawString()
{
	m_drawer.DrawStringBlackAndWhiteForNumber(x, XMFLOAT2(0, 0), 0.5f);
	m_drawer.DrawStringBlackAndWhiteForNumber(y, XMFLOAT2(0, 50), 0.5f);
	m_drawer.DrawStringBlackAndWhiteForNumber(z, XMFLOAT2(0, 100), 0.5f);
}

void TitlePlayer::Update()
{
	
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
