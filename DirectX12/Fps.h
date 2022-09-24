#pragma once
#include <math.h>

#include"Singleton.h"
#include"StringDrawer.h"
#include <windows.h>
class Fps {
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	float mFps;             //fps
	int N = 60;//平均を取るサンプル数
	int FPS = 60;	//設定したFPS
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
		if (mCount == 0) { //1フレーム目なら時刻を記憶
			mStartTime = GetTickCount64();
		}
		if (mCount == N) { //60フレーム目なら平均を計算する
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
		int tookTime = GetTickCount64() - mStartTime;	//かかった時間
		int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
		if (waitTime > 0) {
			Sleep(waitTime);	//待機
		}
	}
};