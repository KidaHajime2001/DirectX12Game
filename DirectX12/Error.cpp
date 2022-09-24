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
	//  エラーメッセージをコピー
	m_errorMessage = str;
	//  エラーが発生
	m_IsOccurErrorFlag = true;
}


bool Error::IsOccurError()
{
    //  エラーが発生していれば
    if (m_IsOccurErrorFlag)
    {
        //  エラーメッセージを出す
        MessageBox(m_device.hwnd, m_errorMessage.c_str(), "エラー", MB_OK);
        return m_IsOccurErrorFlag;
    }
    return m_IsOccurErrorFlag;
}