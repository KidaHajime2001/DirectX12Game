
#pragma once
//�V���O���g���̃x�^�[�Ȏ������@
//https://qiita.com/kikuuuty/items/fcf5f7df2f0493c437dc
#include <mutex>
#include <cassert>
#include "SingletonFinalizer.h"
//  �N���X���V���O���g��������N���X
//  T�ɂ̓N���X���w�肷��
template <typename T>
class Singleton final
{
public:
    //  �N���XT�̃C���X�^���X���擾
    static T& GetInstance()
    {
        //  ��x����Create�֐����Ă�
        call_once(m_initFlag, Create);
        //  �C���X�^���X�𐳏�ɍ쐬�ł������`�F�b�N����
        assert(m_instance);
        //  �C���X�^���X�̒l��Ԃ�
        return *m_instance;
    }
private:
    //  �C���X�^���X�̐���
    static void Create()
    {
        m_instance = new T;
        //  ��������ɃC���X�^���X��o�^
        SingletonFinalizer::AddFinalizer(&Singleton<T>::Delete);
    }

    //  �C���X�^���X�̉��
    static void Delete()
    {
        delete m_instance;
        m_instance = nullptr;
    }

    //  call_once�֐��ɂāA�����ɐݒ肳�ꂽ�֐�����x�����ĂԂ��߂̕ϐ�
    static std::once_flag m_initFlag;
    //  �N���XT�̃C���X�^���X
    static T* m_instance;
};
//  �ÓI�����o�ϐ��̎��̂��`
template <typename T> std::once_flag Singleton<T>::m_initFlag;
template <typename T> T* Singleton<T>::m_instance = nullptr;
