#pragma once
#include"SceneBase.h"
class Title :public SceneBase
{
public:
	Title(SceneTag _sceneTag);
	~Title()override;

	void Update()override;
	void Draw()override;
	void DrawLine()override;
	void DrawString()override;
	void DrawBackGround()override;
	void ChangeImageAlfa();
private:
	class TitlePlayer* m_player;
	const float DefaultAlfaMax=1.0f;
	const float DefaultAlfaMin = 0.3f;
	const float ChangedAlfaMin = 0.0f;
	float m_alfaValue;
	float Code;
	const float DELTA = 0.01f;
	int BGMHandle;
	bool m_decisionFlag;

	class StringDrawer& m_drawer;
	class Controller& m_controller;
	class D12Device& m_device;
	class PMDModel& m_model;            //  PMDÉÇÉfÉãÇÃä«óù
	class SpriteDrawer& m_sprite;
	class Fps& m_fps;
	class Sound& m_sound;
	class Time* m_time;
	enum class ButtonState
	{
		startButton,
		OptionButton,
	};
	ButtonState m_buttonState;
};
