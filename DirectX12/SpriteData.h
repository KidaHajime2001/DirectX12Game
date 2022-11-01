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
        { SpriteType::TitleBack,L"Data/Img/Title/NEOHACK.png" },
        { SpriteType::TitleText,L"Data/Img/Title/Titlename.png" },
        { SpriteType::TitleStart,L"Data/Img/Title/STARTTRUE.png" },
        { SpriteType::TitleStartFalse ,L"Data/Img/Title/STARTFALSE.png" },
        { SpriteType::TitleOption,L"Data/Img/Title/OPTIONTRUE.png" },
        { SpriteType::TitleOptionFalse,L"Data/Img/Title/OPTIONFALSE.png" },
        { SpriteType::TitleView,L"Data/Img/Title/view.png" },
        { SpriteType::GameBackGround,L"Data/Img/GameScene/backgroundColor.png" },
        { SpriteType::GameScoreTest,L"Data/Img/GameScene/UI.png" },
        { SpriteType::Gauge,L"Data/Img/GameScene/Gauge.png" },
        { SpriteType::GaugeFrame,L"Data/Img/GameScene/GaugeFrame.png" },

        { SpriteType::Font0,L"Data/Img/Font/0.png" },
        { SpriteType::Font1,L"Data/Img/Font/1.png" },
        { SpriteType::Font2,L"Data/Img/Font/2.png" },
        { SpriteType::Font3,L"Data/Img/Font/3.png" },
        { SpriteType::Font4,L"Data/Img/Font/4.png" },
        
        { SpriteType::Font5,L"Data/Img/Font/5.png" },
        { SpriteType::Font6,L"Data/Img/Font/6.png" },
        { SpriteType::Font7,L"Data/Img/Font/7.png" },
        { SpriteType::Font8,L"Data/Img/Font/8.png" },
        { SpriteType::Font9,L"Data/Img/Font/9.png" },

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