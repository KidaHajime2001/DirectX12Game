#include "SceneBase.h"
#include"GameLevel.h"
SceneBase::SceneBase(SceneTag _tag)
	:m_nextSceneFlag(false)
	
{
	tag = _tag;
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init()
{
}

void SceneBase::Update()
{
}

void SceneBase::Draw()
{
}

void SceneBase::DrawLine()
{
}

void SceneBase::DrawString()
{
}

void SceneBase::DrawBackGround()
{
}

void SceneBase::SetGameLevelClass(GameLevel* _gamelevel)
{
	m_gameLevel = _gamelevel;
}
