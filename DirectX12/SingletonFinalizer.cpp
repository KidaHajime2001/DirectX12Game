#include "SingletonFinalizer.h"

#include <mutex>
#include <cassert>

namespace
{
    //  ��������������Ȃ���C���X�^���X�̍ő吔
    constexpr int finalizersSizeMax = 256;
    std::mutex gMutex;
    //  ��������ɓo�^����Ă���C���X�^���X�̐�
    int finalizersNum = 0;
    //  ��������p�̊֐�
    SingletonFinalizer::FinalizerFunc finalizerFunc[finalizersSizeMax];

}

//  �V���O���g���N���X�̏I���������ɉ�������C���X�^���X�̒ǉ�
void SingletonFinalizer::AddFinalizer(FinalizerFunc _func) {
    //  �r��������s��
    std::lock_guard<std::mutex> lock(gMutex);
    //  �o�^�ł���C���X�^���X���𒴂�����G���[���o��
    assert(finalizersNum < finalizersSizeMax);
    //  �C���X�^���X����������ɓo�^
    finalizerFunc[finalizersNum++] = _func;
}

//  �V���O���g���N���X�̏I������
void SingletonFinalizer::Finalize() {
    //  �r��������s��
    std::lock_guard<std::mutex> lock(gMutex);
    //  �o�^����Ă���C���X�^���X��S�ĉ������
    for (int i = finalizersNum - 1; i >= 0; --i) {
        (*finalizerFunc[i])();
    }
    finalizersNum = 0;
}