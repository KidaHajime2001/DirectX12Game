#include "Title.h"
#include "ModelTypeData.h"
#include "SpriteType.h"
#include"Singleton.h"
#include"Sound.h"
#include"SoundType.h"
#include"Time.h"
Title::Title(SceneTag _sceneTag)
	:SceneBase(_sceneTag)
	, m_controller(Singleton<Controller>::GetInstance())
	, m_drawer(Singleton<StringDrawer>::GetInstance())
	, m_device(Singleton<D12Device>::GetInstance())
	, m_model(Singleton<PMDModel>::GetInstance())
	, m_sprite((Singleton<SpriteDrawer>::GetInstance()))
	, m_fps(Singleton<Fps>::GetInstance())
	, m_sound(Singleton<Sound>::GetInstance())
	,m_time(new Time())
	,m_decisionFlag(false)
{
	m_alfaValue = 1.0f;
	BGMHandle= m_sound.Play(SoundType::TitleBGM,true,true);
}

Title::~Title()
{
}

void Title::Update()
{
	if (m_controller.IsPushEnter(ButtonName::GAMEPAD_A))
	{
		m_time->SetTimer(1);
		m_sound.Stop(SoundType::TitleBGM,BGMHandle);
		m_sound.Play(SoundType::SelectSE,false,true);
		m_decisionFlag = true;
		Code = 10.0f;
		m_alfaValue = 0;
		
	}
	if (m_time->CheakTime()&& m_decisionFlag)
	{
		m_nextSceneFlag = true;
	}
	ChangeImageAlfa();
}

void Title::Draw()
{/*
	m_model.Draw(XMFLOAT3(0, 0, 0), 0, PMDModelType::Ground);*/
	//  NOTE: ‰æ–Ê‚ÌƒTƒCƒY‚É‡‚í‚¹‚Äì‚Á‚Ä‚¢‚é‚Ì‚ÅÀ•W‚Í0
	XMFLOAT2 pos = { 0,0 };
	//  ”wŒi•`‰æ
	m_sprite.Draw(SpriteType::TitleBack, pos);
	m_sprite.Draw(SpriteType::TitleText, pos);
	m_sprite.Draw(SpriteType::TitleStart,pos, 1.0f, m_sprite.GetColorWithAlfa(m_alfaValue));
	
}

void Title::ChangeImageAlfa()
{
	
	if (m_decisionFlag)
	{
		
		if (m_alfaValue >= DefaultAlfaMax)
		{
			Code = -10.0f;
		}
		if (m_alfaValue <= ChangedAlfaMin)
		{
			Code = 10.0f;
		}
	}
	else
	{
		if (m_alfaValue >= DefaultAlfaMax)
		{
			Code = -1.0f;
		}
		if (m_alfaValue <= DefaultAlfaMin)
		{
			Code = 1.0f;
		}
	}


	m_alfaValue += DELTA * Code;
}
