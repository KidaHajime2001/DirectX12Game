#pragma once
#include<vector>
//�e�����������������Ȃ��悤���u���������̂��ė��p����
class BulletPool
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	BulletPool();
	~BulletPool();

	/// <summary>
	/// �w�萔�I�u�W�F�N�g�𐶐�
	/// </summary>
	/// <param name="_size">�I�u�W�F�N�g�v�[���̑傫��</param>
	void CreatePool(int _size);
	
	//�I�u�W�F�N�g�v�[���̍폜
	void DestroyPool();
	/// <summary>
	/// ���g�p�̒e��Ԃ�
	/// </summary>
	class Bullet* GetUnUsedBullet();
	//�X�V
	void Update();
	//�`��
	void Draw();
private:
	//�I�u�W�F�N�g�̐�
	int m_poolSize;
	//�e�̃I�u�W�F�N�g�v�[��
	std::vector<Bullet*> m_bulletPool;
};
