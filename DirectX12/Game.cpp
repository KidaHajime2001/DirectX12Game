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
#include"LesserEnemy.h"
#include"Sound.h"
#include"SoundType.h"
#include"StraightShotEnemy.h"
#include"EnemyManager.h"
#include"EnemyPool.h"
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
	, m_collisionManager(Singleton<CollisionManager>::GetInstance())
	, m_time(new Time())
	, m_ground(new Ground(CollisionTag::BackGround))
	, m_distanceMoved(0)
	, m_debugFlag(false)
	, m_gameOverFlag(false)
	,m_enemyManager(new EnemyManager())

{
	m_backGroundCode = 0;
	BGMHandle = m_sound.Play(SoundType::GameSceneBGM,true,true);

}

Game::~Game()
{

	
	m_collisionManager.DestroyAll();
	delete m_player;
	delete m_time;
	delete m_ground;
	delete m_enemyManager;
}

void Game::Update()
{
	if (!m_gameOverFlag)
	{
		m_player->Update();

		m_enemyManager->Update(m_player->GetPosition());
		m_collisionManager.Update();
		if (m_controller.IsPushEnter(ButtonName::GAMEPAD_BACK))
		{
			m_debugFlag = !m_debugFlag;
		}
		if (!m_player->IsAlive())
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
	m_ground->Draw();
	m_player->Draw();
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
			m_drawer.DrawStringBlackAndYellowForFewNumber(m_ground->GetSecondPosition().y,XMFLOAT2(0,400),0.5f);
			m_drawer.DrawStringBlackAndYellowForFewNumber(m_ground->GetSecondPosition().z, XMFLOAT2(0, 450), 0.5f);

		}
		
		if (!m_gameOverFlag)
		{
			
			m_drawer.DrawStringBlackAndYellowForFewNumber(m_fps.GetFPS(), XMFLOAT2(1800, 50), 0.5f);
		}
		
	
}

void Game::LineDraw()
{
	m_ground->DrawBackCircle();
	m_enemyManager->Draw();
}

void Game::DrawBackGround()
{
	
	if (m_alphaValue>=1.0f)
	{
		m_backGroundCode = -0.01f;
	}
	else if (m_alphaValue <= 0.0f)
	{
		m_backGroundCode = 0.01f;
	}
	m_alphaValue += m_backGroundCode;

	m_sprite.Draw(SpriteType::GameBackGround, XMFLOAT2(0, 0),1.0f,m_sprite.GetColorWithAlfa(m_alphaValue));
}
