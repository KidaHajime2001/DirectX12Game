#include "Title.h"
#include "ModelTypeData.h"
#include "SpriteType.h"
#include"Singleton.h"
#include"Sound.h"
#include"SoundType.h"
#include"Time.h"
#include"TitlePlayer.h"
#include"XMF3Math.h"
#include"JsonDataType.h"
#include"SupportJSON.h"
#include"GameLevel.h"
#include"Camera.h"
#include"StringDrawer.h"
Title::Title(SceneTag _sceneTag)
	:SceneBase(_sceneTag)
	, m_controller(Singleton<Controller>::GetInstance())
	, m_drawer(Singleton<StringDrawer>::GetInstance())
	, m_device(Singleton<D12Device>::GetInstance())
	, m_model(Singleton<PMDModel>::GetInstance())
	, m_sprite((Singleton<SpriteDrawer>::GetInstance()))
	, m_fps(Singleton<Fps>::GetInstance())
	, m_sound(Singleton<Sound>::GetInstance())
	, m_json(Singleton<SupportJson>::GetInstance())
	,m_time(new Time())
	,m_decisionFlag(false)
	,m_buttonState(SelectState::StartButton)
	,m_player(new TitlePlayer())
	,m_testPos(XMFLOAT2(0,665))
	,m_levelNumber(3)
	,m_allSoundVolume(m_sound.GetSonudVolume().x)
	, m_bgmSoundVolume(m_sound.GetSonudVolume().y)
	, m_seSoundVolume(m_sound.GetSonudVolume().z)
	,m_camera(Singleton<Camera>::GetInstance())
{
	m_alphaValue = 1.0f;
	BGMHandle= m_sound.Play(SoundType::TitleBGM,true,true);
	m_camera.Reset();
}

Title::~Title()
{
	delete m_player;
}

void Title::Update()
{
	m_player->Update();
	if (m_controller.IsPushEnter(ButtonName::GAMEPAD_A))
	{
		PushAButtonState(m_buttonState);
	}
	if (m_controller.IsPushEnter(ButtonName::GAMEPAD_B))
	{
		PushBButtonState(m_buttonState);
	}
	if (m_controller.IsPushEnter(ButtonName::GAMEPAD_UP))
	{
		PushUpButtonState(m_buttonState);
	}
	if (m_controller.IsPushEnter(ButtonName::GAMEPAD_DOWN))
	{
		PushDownButtonState(m_buttonState);
	}
	if (m_controller.IsPushEnter(ButtonName::GAMEPAD_RIGHT))
	{
		PushRightButtonState(m_buttonState);
	}
	if (m_controller.IsPushEnter(ButtonName::GAMEPAD_LEFT))
	{
		PushLeftButtonState(m_buttonState);
	}
	if (m_time->CheakTime()&& m_decisionFlag)
	{
		m_nextSceneFlag = true;
	}
	SetVolume();
	ChangeImagealpha();
}

void Title::Draw()
{

	m_player->Draw();
	m_sprite.Draw(SpriteType::ControllTitle, XMFLOAT2(0, 0));
}

void Title::DrawLine()
{
}

void Title::DrawString()
{
	//m_player->DrawString();
	if (m_controller.IsPress(ButtonName::GAMEPAD_RIGHT))
	{
		m_testPos.x++;
	}
	if (m_controller.IsPress(ButtonName::GAMEPAD_LEFT))
	{
		m_testPos.x--;
	}
	if (m_controller.IsPress(ButtonName::GAMEPAD_UP))
	{
		m_testPos.y++;
	}
	if (m_controller.IsPress(ButtonName::GAMEPAD_DOWN))
	{
		m_testPos.y--;
	}
	//m_drawer.DrawStringBlackAndWhiteForNumber(gameLevel, XMFLOAT2(300, 85), 1.0f);

	//m_drawer.DrawStringTitle("Select : CrossKey + A", m_testPos, 1.0f, m_alphaValue, Colors::GreenYellow);
	switch (m_buttonState)
	{
	case SelectState::StartButton:

		m_drawer.DrawStringTitle(" Start",	START_POSITION,		1.3f,	m_alphaValue,	Colors::GreenYellow);
		m_drawer.DrawStringTitle("Option",	OPTION_POSITION,	1.3f,	1.0f,			Colors::Green);
		m_drawer.DrawStringTitle("Credit", CREDIT_POSITION,		1.3f, 1.0f, Colors::Green);

		break;
	case SelectState::OptionButton:

		m_drawer.DrawStringTitle("Start",	START_POSITION,		1.3f,	1.0f,			Colors::Green);
		m_drawer.DrawStringTitle(" Option",	OPTION_POSITION,	1.3f,	m_alphaValue,	Colors::GreenYellow);
		m_drawer.DrawStringTitle("Credit", CREDIT_POSITION,		1.3f,	1.0f,			Colors::Green);
		break;
	case SelectState::CreditButton:
		m_drawer.DrawStringTitle("Start", START_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitle("Option", OPTION_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitle(" Credit", CREDIT_POSITION, 1.3f, m_alphaValue, Colors::GreenYellow);
		break;
	case SelectState::ModeToLevel:

		m_drawer.DrawStringTitle("Start",			START_POSITION,			1.3f, 1.0f,			Colors::Green);
		m_drawer.DrawStringTitle("[            ]",	START_SELECT_POSITION,	1.3f, 1.0f,			Colors::Green);
		m_drawer.DrawStringTitle("->     Normal",		NORMAL_POSITION,		1.3f, m_alphaValue,	Colors::GreenYellow);/*
		m_drawer.DrawStringTitle("->    Endless",		ENDLESS_POSITION,		1.3f, 1.0f,			Colors::Green);*/

		break;
	/*case SelectState::ModeToEndless:

		m_drawer.DrawStringTitle("Start",			START_POSITION,			1.3f, 1.0f,			Colors::Green);
		m_drawer.DrawStringTitle("[            ]",	START_SELECT_POSITION,	1.3f, 1.0f,			Colors::Green);
		m_drawer.DrawStringTitle("->    Normal",		NORMAL_POSITION,		1.3f, 1.0f,			Colors::Green);
		m_drawer.DrawStringTitle("->     Endless",		ENDLESS_POSITION,		1.3f, m_alphaValue,	Colors::GreenYellow);

		break;*/

	case SelectState::SelectLevel:

		m_drawer.DrawStringTitle("Start",				START_POSITION,			1.3f,	1.0f,			Colors::Green);
		m_drawer.DrawStringTitle("[            ]",		START_SELECT_POSITION,	1.3f,	1.0f,			Colors::Green);
		m_drawer.DrawStringTitle("->    Normal",		NORMAL_POSITION,		1.3f,	1.0f,			Colors::Green);
		m_drawer.DrawStringTitle("[              ]",	NORMAL_SELECT_POSITION, 1.3f,	1.0f,			Colors::Green);
		m_drawer.DrawStringTitle("->    LEVEL <    >",	LEVEL_POSITION,			1.3f,	m_alphaValue,	Colors::GreenYellow);
		m_drawer.DrawStringTitleForNumber(m_levelNumber,LEVEL_NUMBER_POSITION,	1.3f,	m_alphaValue,	Colors::GreenYellow);

		break;
	case SelectState::SoundOptionAll:

		m_drawer.DrawStringTitle("->    GameSound <    >", OPTION_ALL_POSITION, 1.3f, m_alphaValue, Colors::GreenYellow);
		m_drawer.DrawStringTitle("->    BgmSound   <    >", OPTION_BGM_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitle("->    SeSound     <    >", OPTION_SE_POSITION, 1.3f, 1.0f, Colors::Green);

		m_drawer.DrawStringTitleForNumber(m_allSoundVolume, OPTION_ALL_NUMBER_POSITION, 1.3f, m_alphaValue, Colors::GreenYellow);
		m_drawer.DrawStringTitleForNumber(m_bgmSoundVolume, OPTION_BGM_NUMBER_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitleForNumber(m_seSoundVolume,  OPTION_SE_NUMBER_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitle("Option", OPTION_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitle("[             ]", OPTION_SELECT_POSITION, 1.3f, 1.0f, Colors::Green);
		break;
	case SelectState::SoundOptionBgm:

		m_drawer.DrawStringTitle("->    GameSound <    >", OPTION_ALL_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitle("->    BgmSound   <    >", OPTION_BGM_POSITION, 1.3f, m_alphaValue, Colors::GreenYellow);
		m_drawer.DrawStringTitle("->    SeSound     <    >", OPTION_SE_POSITION, 1.3f, 1.0f, Colors::Green);

		m_drawer.DrawStringTitleForNumber(m_allSoundVolume, OPTION_ALL_NUMBER_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitleForNumber(m_bgmSoundVolume, OPTION_BGM_NUMBER_POSITION, 1.3f, m_alphaValue, Colors::GreenYellow);
		m_drawer.DrawStringTitleForNumber(m_seSoundVolume, OPTION_SE_NUMBER_POSITION, 1.3f, 1.0f, Colors::Green);


		m_drawer.DrawStringTitle("Option", OPTION_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitle("[             ]", OPTION_SELECT_POSITION, 1.3f, 1.0f, Colors::Green);
		break;
	case SelectState::SoundOptionSe:

		m_drawer.DrawStringTitle("->    GameSound <    >", OPTION_ALL_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitle("->    BgmSound   <    >", OPTION_BGM_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitle("->    SeSound     <    >", OPTION_SE_POSITION, 1.3f, m_alphaValue, Colors::GreenYellow);

		m_drawer.DrawStringTitleForNumber(m_allSoundVolume, OPTION_ALL_NUMBER_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitleForNumber(m_bgmSoundVolume, OPTION_BGM_NUMBER_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitleForNumber(m_seSoundVolume, OPTION_SE_NUMBER_POSITION, 1.3f, m_alphaValue, Colors::GreenYellow);
		m_drawer.DrawStringTitle("Option", OPTION_POSITION, 1.3f, 1.0f, Colors::Green);
		m_drawer.DrawStringTitle("[             ]", OPTION_SELECT_POSITION, 1.3f, 1.0f, Colors::Green);
		break;

	default:
		break;
	}

	
}

void Title::DrawBackGround()
{
	//  NOTE: ‰æ–Ê‚ÌƒTƒCƒY‚É‡‚í‚¹‚Äì‚Á‚Ä‚¢‚é‚Ì‚ÅÀ•W‚Í0
	XMFLOAT2 pos = { 0,0 };
	//  ”wŒi•`‰æ
	m_sprite.Draw(SpriteType::TitleBack, pos);

}

void Title::ChangeImagealpha()
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

void Title::PlayStart()
{
	m_time->SetTimer(1);
	m_sound.Stop(SoundType::TitleBGM, BGMHandle);
	m_sound.Play(SoundType::SelectSE, false, true);
	m_decisionFlag = true;
	Code = 10.0f;
	m_alphaValue = 0;
	m_gameLevel->SetGameLevel(m_levelNumber);
}

void Title::PushAButtonState(SelectState _state)
{
	switch (_state)
	{
	case Title::SelectState::StartButton:
		m_buttonState = SelectState::ModeToLevel;
		break;
	case Title::SelectState::OptionButton:
		m_buttonState = SelectState::SoundOptionAll;
		break;
	case Title::SelectState::ModeToLevel:
		m_buttonState = SelectState::SelectLevel;
		break;
	case Title::SelectState::CreditButton:
		PlayStart();
		m_nextSceneIndex = (int)NextScene::Credit;
		break;
	case Title::SelectState::SelectLevel:
		PlayStart();
		m_nextSceneIndex = (int)NextScene::Game;
		break;
	default:
		break;
	}
}

void Title::PushBButtonState(SelectState _state)
{
	switch (_state)
	{
	case Title::SelectState::StartButton:
		break;
	case Title::SelectState::OptionButton:

		break;
	case Title::SelectState::ModeToLevel:
		m_buttonState = SelectState::StartButton;
		break;
	case Title::SelectState::SelectLevel:
		m_buttonState = SelectState::ModeToLevel;
		break;
	case Title::SelectState::SoundOptionAll:
		m_buttonState = SelectState::OptionButton;
		
		break;
	case Title::SelectState::SoundOptionBgm:
		m_buttonState = SelectState::OptionButton;
		break;
	case Title::SelectState::SoundOptionSe:
		m_buttonState = SelectState::OptionButton;
		break;
	default:
		break;
	}
}

void Title::PushUpButtonState(SelectState _state)
{
	switch (_state)
	{
	case Title::SelectState::OptionButton:
		m_buttonState = SelectState::StartButton;
		break;
	case Title::SelectState::CreditButton:
		m_buttonState = SelectState::OptionButton;
		break;
	//case Title::SelectState::ModeToEndless:
	//	m_buttonState = SelectState::ModeToLevel;
	//	break;
	case Title::SelectState::SoundOptionBgm:
		m_buttonState = SelectState::SoundOptionAll;
		break;
	case Title::SelectState::SoundOptionSe:
		m_buttonState = SelectState::SoundOptionBgm;
		break;
	default:
		break;
	}
}

void Title::PushDownButtonState(SelectState _state)
{
	switch (_state)
	{
	case Title::SelectState::StartButton:
		m_buttonState = SelectState::OptionButton;
		break;
	case Title::SelectState::OptionButton:
		m_buttonState = SelectState::CreditButton;
		break;
	//case Title::SelectState::ModeToLevel:
	//	m_buttonState = SelectState::ModeToEndless;
	//	break;
	case Title::SelectState::SoundOptionAll:
		m_buttonState = SelectState::SoundOptionBgm;
		break;
	case Title::SelectState::SoundOptionBgm:
		m_buttonState = SelectState::SoundOptionSe;
		break;
	default:
		break;
	}
}

void Title::PushLeftButtonState(SelectState _state)
{
	switch (_state)
	{
	case Title::SelectState::OptionButton:
		break;
	case Title::SelectState::SelectLevel:
		if (m_levelNumber>1)
		{
			m_levelNumber--;
		}
		
		break;
	case Title::SelectState::SoundOptionAll:
		if (m_allSoundVolume > 0)
		{
			m_allSoundVolume--;
		}
		break;
	case Title::SelectState::SoundOptionBgm:
		if (m_bgmSoundVolume > 0)
		{
			m_bgmSoundVolume--;
		}
		break;
	case Title::SelectState::SoundOptionSe:
		if (m_seSoundVolume > 0)
		{
			m_seSoundVolume--;
		}
		break;
	default:
		break;
	}
}


void Title::PushRightButtonState(SelectState _state)
{
	switch (_state)
	{
	case Title::SelectState::OptionButton:
		break;
	case Title::SelectState::SelectLevel:
		if (m_levelNumber < 9)
		{
			m_levelNumber++;
		}
		
		break;
	case Title::SelectState::SoundOptionAll:
		if (m_allSoundVolume < 9)
		{
			m_allSoundVolume++;
		}
		break;
	case Title::SelectState::SoundOptionBgm:
		if (m_bgmSoundVolume < 9)
		{
			m_bgmSoundVolume++;
		}
		break;
	case Title::SelectState::SoundOptionSe:
		if (m_seSoundVolume < 9)
		{
			m_seSoundVolume++;
		}
		break;
	default:
		break;
	}
}

void Title::SetVolume()
{
	float all = m_allSoundVolume;
	float bgm = m_bgmSoundVolume;
	float se  = m_seSoundVolume;
	m_sound.SetSoundVolume(all,bgm,se);
}



