#pragma once
#include <unordered_map>
#include <DirectXMath.h>

#include "SpriteType.h"

using namespace DirectX;

//  画像のデータ
namespace SpriteData
{
    //  ファイルへのパス
    std::unordered_map<SpriteType, const wchar_t*> FILE_PATH =
    {
        { SpriteType::TitleBack,L"Data/Img/Title/TitleBack.png" },
        { SpriteType::TitleText,L"Data/Img/Title/Titlename.png" },
        { SpriteType::TitleStart,L"Data/Img/Title/Title_button.png" },

        { SpriteType::GameBackGround,L"Data/Img/GameScene/megido_background07_1920x1080.png" },
        { SpriteType::Gauge,L"Data/Img/GameScene/Gauge.png" },
        { SpriteType::GaugeFrame,L"Data/Img/GameScene/GaugeFrame.png" },

        { SpriteType::ResultBack,L"Data/Img/GameScene/GameOver.png" },
        { SpriteType::ResultText,L"Data/Img/Result/ResultLogo.png" },
        { SpriteType::Return,L"Data/Img/Result/Return.png" },
    };

    //  元画像の大きさ
    std::unordered_map<SpriteType, const XMINT2> SPRITE_SIZE =
    {
        {SpriteType::Gauge,{1104,262}}
    };
};