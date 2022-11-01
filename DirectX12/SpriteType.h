#pragma once

//  画像の種類
//  NOTE: enum classにするとエラーが発生
//  TODO: 上記のエラーの原因調査
enum SpriteType
{
    //  タイトル
    TitleBack = 0,    //  背景
    TitleText,        //  タイトル
    TitleStart,            //  スタートの文字
    TitleStartFalse,
    TitleOption,
    TitleOptionFalse,
    TitleView,
    //  ゲームシーン
    GameScoreTest,
    GameBackGround,
    Gauge,        //  ゲージ本体
    GaugeFrame,   //  ゲージの枠
    Font0,
    Font1,
    Font2,
    Font3,
    Font4,
    Font5,
    Font6,
    Font7,
    Font8,
    Font9,
    //  リザルト
    ResultBack,        //  背景
    ResultText,        //  リザルト
    Return,            //  スタートの文字

    //  enumのラスト
    EndDescriptors
}; 
