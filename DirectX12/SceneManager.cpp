#include "SceneManager.h"
#include"Title.h"
#include"Game.h"
SceneBase* SceneManager::ScenePasser(SceneBase* scenebase)
{
	//タグ名で判別
	if (scenebase->GetSceneTag() == SceneTag::Title)
	{
		//タイトルの次はゲームメイン
		return new Game(SceneTag::GameMain);
	}
	if (scenebase->GetSceneTag() == SceneTag::GameMain)
	{
		return new Title(SceneTag::Title);
	}

	//タグついてなかったらnullptr(エラー)
	return nullptr;
}

