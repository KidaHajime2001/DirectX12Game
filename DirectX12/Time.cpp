#include"Time.h"
#include<time.h>
#include <windows.h>
Time::Time()
	:m_startCount(0)
	, m_nowCountFlag(false)
{
}

Time::~Time()
{
}

int Time::GetNowCount()
{
	return (int)GetTickCount64();
}

bool Time::CheakTime()
{
	auto nowTime = clock();
	int time = (int)(nowTime - m_startCount) / (int)CLOCKS_PER_SEC;
	if (time>=LimitTime)
	{
		m_nowCountFlag = false;
		return true;
	}
	return false;
}

void Time::SetTimer(int _Limit)
{
	if (m_nowCountFlag)
	{
		OutputDebugString("AllReady Set.\n");
		return;
	}
	LimitTime=_Limit;
	m_startCount =  clock();
	m_nowCountFlag = true;
}

