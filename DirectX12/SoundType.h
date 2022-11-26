#pragma once

//  音の種類
enum class SoundType {
    //  タイトル
    TitleBGM = 0,           //  BGM
    SelectSE,
    //  ゲームシーン
    GameSceneBGM,       //  BGM

    //  リザルト
    ResultBGM,          //  BGM

    //  プレイヤー
    DefeatPlayerSE,     //  撃破

    //  エネミー
    DefeatEnemySE,      //  撃破
    DefeatLesserEnemySE,
    ScoreSE,
    //  弾
    ShootSE,        //  発射

    //  enumのラスト
    EndSound
};
enum class SoundVolumeType
{
    BGM,
    SE,
};