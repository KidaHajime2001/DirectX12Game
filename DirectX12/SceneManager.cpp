#include "SceneManager.h"
#include"Title.h"
#include"Game.h"
SceneBase* SceneManager::ScenePasser(SceneBase* scenebase)
{
	//�^�O���Ŕ���
	if (scenebase->GetSceneTag() == SceneTag::Title)
	{
		//�^�C�g���̎��̓Q�[�����C��
		return new Game(SceneTag::GameMain);
	}
	if (scenebase->GetSceneTag() == SceneTag::GameMain)
	{
		return new Title(SceneTag::Title);
	}

	//�^�O���ĂȂ�������nullptr(�G���[)
	return nullptr;
}

