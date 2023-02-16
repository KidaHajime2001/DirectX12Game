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
        { SpriteType::Wave1Start,L"Data/Img/GameScene/START.png"},
        { SpriteType::Credit,L"Data/Img/Title/Credit.png"},
        { SpriteType::ControllTitle,L"Data/Img/Title/ControllTitle.png"},
        { SpriteType::ControllGame,L"Data/Img/GameScene/ControllGame.png"},
        { SpriteType::ControllCredit,L"Data/Img/Title/ControllCredit.png"},
        { SpriteType::ControllResult,L"Data/Img/GameScene/ControllResult.png"},
        { SpriteType::count1,L"Data/Img/GameScene/count1.png"},
        { SpriteType::count2,L"Data/Img/GameScene/count2.png"},
        { SpriteType::count3,L"Data/Img/GameScene/count3.png"},
        { SpriteType::count4,L"Data/Img/GameScene/count4.png"},
        { SpriteType::count5,L"Data/Img/GameScene/count5.png"},

        { SpriteType::count6,L"Data/Img/GameScene/count6.png"},
        { SpriteType::count7,L"Data/Img/GameScene/count7.png"},
        { SpriteType::count8,L"Data/Img/GameScene/count8.png"},
        { SpriteType::count9,L"Data/Img/GameScene/count9.png"},
        { SpriteType::count10,L"Data/Img/GameScene/count10.png"},
         { SpriteType::shieldGauge,L"Data/Img/GameScene/shieldGauge.png"},
         { SpriteType::shieldGaugeFlame ,L"Data/Img/GameScene/shieldGaugeFlame.png"},
        { SpriteType::GameBackGround,L"Data/Img/GameScene/backgroundColor.png" },
        { SpriteType::GameScoreTest,L"Data/Img/GameScene/UI.png" },
        { SpriteType::matrix0,L"Data/Img/Title/0s.png" },
        { SpriteType::matrix1,L"Data/Img/Title/1s.png" },

        { SpriteType::ResultBack,L"Data/Img/GameScene/Gray.png" },
        { SpriteType::ResultText,L"Data/Img/GameScene/test5.png" },
        { SpriteType::ResultLine,L"Data/Img/GameScene/result4.png" },

    };


};