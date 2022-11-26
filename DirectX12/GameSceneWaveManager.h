#pragma once
//waveëJà⁄ÇÃÇ›Çä«óù
class GameSceneWaveManager
{
public:
	enum class GameWave
	{
		AppearPlayer,
		StartWave,
		Wave,
		Result,
	};
	GameSceneWaveManager();
	~GameSceneWaveManager();
	void Update(const bool _IsAlive);
	const GameWave GetNowGameWave() { return m_gamewave; };
	const int GetNowCountTime();
	const int GetNowOverTime();
	void Draw();
	void DrawString();

	const bool Is90s();
	const bool Is60s();
	const bool Is30s();

private:
	void DrawCountDown();
	const float m_countSpriteAlpha = 0.2f;
	const float COUNT_SPRITE_ALPHA = 0.2f;
	 
	class Time* m_timer90s;
	class Time* m_timer60s;
	class Time* m_timer30s;
	const int WAVETIME_MAX	=	90;
	GameWave m_gamewave;
	class Controller& m_controller;
	float x = 0;
	float y = 0;
	class Time* m_timer;
	class StringDrawer& m_drawer;
	class Camera& m_camera;
	int m_waveCount;
	class SpriteDrawer& m_sprite;
	float m_size;
	bool m_revers;
	bool m_countDown;
	float m_reversSize;
	int m_gameOverTime; 
	int m_holdTime;
};