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
	auto nowTime = clock();
	return (float)(nowTime - m_startCount) / (float)CLOCKS_PER_SEC;
}

void Time::SetTimer(int _Limit)
{
	if (m_nowCountFlag)
	{
		/*OutputDebugString("AllReady Set.\n");*/
		return;
	}
	m_limitTime = _Limit;
	m_startCount = clock();
	m_nowCountFlag = true;
}

bool Time::CheakTime()
{
	if (!m_nowCountFlag)
	{
		return false;
	}
	auto nowTime = clock();
	float time = (float)(nowTime - m_startCount) / (float)CLOCKS_PER_SEC;
	if (time>=m_limitTime)
	{
		m_nowCountFlag = false;
		return true;
	}
	return false;
}

void Time::SetTimer(float _Limit)
{
	if (m_nowCountFlag)
	{
		/*OutputDebugString("AllReady Set.\n");*/
		return;
	}
	m_limitTime = _Limit;
	m_startCount =  clock();
	m_nowCountFlag = true;
}

