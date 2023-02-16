#include "GameResultUI.h"
#include"Singleton.h"
#include"StringDrawer.h"
#include"Singleton.h"
#include"Controller.h"
#include "ScoreData.h"
#include"Fps.h"
#include"Sound.h"
#include"SoundType.h"
GameResultUI::GameResultUI()
	: m_drawer(Singleton<StringDrawer>::GetInstance())
	, m_controller(Singleton<Controller>::GetInstance())
	, m_drawScoreData({0,0,0,0,0})
	,m_fps(Singleton<Fps>::GetInstance())
	,m_sound(Singleton<Sound>::GetInstance())
	, m_drawScoreCompleateFlag(false)
	, m_seOnceFlag(false)
{
}

GameResultUI::~GameResultUI()
{
}

void GameResultUI::Update()
{
}

void GameResultUI::Draw(ScoreData _score)
{
	if (!m_seOnceFlag)
	{
		m_bgmHandle = m_sound.Play(SoundType::ScoreSE, true, true);
		m_seOnceFlag = true;
	}
	
	m_drawer.DrawStringBlackAndWhite("RESULT",			XMFLOAT2(350, 150), 2.5f, 1.0f);
	m_drawer.DrawStringBlackAndWhite("TIME",			XMFLOAT2(350, 350), 1.5f, 1.0f);
	m_drawer.DrawStringBlackAndWhite("LESSER ENEMY",	XMFLOAT2(350, 450), 1.5f, 1.0f);
	m_drawer.DrawStringBlackAndWhite("HIGHER ENEMY",	XMFLOAT2(350, 550), 1.5f, 1.0f);
	m_drawer.DrawStringBlackAndWhite("CLEAR",			XMFLOAT2(350, 650), 1.5f, 1.0f);
	m_drawer.DrawStringBlackAndWhite("TOTAL SCORE",		XMFLOAT2(350, 850), 1.5f, 1.0f);
	m_drawer.DrawStringBlackAndWhite("BEST SCORE",		XMFLOAT2(350, 950), 1.5f, 1.0f);

	m_maxScoreData.timeScore = _score.timeScore * TIME_SCORE;
	m_maxScoreData.lesserScore = _score.lesserScore * DEFEAT_LESSER;
	m_maxScoreData.higherScore = _score.higherScore * DEFEAT_HIGHER;
	m_maxScoreData.clearScore = _score.clearScore;

	m_maxScoreData.sumScore = m_maxScoreData.timeScore + m_maxScoreData.lesserScore + m_maxScoreData.higherScore + m_maxScoreData.clearScore;

	CalculationCode();

	m_drawScoreData.timeScore	+= m_codeData.timeScore;
	m_drawScoreData.lesserScore += m_codeData.lesserScore;
	m_drawScoreData.higherScore += m_codeData.higherScore;
	m_drawScoreData.clearScore	+= m_codeData.clearScore;
	
	m_alreadyCompleateNum = 0;
	if (m_drawScoreData.timeScore>= m_maxScoreData.timeScore)
	{
		m_drawScoreData.timeScore = m_maxScoreData.timeScore;
		m_alreadyCompleateNum++;
	}
	if (m_drawScoreData.lesserScore >= m_maxScoreData.lesserScore)
	{
		m_drawScoreData.lesserScore = m_maxScoreData.lesserScore;
		m_alreadyCompleateNum++;
	}
	if (m_drawScoreData.higherScore >= m_maxScoreData.higherScore)
	{
		m_drawScoreData.higherScore = m_maxScoreData.higherScore;
		m_alreadyCompleateNum++;
	}
	if (m_drawScoreData.clearScore >= m_maxScoreData.clearScore)
	{
		m_drawScoreData.clearScore = m_maxScoreData.clearScore;
		m_alreadyCompleateNum++;
	}

	if (m_alreadyCompleateNum>=ALREADY_COMPLEATE_NUM_MAX)
	{
		m_drawScoreData.sumScore += m_codeData.sumScore;
		if (m_drawScoreData.sumScore >= m_maxScoreData.sumScore)
		{
			m_drawScoreData.sumScore = m_maxScoreData.sumScore;
			m_sound.Stop(SoundType::ScoreSE,m_bgmHandle);
		}
	}
	

	m_drawer.DrawStringBlackAndWhiteForNumber(m_drawScoreData.timeScore,	XMFLOAT2(1030, 350), 1.5f, 1.0f);
	m_drawer.DrawStringBlackAndWhiteForNumber(m_drawScoreData.lesserScore,	XMFLOAT2(1030, 450), 1.5f, 1.0f);
	m_drawer.DrawStringBlackAndWhiteForNumber(m_drawScoreData.higherScore,	XMFLOAT2(1030, 550), 1.5f, 1.0f);
	m_drawer.DrawStringBlackAndWhiteForNumber(m_drawScoreData.clearScore,	XMFLOAT2(1030, 650), 1.5f, 1.0f);
	m_drawer.DrawStringBlackAndWhiteForNumber(m_drawScoreData.sumScore,		XMFLOAT2(1030, 850), 1.5f, 1.0f);
	m_drawer.DrawStringBlackAndWhiteForNumber(_score.bestScore,		 XMFLOAT2(1030, 950), 1.5f, 1.0f);

	sumScore = m_drawScoreData.sumScore;
	//m_drawer.DrawStringBlackAndWhiteForFewNumber(x, XMFLOAT2(0, 300), 0.5f);
	//m_drawer.DrawStringBlackAndWhiteForFewNumber(y, XMFLOAT2(0, 400), 0.5f);
}

void GameResultUI::CalculationCode()
{
	int CalculationFlameMax=m_fps.GetMaxFps()*CALCULATION_TIME_MAX;

	m_codeData.timeScore	= (m_maxScoreData.timeScore		/ CalculationFlameMax	)+1;
	m_codeData.lesserScore	= (m_maxScoreData.lesserScore	/ CalculationFlameMax	)+1;
	m_codeData.higherScore	= (m_maxScoreData.higherScore	/ CalculationFlameMax	)+1;
	m_codeData.clearScore 	= (m_maxScoreData.clearScore	/ CalculationFlameMax	)+1;
	m_codeData.sumScore		= (m_maxScoreData.sumScore		/ CalculationFlameMax	)+1;
}
