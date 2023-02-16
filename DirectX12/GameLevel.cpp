#include "GameLevel.h"

void GameLevel::SetGameLevel(const int _level)
{
	m_level = _level;
}

void GameLevel::SetGameScore(const int _score)
{
	m_score = _score;
}

const int GameLevel::GetGameLevel()
{
	return m_level;
}

const int GameLevel::GetGameScore()
{
	return m_score;
}
