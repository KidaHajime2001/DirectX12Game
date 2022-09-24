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
	//�ǂݍ��񂾃t�@�C���f�[�^�̃Q�b�^�[
	 int				GetInt			(JsonDataType _type,	const char* _dataKey, const char* _IndexString = nullptr, int Index = -1);
	 float			    Getfloat		(JsonDataType _type,	const char* _dataKey, const char* _IndexString = nullptr, int Index = -1);
	 std::string		GetString		(JsonDataType _type,	const char* _dataKey, const char* _IndexString = nullptr, int Index = -1);
	 DirectX::XMFLOAT3  GetXMFLOAT3		(JsonDataType _type,	const char* _dataKey, const char* _IndexString = nullptr, int Index = -1);
	
private:
	std::unordered_map<JsonDataType, rapidjson::Document> m_doc;
	std::unordered_map<JsonDataType, const char*> filePathMap;
};
