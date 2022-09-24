#include"SupportJSON.h"
#include"JsonDataType.h"
#include"Singleton.h"
#include"CheckError.h"
#include"EnumItr.h"
#include <fstream>
#include "rapidjson/istreamwrapper.h"
SupportJson::SupportJson()
{
    //  ファイルパス
    filePathMap =
    {
        { JsonDataType::Player,"Data/Param/PlayerData.json" },
        { JsonDataType::Enemy,"Data/Param/EnemyData.json" },
        { JsonDataType::AdventPoint,"Data/Param/Enemy_Advent.json" },
        {JsonDataType::Ground,"Data/Param/GoundData.json"},
    };

    //  ファイルのロード
    Load();
}

SupportJson::~SupportJson()
{
}

int SupportJson::GetInt(JsonDataType _type, const char* _dataKey, int Index = -1)
{
    int ret;
    if (Index==-1)
    {
        ret = m_doc[_type][_dataKey].GetInt();
    }
    
    return ret;
}

float SupportJson::Getfloat(JsonDataType _type, const char* _dataKey, int Index = -1)
{
    float ret;
    if (Index == -1)
    {
        ret = m_doc[_type][_dataKey].GetFloat();
    }
    
    return ret;
}

std::string SupportJson::GetString(JsonDataType _type, const char* _dataKey, int Index = -1)
{
    std::string ret;
    if (Index == -1)
    {
        ret = m_doc[_type][_dataKey].GetString();
    }
    return ret;
}

DirectX::XMFLOAT3 SupportJson::GetXMFLOAT3(JsonDataType _type, const char* _dataKey, int Index = -1)
{
    
    DirectX::XMFLOAT3 ret;
    if (Index == -1)
    {
        ret.x = m_doc[_type][_dataKey]["x"].GetFloat();
        ret.y = m_doc[_type][_dataKey]["y"].GetFloat();
        ret.z = m_doc[_type][_dataKey]["z"].GetFloat();
    }
    
    return ret;
}

void SupportJson::Load()
{
    //  エラーチェック用クラスのシングルトンインスタンスを得る
    CheckError& checkError = Singleton<CheckError>::GetInstance();

    //  列挙型JsonDataTypeのイテレータを作成
    typedef EnumIterator<JsonDataType, JsonDataType::Player, JsonDataType::Ground> typeItr;
    for (auto itr : typeItr())
    {
        //  二重ロードの防止
        for (auto secondItr : typeItr())
        {
            if (itr != secondItr && filePathMap[itr] == filePathMap[secondItr])
            {
                std::string str = "jsonファイル : " + std::to_string(static_cast<int>(itr)) + "は二重にロードされています。";
                checkError.CreateErrorMessage(str);
            }
        }
        std::ifstream ifs(filePathMap [itr] );
        rapidjson::IStreamWrapper isw(ifs);
        m_doc[itr].ParseStream(isw);
    }
}
