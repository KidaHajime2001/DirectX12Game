#include "CheckError.h"

#include "Singleton.h"
#include "D12Device.h"

CheckError::CheckError()
    :m_device(Singleton<D12Device>::GetInstance())
    , m_isOccurError(false)
{
    //  �����Ȃ�
}

CheckError::~CheckError()
{
    //  �����Ȃ�
}

//  �G���[���b�Z�[�W�̍쐬
void CheckError::CreateErrorMessage(const std::string& _str)
{
    //  �G���[���b�Z�[�W���R�s�[
    m_errorMessage = _str;
    //  �G���[������
    m_isOccurError = true;
}

//  �G���[���N���Ă��邩
bool CheckError::IsOccurError()
{
    //  �G���[���������Ă����
    if (m_isOccurError)
    {
        //  �G���[���b�Z�[�W���o��
        MessageBox(m_device.hwnd, m_errorMessage.c_str(), "�G���[", MB_OK);
        return m_isOccurError;
    }
    return m_isOccurError;
}
