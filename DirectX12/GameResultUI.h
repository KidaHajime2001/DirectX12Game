#include<DirectXHelpers.h>
#include<unordered_map>
class GameResultUI
{
public:
	struct ScoreData
	{
		int timeScore;
		int lesserScore;
		int higherScore;
		int clearScore;
		int sumScore;
	};
	GameResultUI();
	~GameResultUI();
	void Update();
	void Draw(const ScoreData _score);
private:
	void CalculationCode();
	class StringDrawer& m_drawer;
	class Fps& m_fps;
	class Sound& m_sound;
	const int CALCULATION_TIME_MAX=3;
	int m_alreadyCompleateNum;
	int m_bgmHandle;
	bool m_drawScoreCompleateFlag;
	bool m_seOnceFlag;
	const int ALREADY_COMPLEATE_NUM_MAX=4;
	ScoreData m_maxScoreData;
	ScoreData m_drawScoreData;
	ScoreData m_codeData;
	
	float x = 0;
	float y = 0;
	class Controller& m_controller;
};