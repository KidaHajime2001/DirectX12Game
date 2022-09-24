#pragma once
#include<DirectXMath.h>
#include"JsonDataType.h"
#include<unordered_map>
#include"rapidjson/document.h"
using namespace DirectX;
class SupportJson
{
public:
	SupportJson();
	~SupportJson();

	void Load();
	//�ǂݍ��񂾃t�@�C���f�[�^�̃Q�b�^-

	/// <summary>
	/// Int�^�f�[�^�̌Ăяo��
	/// </summary>
	/// <param name="_type">�Ăяo��Load�����t�@�C���̎��</param>
	/// <param name="_dataKey">�Ăяo���f�[�^�̖��O</param>
	/// <param name="_IndexString">�z�񂪂���ꍇ�A���̔z��</param>
	/// <param name="Index">�z�񂪂���ꍇ���̗v�f</param>
	/// <returns></returns>
	int				GetInt			(JsonDataType _type,	const char* _dataKey, const char* _IndexString = nullptr, int Index = -1);
	float			    Getfloat		(JsonDataType _type,	const char* _dataKey, const char* _IndexString = nullptr, int Index = -1);
	std::string		GetString		(JsonDataType _type,	const char* _dataKey, const char* _IndexString = nullptr, int Index = -1);
	DirectX::XMFLOAT3  GetXMFLOAT3		(JsonDataType _type,	const char* _dataKey, const char* _IndexString = nullptr, int Index = -1);
	
private:
	std::unordered_map<JsonDataType, rapidjson::Document> m_doc;
	std::unordered_map<JsonDataType, const char*> filePathMap;
};
