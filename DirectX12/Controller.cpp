#include "Controller.h"
#include<iostream>
#include"Singleton.h"
#include"StringDrawer.h"
#include<Windows.h>
#include"EnumItr.h"
//https://docs.microsoft.com/ja-jp/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN
using namespace std;

void Controller::Update()
{
	//  列挙型PMDModelTypeのイテレータを作成
	typedef EnumIterator<ButtonName, ButtonName::GAMEPAD_UP, ButtonName::GAMEPAD_Y> typeItr;
	XInputGetState(0, &padState);
	//前フレームの状態確保
	for (auto itr : typeItr())
	{
		button[static_cast<int>(itr)].beforeState = button[static_cast<int>(itr)].State;
	}
	
	//更新
	for (auto itr : typeItr())
	{
		if (GetControllerButtonState(itr))
		{
			if (button[static_cast<int>(itr)].beforeState==InputState::NoPush)
			{
				button[static_cast<int>(itr)].State = InputState::PushEnter;
			}
			if (button[static_cast<int>(itr)].beforeState == InputState::PushEnter)
			{
				button[static_cast<int>(itr)].State = InputState::Press;
			}
		}
		else
		{
			if (button[static_cast<int>(itr)].beforeState == InputState::Press)
			{
				button[static_cast<int>(itr)].State = InputState::PushExit;
			}
			if (button[static_cast<int>(itr)].beforeState == InputState::PushExit)
			{
				button[static_cast<int>(itr)].State = InputState::NoPush;
			}
		}
	}

	
	

	//フォント関連の描写

}

void Controller::ShowControllerState()
{
	m_drawer.DrawStringBlackAndWhite("sThumbLX", XMFLOAT2(0, 0)		, 0.5f);
	m_drawer.DrawStringBlackAndWhite("sThumbLY", XMFLOAT2(0, 50)		, 0.5f);
	m_drawer.DrawStringBlackAndWhite("sThumbRX", XMFLOAT2(0, 100)		, 0.5f);
	m_drawer.DrawStringBlackAndWhite("sThumbRY", XMFLOAT2(0, 150)		, 0.5f);
	m_drawer.DrawStringBlackAndWhite("bLeftTrigger", XMFLOAT2(0, 200)	, 0.5f);
	m_drawer.DrawStringBlackAndWhite("bRightTrigges", XMFLOAT2(0, 250)	, 0.5f);

	m_drawer.DrawStringBlackAndWhiteForFewNumber(GetLeftStickInput().x, XMFLOAT2(300, 0), 0.5f);
	m_drawer.DrawStringBlackAndWhiteForFewNumber(GetLeftStickInput().y, XMFLOAT2(300, 50), 0.5f);
	m_drawer.DrawStringBlackAndWhiteForFewNumber(GetContorollerState().Gamepad.sThumbRX, XMFLOAT2(300, 100), 0.5f);
	m_drawer.DrawStringBlackAndWhiteForFewNumber(GetContorollerState().Gamepad.sThumbRY, XMFLOAT2(300, 150), 0.5f);
	m_drawer.DrawStringBlackAndWhiteForFewNumber(GetContorollerState().Gamepad.bLeftTrigger, XMFLOAT2(300, 200), 0.5f);
	m_drawer.DrawStringBlackAndWhiteForFewNumber(GetContorollerState().Gamepad.bRightTrigger, XMFLOAT2(300, 250), 0.5f);
	//  列挙型PMDModelTypeのイテレータを作成
	typedef EnumIterator<ButtonName, ButtonName::GAMEPAD_UP, ButtonName::GAMEPAD_Y> typeItr;

	m_drawer.DrawStringBlackAndWhite("GAMEPAD_UP",				XMFLOAT2(600,0),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_DOWN",			XMFLOAT2(600,50),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_LEFT",			XMFLOAT2(600,100),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_RIGHT",			XMFLOAT2(600,150),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_START",			XMFLOAT2(600,200),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_BACK",			XMFLOAT2(600,250),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_LEFT_THUMB",		XMFLOAT2(600,300),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_RIGHT_THUMB",	XMFLOAT2(600,350),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_LEFT_SHOULDER",	XMFLOAT2(600,400),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_RIGHT_SHOULDER",	XMFLOAT2(600,450),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_A",				XMFLOAT2(600,500),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_B",				XMFLOAT2(600,550),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_X",				XMFLOAT2(600,600),0.5f);
	m_drawer.DrawStringBlackAndWhite("GAMEPAD_Y",				XMFLOAT2(600,650),0.5f);

	int i = 0;
	for (auto itr : typeItr())	
	{
		int StatusNum=-1;
		switch (button[static_cast<int>(itr)].State)
		{
		case InputState::NoPush:
			StatusNum = 0;
			break;
		case InputState::PushEnter:
			StatusNum = 1;
			break;
		case InputState::Press:
			StatusNum = 2;
			break;
		case InputState::PushExit:
			StatusNum = 3;
			break;
		}
		m_drawer.DrawStringBlackAndWhiteForFewNumber(StatusNum, XMFLOAT2(900, 0+(i*50)), 0.5f);
		i++;
	}

}

const bool Controller::CheckSubInput(ButtonName bN)
{
	
	
	return (GetKeyState(SubInputKeyBord[static_cast<int>(bN)]) & 0x8000);
}

const bool Controller::GetControllerButtonState(ButtonName bN)
{

	if (padState.Gamepad.wButtons & button[static_cast<int>(bN)].Data|| CheckSubInput(bN))
	{
		return true;
	}
	return false;
}

const bool Controller::IsPushEnter(ButtonName bN)
{
	if (button[static_cast<int>(bN)].State == InputState::PushEnter)
	{
		return true;
	}
	return false;
}

const bool Controller::IsPress(ButtonName bN)
{
	if (button[static_cast<int>(bN)].State == InputState::Press)
	{
		return true;
	}
	return false;
}

const bool Controller::IsRelease(ButtonName bN)
{
	if (button[static_cast<int>(bN)].State==InputState::PushExit)
	{
		return true;
	}
	return false;
}

const DirectX::XMFLOAT2 Controller::GetRightStickInput()
{
	float x = (float)(padState.Gamepad.sThumbRX / INPUT_MAX);
	float y = (float)(padState.Gamepad.sThumbRY / INPUT_MAX);
	return DirectX::XMFLOAT2(x,y);
}

const DirectX::XMFLOAT2 Controller::GetLeftStickInput()
{
	float x = (float)(padState.Gamepad.sThumbLX / INPUT_MAX);
	float y = (float)(padState.Gamepad.sThumbLY / INPUT_MAX);
	return DirectX::XMFLOAT2(x, y);
}

const float Controller::GetTiggerInputL()
{
	float x = (float)(padState.Gamepad.bLeftTrigger / TRIGGER_INPUT_MAX);

	return x;
}

const float Controller::GetTiggerInputR()
{
	
	float x = (float)(padState.Gamepad.bRightTrigger / TRIGGER_INPUT_MAX);
	return x;
}




Controller::~Controller()
{

}

Controller::Controller()
	:m_drawer(Singleton<StringDrawer>::GetInstance())
{
	// 0番のパッドが接続されているかをチェックし、パッド状態を出力
	bool isPad0 = XInputGetState(0, &padState) == ERROR_SUCCESS;;
	if (isPad0)
	{
		OutputDebugString("Controller successfully connected.\n");
	}
	else
	{
		OutputDebugString("Controller connection failed.\n");
	}
	int Binarynumber = 1;

	button[static_cast<int>(ButtonName::GAMEPAD_UP)]    =			 {XINPUT_GAMEPAD_DPAD_UP		,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_DOWN)] = { XINPUT_GAMEPAD_DPAD_DOWN		,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_LEFT)] = { XINPUT_GAMEPAD_DPAD_LEFT		,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_RIGHT)] = { XINPUT_GAMEPAD_DPAD_RIGHT		,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_START)] = { XINPUT_GAMEPAD_START			,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_BACK)] = { XINPUT_GAMEPAD_BACK			,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_LEFT_THUMB)] = { XINPUT_GAMEPAD_LEFT_THUMB		,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_RIGHT_THUMB)] = { XINPUT_GAMEPAD_RIGHT_THUMB	,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_LEFT_SHOULDER)] = { XINPUT_GAMEPAD_LEFT_SHOULDER	,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_RIGHT_SHOULDER)] = { XINPUT_GAMEPAD_RIGHT_SHOULDER	,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_A)] = { XINPUT_GAMEPAD_A				,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_B)] = { XINPUT_GAMEPAD_B				,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_X)] = { XINPUT_GAMEPAD_X				,InputState::NoPush,InputState::NoPush };
	button[static_cast<int>(ButtonName::GAMEPAD_Y)] = { XINPUT_GAMEPAD_Y				,InputState::NoPush,InputState::NoPush };

	
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_UP)]				= VK_UP;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_DOWN)]				= VK_DOWN;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_LEFT)]				= VK_LEFT;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_RIGHT)]			= VK_RIGHT;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_START)]			= VK_TAB;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_A)]				= VK_RETURN;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_START)]			= VK_ESCAPE;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_RIGHT_SHOULDER)] =   VK_RSHIFT;
		/*
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_BACK)]				= ;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_LEFT_THUMB)]		= ;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_RIGHT_THUMB)]		=;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_LEFT_SHOULDER)]	=;
	
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_A)]				= 0x57;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_B)]				=;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_X)]				=;
	SubInputKeyBord[static_cast<int>(ButtonName::GAMEPAD_Y)]				=;*/










}
