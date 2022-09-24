#include"SupportJSON.h"
#include"JsonDataType.h"
#include"Singleton.h"
#include"CheckError.h"
#include"EnumItr.h"
#include <fstream>
#include "rapidjson/istreamwrapper.h"
SupportJson::SupportJson()
{
    //  �t�@�C���p�X
    filePathMap =
    {
        { JsonDataType::Player,"Data/Param/PlayerData.json" },
        { JsonDataType::Enemy,"Data/Param/EnemyData.json" },
        { JsonDataType::AdventPoint,"Data/Param/Enemy_Advent.json" },
        {JsonDataType::Ground,"Data/Param/GoundData.json"},
    };

    //  �t�@�C���̃��[�h
    Load();
}

SupportJson::~SupportJson()
{
}

int SupportJson::GetInt(JsonDataType _type, const char* _dataKey,const char* _IndexString, int Index )
{
    int ret;
    if (Index==-1)
    {
        ret = m_doc[_type][_dataKey].GetInt();
    }
    else
    {
        ret = m_doc[_type][_IndexString][Index][_dataKey].GetInt();
    }

    return ret;
}

float SupportJson::Getfloat(JsonDataType _type, const char* _dataKey, const char* _IndexString, int Index )
{
    float ret;
    if (Index == -1)
    {
        ret = m_doc[_type][_dataKey].GetFloat();
    }
    
    return ret;
}

std::string SupportJson::GetString(JsonDataType _type, const char* _dataKey, const char* _IndexString, int Index )
{
    std::string ret;
    if (Index == -1)
    {
        ret = m_doc[_type][_dataKey].GetString();
    }
    else
    {
        ret = m_doc[_type][_IndexString][Index][_dataKey].GetString();
    }

    return ret;
}

DirectX::XMFLOAT3 SupportJson::GetXMFLOAT3(JsonDataType _type, const char* _dataKey, const char* _IndexString, int Index)
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
    //  �G���[�`�F�b�N�p�N���X�̃V���O���g���C���X�^���X�𓾂�
    CheckError& checkError = Singleton<CheckError>::GetInstance();

    //  �񋓌^JsonDataType�̃C�e���[�^���쐬
    typedef EnumIterator<JsonDataType, JsonDataType::Player, JsonDataType::Ground> typeItr;
    for (auto itr : typeItr())
    {
        //  ��d���[�h�̖h�~
        for (auto secondItr : typeItr())
        {
            if (itr != secondItr && filePathMap[itr] == filePathMap[secondItr])
            {
                std::string str = "json�t�@�C�� : " + std::to_string(static_cast<int>(itr)) + "�͓�d�Ƀ��[�h����Ă��܂��B";
                checkError.CreateErrorMessage(str);
            }
        }
        std::ifstream ifs(filePathMap [itr] );
        rapidjson::IStreamWrapper isw(ifs);
        m_doc[itr].ParseStream(isw);
    }
}
