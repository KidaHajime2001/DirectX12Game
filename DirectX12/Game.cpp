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
#include"Score.h"
#include"GameLevel.h"
#include"GameResultUI.h"
#include"GameSceneWaveManager.h"
#include "ScoreData.h"
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
	, m_debugFlag(false)
	, m_gameOverFlag(false)
	, m_enemyManager(new EnemyManager())
	, m_score(new ScoreUI())
	, m_gameResultUI(new GameResultUI())
	, m_gameSceneWaveManager(new GameSceneWaveManager())


	, m_shieldImg(SHIELD_IMAGE_SIZE* SHIELD_IMAGE_VAR)
{
	m_backGroundCode = 0;

}

Game::~Game()
{

	
	m_collisionManager.DestroyAll();
	delete m_score;
	delete m_player;
	delete m_time;
	delete m_ground;
	delete m_enemyManager;
	delete m_gameResultUI;
	delete m_gameSceneWaveManager;
}

void Game::Update()
{
	m_gameSceneWaveManager->Update(m_player->IsAlive());
	if (m_gameSceneWaveManager->GetNowGameWave()==GameSceneWaveManager::GameWave::Wave)
	{
		m_player->Update();
		m_ground->Update();
		m_enemyManager->Update(m_player->GetPosition());
		if (m_gameSceneWaveManager->Is90s())
		{
			m_enemyManager->Advent90s();
		}
		if (m_gameSceneWaveManager->Is60s())
		{
			m_enemyManager->Advent60s();
		}
		if (m_gameSceneWaveManager->Is30s())
		{
			m_enemyManager->Advent30s();
		}
		CountScore(m_enemyManager->GetEnemyDefeatScore().x, m_enemyManager->GetEnemyDefeatScore().y);

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
	else if(m_gameSceneWaveManager->GetNowGameWave() == GameSceneWaveManager::GameWave::Result)
	{
		if (m_controller.IsPushEnter(ButtonName::GAMEPAD_A))
		{
			m_sound.Stop(SoundType::GameSceneBGM,BGMHandle);
			m_nextSceneFlag = true;
			m_sound.StopAll();
		}
	}
	FadeImageControll();
}

void Game::Draw()
{
	m_enemyManager->Draw();
	m_ground->Draw();
	m_player->Draw();
	if (m_gameOverFlag)
	{
		m_sprite.Draw(SpriteType::ResultBack,XMFLOAT2(0,0));
	}
	m_score->DrawSprite();
	m_gameSceneWaveManager->Draw(); 
	if (m_gameSceneWaveManager->GetNowGameWave() == GameSceneWaveManager::GameWave::Wave)
	{
		float alpha = 1.0f;
		if (m_player->GetShieldGauge()<=1.0f)
		{
			alpha = m_player->GetShieldGauge()+0.2f;
		}
		m_sprite.Draw(SpriteType::ControllGame, XMFLOAT2(0, -30),1.0f,m_sprite.GetColorWithalpha(m_controllerImageAlpha));
		float var = m_player->GetShieldGauge();
		m_sprite.Draw(SpriteType::shieldGauge, XMFLOAT2(500 + m_shieldPos.x, m_shieldPos.y + (m_shieldImg - (m_shieldImg * var))),
			var,
			1.0f,
			1.0f,
			1.0f,
			1.0f * SHIELD_IMAGE_VAR, m_sprite.GetColorWithalpha(alpha));
		m_sprite.Draw(SpriteType::shieldGaugeFlame, XMFLOAT2(500 + m_shieldPos.x, m_shieldPos.y),
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f * SHIELD_IMAGE_VAR, m_sprite.GetColorWithalpha(alpha));
	}
	if (m_gameSceneWaveManager->GetNowGameWave() == GameSceneWaveManager::GameWave::Result)
	{
		m_sprite.Draw(SpriteType::ControllResult, XMFLOAT2(0, 0));
	}
}

void Game::DrawString()
{
	
	
	if (m_debugFlag)
	{
		m_score->DrawString();
		m_controller.ShowControllerState();
		m_drawer.DrawStringBlackAndWhiteForFewNumber(m_time->GetNowCount(), XMFLOAT2(0,300), 0.5f);
		m_drawer.DrawStringBlackAndWhiteForFewNumber(m_player->GetPosition().x,XMFLOAT2(0,400),0.5f);
		m_drawer.DrawStringBlackAndWhiteForFewNumber(m_ground->GetSecondPosition().z, XMFLOAT2(0, 450), 0.5f);

		m_drawer.DrawStringBlackAndWhiteForFewNumber(m_fps.GetFPS(), XMFLOAT2(1800, 50), 0.5f);

	}
		
	if (m_gameSceneWaveManager->GetNowGameWave() == GameSceneWaveManager::GameWave::Wave)
	{
		m_drawer.DrawStringBlackAndWhite("SCORE : ", XMFLOAT2(80, 30));
		m_drawer.DrawStringBlackAndWhiteForNumber(m_defeatScore, XMFLOAT2(300, 30), 1.0f);
		m_drawer.DrawStringBlackAndWhite("TIME  : ", XMFLOAT2(104, 85));
		

		m_drawer.DrawStringBlackAndWhite("SHIELD : ", XMFLOAT2(70, 135));
		m_drawer.DrawStringBlackAndWhiteForNumber(m_gameSceneWaveManager->GetNowCountTime(), XMFLOAT2(300, 85), 1.0f);

		m_drawer.DrawStringBlackAndWhiteForNumber(m_player->GetShieldGauge()*100, XMFLOAT2(300, 135), 1.0f);
		m_drawer.DrawStringBlackAndWhite("/100", XMFLOAT2(360, 135), 1.0f);
		m_gameSceneWaveManager->DrawString();
		
	}
	else if(m_gameSceneWaveManager->GetNowGameWave() == GameSceneWaveManager::GameWave::Result)
	{
		float gameClearScore;
		if (!m_player->IsAlive())
		{
			gameClearScore = 0;
		}
		else
		{
			gameClearScore = 1000;
		}
		GameResultUI::ScoreData score = { m_gameSceneWaveManager->GetNowOverTime(),m_enemyManager->GetEnemyDefeatScore().x,m_enemyManager->GetEnemyDefeatScore().y,gameClearScore ,m_defeatScore,m_gameLevel->GetGameScore() };
		m_gameResultUI->Draw(score);
		int sum =m_gameResultUI->GetScore();
		if (sum> m_gameLevel->GetGameScore())
		{
			m_gameLevel->SetGameScore(sum);
		}
		
	}
		
	
}

void Game::DrawLine()
{
	m_ground->DrawBackCircle();
	m_enemyManager->LineDraw();
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

	m_sprite.Draw(SpriteType::GameBackGround, XMFLOAT2(0, 0),1.0f,m_sprite.GetColorWithalpha(m_alphaValue));
}

void Game::Init()
{
	m_enemyManager->SetGameLevel(m_gameLevel->GetGameLevel());
	BGMHandle = m_sound.Play(SoundType::GameSceneBGM, true, true);
}

void Game::FadeImageControll()
{
	if (m_controller.IsPress(ButtonName::GAMEPAD_RIGHT_SHOULDER)
		|| m_controller.GetTiggerInputR()>=0.3f)
	{
		if (m_controllerImageAlpha>=0)
		{
			m_controllerImageAlpha -= 0.2f;
			return;
		}
	}

	m_controllerImageAlpha += 0.02f;
	if (m_controllerImageAlpha > 1.0f)
	{
		m_controllerImageAlpha = 1.0f;
	}
	
}

void Game::CountScore(const int _defeatLesserEnemyScore, const int _defeathigherEnemyScore)
{
	
	m_maxScore = (DEFEAT_LESSER * _defeatLesserEnemyScore) + (DEFEAT_HIGHER * _defeathigherEnemyScore);
	m_defeatScore += 3;
	if (m_defeatScore >= m_maxScore)
	{
		m_defeatScore = m_maxScore;
	}
}
