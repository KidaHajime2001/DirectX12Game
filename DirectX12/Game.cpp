#include"Game.h"
#include"Player.h"
#include"CollisionManager.h"
#include"Time.h"
#include"Ground.h"
#include "SpriteType.h"
#include"XMF3Math.h"
#include"Camera.h"
#include"Bullet.h"
#include"BulletPool.h"
#include"ShootDirector.h"
#include"Sound.h"
#include"SoundType.h"
Game::Game(SceneTag _sceneTag)
	:SceneBase(_sceneTag)
	, m_controller(Singleton<Controller>::GetInstance())
	, m_drawer(Singleton<StringDrawer>::GetInstance())
	, m_device(Singleton<D12Device>::GetInstance())
	, m_model(Singleton<PMDModel>::GetInstance())
	, m_sprite((Singleton<SpriteDrawer>::GetInstance()))
	, m_fps(Singleton<Fps>::GetInstance())
	, m_sound(Singleton<Sound>::GetInstance())

	, m_player(new Player(CollisionTag::Player, true))
	, m_Enemy(new Enemy(CollisionTag::Enemy, true))
	, m_collisionManager(new CollisionManager())
	, m_time(new Time())
	, m_ground(new Ground(CollisionTag::BackGround, true))
	, m_distanceMoved(0)
	, m_debugFlag(false)
	, m_gameOverFlag(false)
	,m_shootDirector(new ShootDirector())
{

	m_collisionManager->AddCollision(m_player->GetCollision());

	
	BGMHandle = m_sound.Play(SoundType::GameSceneBGM,true,true);

}

Game::~Game()
{
	delete m_player;
	delete m_Enemy;
	delete m_time;
	delete m_collisionManager;
	delete m_ground;
	delete m_shootDirector;
}

void Game::Update()
{
	if (!m_gameOverFlag)
	{
		m_player->Update();

		

		m_shootDirector->Update(m_player);

		m_collisionManager->CollisionUpdate();
		
		if (m_controller.IsPushEnter(ButtonName::GAMEPAD_BACK))
		{
			m_debugFlag = !m_debugFlag;
		}
		if (!m_player->GetAlive())
		{
			m_gameOverFlag = true;
		}
	}
	else
	{
		if (m_controller.IsPushEnter(ButtonName::GAMEPAD_A))
		{
			m_sound.Stop(SoundType::GameSceneBGM,BGMHandle);
			m_nextSceneFlag = true;
		}
	}

}

void Game::Draw()
{

	m_player->Draw();
	m_ground->Draw();
	m_shootDirector->Draw();
	if (m_gameOverFlag)
	{
		m_sprite.Draw(SpriteType::ResultBack,XMFLOAT2(0,0));
	}
}

void Game::DrawString()
{
		if (m_debugFlag)
		{

			m_controller.ShowControllerState();
			m_drawer.DrawStringBlackAndYellowForFewNumber(m_time->GetNowCount(), XMFLOAT2(0,300), 0.5f);
			m_drawer.DrawStringBlackAndYellowForFewNumber(m_player->GetInputVec().x, XMFLOAT2(0, 350), 0.5f);
			m_drawer.DrawStringBlackAndYellowForFewNumber(m_player->GetInputVec().y,XMFLOAT2(0,400),0.5f);
			m_drawer.DrawStringBlackAndYellowForFewNumber(m_player->GetInputVec().z, XMFLOAT2(0, 450), 0.5f);
		}
		
		if (!m_gameOverFlag)
		{
			
			m_drawer.DrawStringBlackAndYellowForFewNumber(m_fps.GetFPS(), XMFLOAT2(1800, 50), 0.5f);
		}
		
	
}

void Game::DrawBackGround()
{
	m_sprite.Draw(SpriteType::GameBackGround , XMFLOAT2(0, 0));
}
