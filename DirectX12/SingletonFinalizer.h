#pragma once

//  �V���O���g���̉�����s���N���X
class SingletonFinalizer {
public:
    /// <summary>
    /// ���̃N���X�̊֐��𗘗p���邽�߂̐錾
    /// void = �֐��̖߂�l
    /// (*)  = �֐����i���̏ꍇ�͉��������
    /// ()   = ���� 
    /// </summary>
    using FinalizerFunc = void(*)();
    
    /// <summary>
    /// �V���O���g���N���X�̏I���������ɉ�������C���X�^���X�̓o�^
    /// </summary>
    /// <param name="_func">
    /// �֐��|�C���^
    /// ����̏����֐�������
    /// </param>
    static void AddFinalizer(FinalizerFunc _func);
    //  �V���O���g���N���X�̏I������
    static void Finalize();
};