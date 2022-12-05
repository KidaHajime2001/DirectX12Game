#pragma once
#include<DirectXMath.h>
//�v���C���[�̒e�����N���X
class PlayerShotDirector
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	PlayerShotDirector();
	~PlayerShotDirector();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="_isShot">�v���C���[�̒e�����t���O�������Ă��邩</param>
	/// <param name="_pos">�e���˂̂��߂̃|�W�V����</param>
	/// <param name="_direction">�e��������</param>
	/// <param name="_speed">�e�̑��x</param>
	void Update(const bool& _isShot,const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT3& _direction,const float& _speed);

	//�`��
	void Draw();
private:
	//�I�u�W�F�N�g�v�[��
	class BulletPool* m_bulletPool;
	const float FIRE_POSITION = 5.0f;
};
