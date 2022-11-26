#pragma once
#include <unordered_map>

#include "SoundType.h"
//  音のロードに必要なデータ
namespace SoundData
{
    //  ファイルへのパス
    std::unordered_map<SoundType, const wchar_t*> PATH_MAP =
    {
        {SoundType::TitleBGM,L"Data/Sound/BGM/k006.wav"},
        {SoundType::SelectSE,L"Data/Sound/SE/button36.wav"},
        {SoundType::GameSceneBGM,L"Data/Sound/BGM/w006.wav"},

        {SoundType::ResultBGM,L"Data/Sound/BGM/ResultBGM.wav"},
  
        {SoundType::DefeatPlayerSE,L"Data/Sound/SE/DefeatPlayer.wav"},

        {SoundType::DefeatEnemySE,L"Data/Sound/SE/Burn.wav"},
        {SoundType::DefeatLesserEnemySE,L"Data/Sound/SE/Burn2.wav" },

        {SoundType::ScoreSE,L"Data/Sound/SE/SCORE.wav"},
        {SoundType::ShootSE,L"Data/Sound/SE/ショット音.wav"},

    };

    //  初期音量
    std::unordered_map<SoundType, float> FIRST_VOLUME =
    {
        {SoundType::TitleBGM,0.3f},
        {SoundType::SelectSE,0.1f},
        {SoundType::GameSceneBGM,0.2f},

        {SoundType::ResultBGM,0.01f},

        {SoundType::DefeatPlayerSE,0.01f},

        {SoundType::DefeatEnemySE,0.4f},
        {SoundType::DefeatLesserEnemySE,0.1f},


        {SoundType::ScoreSE,0.1f},
        {SoundType::ShootSE,0.05f},


    };
    //  初期音量
    std::unordered_map<SoundType, SoundVolumeType> VOLUME_TYPE =
    {
        {SoundType::TitleBGM,SoundVolumeType::BGM},
        {SoundType::SelectSE,SoundVolumeType::SE},
        {SoundType::GameSceneBGM,SoundVolumeType::BGM},

        {SoundType::ResultBGM,SoundVolumeType::SE},

        {SoundType::DefeatPlayerSE,SoundVolumeType::SE},

        {SoundType::DefeatEnemySE,SoundVolumeType::SE},
        {SoundType::DefeatLesserEnemySE,SoundVolumeType::SE},


        {SoundType::ScoreSE,SoundVolumeType::SE},
        {SoundType::ShootSE,SoundVolumeType::SE},


    };
};