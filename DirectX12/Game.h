#pragma once
#include"SceneBase.h"
#include<vector>
class Game :public SceneBase
{
public:
	Game(SceneTag _sceneTag);
	~Game()override;

	void Update()override;
	void Draw()override;
	void DrawString()override;
	void LineDraw()override;
	void DrawBackGround()override;
private:
	
	class StringDrawer& m_drawer;
	class Controller& m_controller;
	class D12Device& m_device;
	class PMDModel& m_model;            //  PMDÉÇÉfÉãÇÃä«óù
	class SpriteDrawer& m_sprite;
	class Fps& m_fps;
	class Sound& m_sound;
	int BGMHandle;

	class Player* m_player;
	class EnemyManager* m_enemyManager;
	class Time* m_time;
	class CollisionManager& m_collisionManager;
	class Ground* m_ground;
	const int TARGET_NUMBER_Z = 70;
	const int PLAYER_CAMERA_NUMBER_Y = 50;
	const int PLAYER_CAMERA_NUMBER_Z = -50;
	bool m_debugFlag;
	float m_distanceMoved = 0.00f;//à⁄ìÆÇµÇΩãóó£
	bool m_gameOverFlag;

	const float WINDOW_WIDTH = 1920;
	const float WINDOW_HEIGHT = 1080;



	float m_alphaValue = 0.0f;
	float m_backGroundCode;
};

