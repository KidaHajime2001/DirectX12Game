#include "GameSceneWaveManager.h"
#include"Time.h"
#include"SpriteDrawer.h"
#include"Singleton.h"
#include "SpriteType.h"
#include"StringDrawer.h"
#include"Camera.h"
#include"Controller.h"
GameSceneWaveManager::GameSceneWaveManager()
	:m_timer(new Time())
	, m_timer90s(new Time())
	,m_timer60s(new Time())
	, m_timer30s(new Time())
	,m_waveCount(1)
	,m_gamewave(GameWave::StartWave)
	, m_drawer(Singleton<StringDrawer>::GetInstance())
	,m_size(0)
	,m_reversSize(0)
	,m_holdTime(0)
	,m_revers(false)
	,m_countDown(false)
	, m_sprite((Singleton<SpriteDrawer>::GetInstance()))
	, m_camera(Singleton<Camera>::GetInstance())
	, m_controller(Singleton<Controller>::GetInstance())
{
}

GameSceneWaveManager::~GameSceneWaveManager()
{
	delete m_timer;
	delete m_timer90s;
	delete m_timer60s;
	delete m_timer30s;
}

void GameSceneWaveManager::Update(const bool _IsAlive)
{
	m_size += 0.01f; 
	if (m_revers)
	{
		m_reversSize -= 0.01f;
	}
	switch (m_gamewave)
	{
	case GameWave::StartWave:
		if (m_size >= 1.0f)
		{
			m_revers = true;
		}
		if(m_revers&& m_reversSize<=-1.0f)
		{
			m_timer->SetTimer(1);
			m_camera.MovementGameStart();
			if (m_timer->CheakTime()&&m_camera.GetCompleteFlag())
			{
				m_revers = false;
				m_reversSize = 0;
				m_size = 0;
				m_gamewave = GameWave::Wave;
			}

		}
		break;
	case GameWave::Wave:
		m_timer->SetTimer(WAVETIME_MAX);
		if (m_timer->CheakTime())
		{
			m_holdTime = m_timer->GetNowCount();
			m_gamewave = GameWave::Result;

		}
		if (!_IsAlive)
		{
			m_holdTime = m_timer->GetNowCount();
			m_gameOverTime = m_timer->GetNowCount();
			m_gamewave = GameWave::Result;
		}
		if (GetNowCountTime() <= 90
			&& GetNowCountTime() >= 60)
		{
			m_timer90s->SetTimer(1);
		}
		if (GetNowCountTime() <= 80)
		{
			m_timer60s->SetTimer(20);
		}
		if (GetNowCountTime() <= 45)
		{

			m_timer30s->SetTimer(15);
		}
		if (30 < GetNowCountTime() && GetNowCountTime() <= 60)
		{
			m_camera.SetBackGroundColor(XMFLOAT3(35, 0, 10));

		}
		else if (GetNowCountTime() <= 30)
		{

			m_camera.SetBackGroundColor(XMFLOAT3(92, 5, 26));
		}


		break;
	case GameWave::Result:
		break;
	default:
		break;
	}
}

const int GameSceneWaveManager::GetNowCountTime()
{
	if (GetNowGameWave() == GameSceneWaveManager::GameWave::Result)
	{
		return m_gameOverTime;
	}
	return WAVETIME_MAX- m_timer->GetNowCount();
}

const int GameSceneWaveManager::GetNowOverTime()
{
	return m_holdTime;
}

void GameSceneWaveManager::Draw()
{
	
	if (m_gamewave == GameWave::StartWave)
	{
		m_sprite.Draw(SpriteType::Wave1Start, XMFLOAT2(0, 0), 1.0f, m_size, m_size, m_size, 1.0f, m_sprite.GetColorWithalpha(1.0f + m_reversSize));
	}
	if (m_gamewave == GameWave::Wave)
	{
		/*if (GetNowCountTime() <= 90
			&& GetNowCountTime() >= 60)
		{
			m_timer60s->SetTimer(15);
		}
		if (GetNowCountTime() <= 80)
		{
			m_timer60s->SetTimer(20);
		}
		if (GetNowCountTime() <= 45)
		{

			m_timer30s->SetTimer(15);
		}
		if ( 30<GetNowCountTime()&& GetNowCountTime() <= 60)
		{
			m_camera.SetBackGroundColor(XMFLOAT3(35, 0, 10));

		}
		else if (GetNowCountTime() <= 30)
		{

			m_camera.SetBackGroundColor(XMFLOAT3(92, 5, 26));
		}*/
		DrawCountDown();
		
	}
	else if (GetNowGameWave() == GameSceneWaveManager::GameWave::Result)
	{
		m_sprite.Draw(SpriteType::ResultText , XMFLOAT2(0, 57), 1.0f, m_sprite.GetColorWithalpha(1.0f));
		m_sprite.Draw(SpriteType::ResultLine, XMFLOAT2(53, -13), 1.0f, m_sprite.GetColorWithalpha(1.0f));
	}
}

void GameSceneWaveManager::DrawString()
{
	
	
}

const bool GameSceneWaveManager::Is90s()
{
	return m_timer90s->CheakTime();
}

const bool GameSceneWaveManager::Is60s()
{
	return m_timer60s->CheakTime();
}

const bool GameSceneWaveManager::Is30s()
{

	return m_timer30s->CheakTime();
}

void GameSceneWaveManager::DrawCountDown()
{
	switch (GetNowCountTime())
	{
	case 1:
		m_sprite.Draw(SpriteType::count1, XMFLOAT2(0, 0), 1.0f, m_sprite.GetColorWithalpha(COUNT_SPRITE_ALPHA));
		break;
	case 2:
		m_sprite.Draw(SpriteType::count2, XMFLOAT2(0, 0), 1.0f, m_sprite.GetColorWithalpha(COUNT_SPRITE_ALPHA));
		break;
	case 3:
		m_sprite.Draw(SpriteType::count3, XMFLOAT2(0, 0), 1.0f, m_sprite.GetColorWithalpha(COUNT_SPRITE_ALPHA));
		break;
	case 4:
		m_sprite.Draw(SpriteType::count4, XMFLOAT2(0, 0), 1.0f, m_sprite.GetColorWithalpha(COUNT_SPRITE_ALPHA));
		break;
	case 5:
		m_sprite.Draw(SpriteType::count5, XMFLOAT2(0, 0), 1.0f, m_sprite.GetColorWithalpha(COUNT_SPRITE_ALPHA));
		break;
	case 6:
		m_sprite.Draw(SpriteType::count6, XMFLOAT2(0, 0), 1.0f, m_sprite.GetColorWithalpha(COUNT_SPRITE_ALPHA));
		break;
	case 7:
		m_sprite.Draw(SpriteType::count7, XMFLOAT2(0, 0), 1.0f, m_sprite.GetColorWithalpha(COUNT_SPRITE_ALPHA));
		break;
	case 8:
		m_sprite.Draw(SpriteType::count8, XMFLOAT2(0, 0), 1.0f, m_sprite.GetColorWithalpha(COUNT_SPRITE_ALPHA));
		break;
	case 9:
		m_sprite.Draw(SpriteType::count9, XMFLOAT2(0, 0), 1.0f, m_sprite.GetColorWithalpha(COUNT_SPRITE_ALPHA));
		break;
	case 10:
		m_sprite.Draw(SpriteType::count10, XMFLOAT2(0, 0), 1.0f, m_sprite.GetColorWithalpha(COUNT_SPRITE_ALPHA));
		break;

	default:
		break;
	}
}


