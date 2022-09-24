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
	//読み込んだファイルデータのゲッタ-

	/// <summary>
	/// Int型データの呼び出し
	/// </summary>
	/// <param name="_type">呼び出すLoadしたファイルの種類</param>
	/// <param name="_dataKey">呼び出すデータの名前</param>
	/// <param name="_IndexString">配列がある場合、その配列名</param>
	/// <param name="Index">配列がある場合その要素</param>
	/// <returns></returns>
	int				GetInt			(JsonDataType _type,	const char* _dataKey, const char* _IndexString = nullptr, int Index = -1);
	float			    Getfloat		(JsonDataType _type,	const char* _dataKey, const char* _IndexString = nullptr, int Index = -1);
	std::string		GetString		(JsonDataType _type,	const char* _dataKey, const char* _IndexString = nullptr, int Index = -1);
	DirectX::XMFLOAT3  GetXMFLOAT3		(JsonDataType _type,	const char* _dataKey, const char* _IndexString = nullptr, int Index = -1);
	
private:
	std::unordered_map<JsonDataType, rapidjson::Document> m_doc;
	std::unordered_map<JsonDataType, const char*> filePathMap;
};
