#pragma once
#include"SceneBase.h"
class Title :public SceneBase
{
public:
	enum class SelectState
	{
		StartButton,
		OptionButton,
		CreditButton,
		ModeToLevel,
		/*ModeToEndless,*/
		SelectLevel,
		SoundOptionAll,
		SoundOptionBgm,
		SoundOptionSe,

	};
	enum class NextScene
	{
		Game,
		Credit,
	};
	Title(SceneTag _sceneTag);
	~Title()override;

	void Update()override;
	void Draw()override;
	void DrawLine()override;
	void DrawString()override;
	void DrawBackGround()override;
	void ChangeImagealpha();
private:
	void PlayStart();
	void PushAButtonState(SelectState _state);
	void PushBButtonState(SelectState _state);
	void PushUpButtonState(SelectState _state);
	void PushDownButtonState(SelectState _state);
	void PushLeftButtonState(SelectState _state);
	void PushRightButtonState(SelectState _state);
	void SetVolume();
	class TitlePlayer* m_player;
	const float DefaultalphaMax=1.0f;
	const float DefaultalphaMin = 0.3f;
	const float ChangedalphaMin = 0.0f;
	float m_alphaValue;
	float Code;
	const float DELTA = 0.01f;
	int BGMHandle;
	bool m_decisionFlag;

	class StringDrawer& m_drawer;
	class Controller& m_controller;
	class SpriteDrawer& m_sprite;
	class Sound& m_sound;
	class D12Device& m_device;
	class PMDModel& m_model;            //  PMDモデルの管理
	class Fps& m_fps;
	class Time* m_time;
	class Camera& m_camera;
	class SupportJson& m_json;
	class MatrixEffectController* m_matEffectCon;

	SelectState m_buttonState;
	XMFLOAT2 m_testPos;
	int m_levelNumber;
	float m_allSoundVolume;
	float m_bgmSoundVolume;
	float m_seSoundVolume;

	//UIポジション


	const XMFLOAT2 START_POSITION = {400,600};

	const XMFLOAT2 START_SELECT_POSITION = { 375,600 };
	const XMFLOAT2 NORMAL_POSITION = { 600,600 };
	const XMFLOAT2 NORMAL_SELECT_POSITION = { 675,600 };
	const XMFLOAT2 OPTION_POSITION = { 400,665 };
	const XMFLOAT2 OPTION_SELECT_POSITION = { 375,665 };
	const XMFLOAT2 ENDLESS_POSITION = { 600,665 };
	const XMFLOAT2 LEVEL_POSITION = { 930,600 };
	const XMFLOAT2 LEVEL_NUMBER_POSITION = { 1240,600 };
	const XMFLOAT2 OPTION_ALL_POSITION = { 675,665 };
	const XMFLOAT2 OPTION_BGM_POSITION = { 675,730 };
	const XMFLOAT2 OPTION_SE_POSITION =	 { 675,795 };
	const XMFLOAT2 OPTION_ALL_NUMBER_POSITION = { 1105,665 };
	const XMFLOAT2 OPTION_BGM_NUMBER_POSITION = { 1105,730 };
	const XMFLOAT2 OPTION_SE_NUMBER_POSITION = { 1105,795 };
	const XMFLOAT2 CREDIT_POSITION = { 400,730 };
	

	const XMVECTORF32 SELECTCOLOR = Colors::GreenYellow;
	const XMVECTORF32 OTHERCOLOR = Colors::Green;
	const XMVECTORF32 NONECOLOR = Colors::Black;

};
