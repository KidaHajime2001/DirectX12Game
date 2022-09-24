#pragma once
#include <math.h>

#include"Singleton.h"
#include"StringDrawer.h"
#include <windows.h>
class Fps {
	int mStartTime;         //����J�n����
	int mCount;             //�J�E���^
	float mFps;             //fps
	int N = 60;//���ς����T���v����
	int FPS = 60;	//�ݒ肵��FPS
	class StringDrawer& m_drawer;
public:
	Fps()
	:m_drawer(Singleton<StringDrawer>::GetInstance())
	{
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}
	void SetFPS(int _fps)
	{
		mCount = 0;
		N = FPS = _fps;
	};
	bool Update() {
		if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
			mStartTime = GetTickCount64();
		}
		if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
			int t = GetTickCount64();
			mFps = 1000.f / ((t - mStartTime) / (float)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}
	const int GetFPS() { return mFps; };
	void Draw() {
		m_drawer.DrawStringBlackAndYellowForFewNumber(mFps,XMFLOAT2(1500,0));
	}

	void Wait() {
		int tookTime = GetTickCount64() - mStartTime;	//������������
		int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
		if (waitTime > 0) {
			Sleep(waitTime);	//�ҋ@
		}
	}
};