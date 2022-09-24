#pragma once
#include"SceneBase.h"
#include<vector>
#include"Enemy.h"
#include"ActorPool.h"
class Game :public SceneBase
{
public:
	Game(SceneTag _sceneTag);
	~Game()override;

	void Update()override;
	void Draw()override;
	void DrawString()override;
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
	class Enemy* m_Enemy;
	class Time* m_time;
	class Pool* m_enemypool;
	class ShootDirector* m_shootDirector;
	class CollisionManager* m_collisionManager;
	class Ground* m_ground;
	const int TARGET_NUMBER_Z = 70;
	const int PLAYER_CAMERA_NUMBER_Y = 50;
	const int PLAYER_CAMERA_NUMBER_Z = -50;
	bool m_debugFlag;
	float m_distanceMoved = 0.00f;//à⁄ìÆÇµÇΩãóó£
	bool m_gameOverFlag;
};

