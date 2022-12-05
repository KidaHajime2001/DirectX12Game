#pragma once
#include "EnemyBase.h"

//�ˌ����s��Ȃ��G���G�N���X
class LesserEnemy :
    public EnemyBase
{
public:
    //�R���X�g���N�^
    LesserEnemy(CollisionTag _tag, bool m_alive);
    //�f�X�g���N�^
    ~LesserEnemy();
    //������
    void Init();
    //�X�V
    void Update(const DirectX::XMFLOAT3 _targetPos);

   
private:
    /// <summary>
    /// �Ȉ�AI�̑ҋ@�s��
    /// </summary>
    /// <param name="_targetPos">
    /// �^�[�Q�b�g�i�v���C���[�j�̈ʒu
    /// </param>
    void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);
    /// <summary>
    /// �Ȉ�AI�̈ړ��s��
    /// </summary>
    /// <param name="_targetPos">
    /// �^�[�Q�b�g�i�v���C���[�j�̈ʒu
    /// </param>
	void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);
   
    /// <summary>
   /// �ŗL�̓����A
   /// </summary>
   /// <param name="otherCollision">
   ///�@�ڐG�����������蔻����
   /// </param>
    void CollisionOriginal(class Collision* otherCollision);

    //���Ԃ�}��N���X
    class Time* m_timer;
};