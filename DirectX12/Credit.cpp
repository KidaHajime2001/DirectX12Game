#include "Credit.h"
#include "SpriteType.h"
#include"Singleton.h"
#include"Sound.h"
#include"SoundType.h"
#include"StringDrawer.h"
#include"SpriteDrawer.h"
#include"Controller.h"
Credit::Credit(SceneTag _sceneTag)
	:SceneBase(_sceneTag)
,m_controller(Singleton<Controller>::GetInstance())
, m_drawer(Singleton<StringDrawer>::GetInstance())
, m_sprite((Singleton<SpriteDrawer>::GetInstance()))
, m_sound(Singleton<Sound>::GetInstance())
{
}

Credit::~Credit()
{
}

void Credit::Draw()
{
	m_sprite.Draw(SpriteType::Credit,XMFLOAT2(0,0));
	m_sprite.Draw(SpriteType::ControllCredit, XMFLOAT2(0, 0),1.0f,m_sprite.GetColorWithalpha(m_alphaValue));
}

void Credit::Update()
{
	if (m_controller.IsPushEnter(ButtonName::GAMEPAD_A))
	{
		m_nextSceneFlag = true;
	}
	ChangeImageAlpha();
}

void Credit::DrawString()
{/*
	m_drawer.DrawStringTitle("Press A",XMFLOAT2(1600,900),1.5f,m_alphaValue,Colors::Green);*/
}

void Credit::ChangeImageAlpha()
{
	if (m_decisionFlag)
	{

		if (m_alphaValue >= DefaultalphaMax)
		{
			Code = -10.0f;
		}
		if (m_alphaValue <= ChangedalphaMin)
		{
			Code = 10.0f;
		}
	}
	else
	{
		if (m_alphaValue >= DefaultalphaMax)
		{
			Code = -1.0f;
		}
		if (m_alphaValue <= DefaultalphaMin)
		{
			Code = 1.0f;
		}
	}


	m_alphaValue += DELTA * Code;
}
