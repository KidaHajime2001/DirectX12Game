#pragma once
#include<string>
class Error
{
public:
	Error();
	~Error();
	
	//エラーメッセージの作成
	void CreateErrorMessage(const std::string& str);
	
	//エラーは発生しているか
	bool IsOccurError();
private:
	//エラーが発生しているか
	// Occurは起こる、という意味
	bool m_IsOccurErrorFlag;
	std::string m_errorMessage;

	//シングルトンクラスへの参照
	class D12Device& m_device;

};

