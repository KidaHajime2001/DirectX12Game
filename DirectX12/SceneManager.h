#pragma once
#pragma once
#include"SceneBase.h"
#include"SceneTag.h"
//���݂̃V�[�����Ď����ēK�؂Ȏ��N���X��n���A�t���[�̖���
class SceneManager
{
public:
	/// <summary>
	/// ���͂����Ď��̃V�[����n��
	/// �V�[���؂�ւ��̃t���O����������Ăяo�����
	/// </summary>
	/// <param name="nowScene">���̃V�[�����󂯎��</param>
	/// <returns> ���̃V�[����Ԃ�</returns>
	class SceneBase* ScenePasser(SceneBase* scenebase);

};
