#pragma once
#include<time.h>
class Time
{
public:
	Time();
	~Time();
	int GetNowCount();
	void SetTimer(int _Limit);
	bool CheakTime();
private:
	clock_t m_startCount;
	int m_limitTime;
	bool m_nowCountFlag;

};
