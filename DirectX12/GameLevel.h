#pragma once
class GameLevel
{
public:
	void SetGameLevel(const int _level);
	void SetGameScore(const int _score);
	const int GetGameLevel();
	const int GetGameScore();
private:
	int m_level;
	int m_score = 7000;
};

