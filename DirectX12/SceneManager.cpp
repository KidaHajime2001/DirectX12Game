#include "SceneManager.h"
#include"Title.h"
#include"Game.h"
#include"Credit.h"
SceneBase* SceneManager::ScenePasser(SceneBase* scenebase)
{
	//タグ名で判別
	if (scenebase->GetSceneTag() == SceneTag::Title)
	{

		if (scenebase->GetSceneIndex()==(int)Title::NextScene::Game)
		{
			//タイトルの次はゲームメイン
			return new Game(SceneTag::GameMain);
		}
		else if (scenebase->GetSceneIndex() ==(int)Title::NextScene::Credit)
		{
			return new Credit(SceneTag::GameCredit);
		}
		
	}
	if (scenebase->GetSceneTag() == SceneTag::GameCredit)
	{
		return new Title(SceneTag::Title);
	}
	if (scenebase->GetSceneTag() == SceneTag::GameMain)
	{
		return new Title(SceneTag::Title);
	}

	//タグついてなかったらnullptr(エラー)
	return nullptr;
}

