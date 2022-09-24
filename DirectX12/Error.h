#pragma once
#include<string>
class Error
{
public:
	Error();
	~Error();
	
	//�G���[���b�Z�[�W�̍쐬
	void CreateErrorMessage(const std::string& str);
	
	//�G���[�͔������Ă��邩
	bool IsOccurError();
private:
	//�G���[���������Ă��邩
	// Occur�͋N����A�Ƃ����Ӗ�
	bool m_IsOccurErrorFlag;
	std::string m_errorMessage;

	//�V���O���g���N���X�ւ̎Q��
	class D12Device& m_device;

};

