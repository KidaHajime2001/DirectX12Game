#pragma once
#include "SceneTag.h"
#include"Singleton.h"
#include"Controller.h"
#include"StringDrawer.h"
#include"SpriteDrawer.h"
#include"D12Device.h"
#include "PMDModel.h"
#include "Fps.h"
class SceneBase
{
public:
	SceneBase(SceneTag _tag);
	virtual ~SceneBase();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void DrawLine();
	virtual void DrawString();
	virtual void DrawBackGround();
	bool GetNextSceneFlag() { return m_nextSceneFlag; };
	SceneTag GetSceneTag() { return tag; };
	void  SetGameLevelClass(class GameLevel* _gamelevel);
	const int GetSceneIndex() { return m_nextSceneIndex; };
protected:
	//今のシーンを判別するタグ
	SceneTag tag;
	bool m_nextSceneFlag;
	GameLevel* m_gameLevel;
	int m_nextSceneIndex=0;
};
