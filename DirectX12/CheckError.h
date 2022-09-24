#pragma once
#include <string>

//  �G���[�`�F�b�N������N���X
class CheckError
{
public:
    CheckError();
    ~CheckError();

    //  �G���[���b�Z�[�W�̍쐬
    void CreateErrorMessage(const std::string& _str);

    //  �G���[�͔������Ă��邩
    bool IsOccurError();
private:
    //  �G���[���������Ă��邩
    bool m_isOccurError;
    //  �G���[���b�Z�[�W
    std::string m_errorMessage;

    //  �V���O���g���N���X�ւ̎Q��
    class D12Device& m_device; //  �f�o�C�X�̊Ǘ�
};
