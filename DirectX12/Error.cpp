#include "Error.h"
#include"Singleton.h"
#include"D12Device.h"

Error::Error()
	:m_device(Singleton<D12Device>::GetInstance())
	,m_IsOccurErrorFlag(false)
{
}

Error::~Error()
{
}

void Error::CreateErrorMessage(const std::string& str)
{
	//  �G���[���b�Z�[�W���R�s�[
	m_errorMessage = str;
	//  �G���[������
	m_IsOccurErrorFlag = true;
}


bool Error::IsOccurError()
{
    //  �G���[���������Ă����
    if (m_IsOccurErrorFlag)
    {
        //  �G���[���b�Z�[�W���o��
        MessageBox(m_device.hwnd, m_errorMessage.c_str(), "�G���[", MB_OK);
        return m_IsOccurErrorFlag;
    }
    return m_IsOccurErrorFlag;
}