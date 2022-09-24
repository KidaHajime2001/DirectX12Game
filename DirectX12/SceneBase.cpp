#include "SceneBase.h"

SceneBase::SceneBase(SceneTag _tag)
	:m_nextSceneFlag(false)
	
{
	tag = _tag;
}

SceneBase::~SceneBase()
{
}

void SceneBase::Update()
{
}

void SceneBase::Draw()
{
}

void SceneBase::DrawString()
{
}

void SceneBase::DrawBackGround()
{
}
