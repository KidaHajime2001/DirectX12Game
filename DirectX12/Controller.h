#pragma once
#include <Windows.h>
#include <Xinput.h>
#include<string>
#include<map>
#pragma comment (lib, "xinput.lib")
#include"DirectXTex.h"
#define BUTTON_TOTAL 14
enum class ButtonName
{
	GAMEPAD_UP,
	GAMEPAD_DOWN,
	GAMEPAD_LEFT,
	GAMEPAD_RIGHT,
	GAMEPAD_START,

	GAMEPAD_BACK,
	GAMEPAD_LEFT_THUMB,
	GAMEPAD_RIGHT_THUMB,
	GAMEPAD_LEFT_SHOULDER,
	GAMEPAD_RIGHT_SHOULDER,

	GAMEPAD_A,
	GAMEPAD_B,
	GAMEPAD_X,
	GAMEPAD_Y,
};
enum class InputState
{
	NoPush,
	PushEnter,
	Press,
	PushExit,
};
struct Button
{
	int Data;
	InputState State;
	InputState beforeState;
};
class Controller
{
private:
	XINPUT_STATE padState;
	std::map<int, Button> button;
	std::map<int, int> SubInputKeyBord;
	class StringDrawer& m_drawer;
	
public:
	Controller();
	~Controller();
	
	void Update();
	void ShowControllerState();
	XINPUT_STATE GetContorollerState() { return padState; };
	bool CheckSubInput(ButtonName bN);
	bool GetControllerButtonState(ButtonName bN);
	bool IsPushEnter(ButtonName bN);
	bool IsPress(ButtonName bN);
	bool IsRelease(ButtonName bN);
	////右のスティック入力を0.0f～1.0fで受け取れる(x,y)
	const DirectX::XMFLOAT2 GetRightStickInput();

	////右のスティック入力を0.0f～1.0fで受け取れる(x,y)
	const DirectX::XMFLOAT2 GetLeftStickInput();
	const float INPUT_MAX = 32767.0f;
};

