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
    //  ゲームシーン
    GameBackGround,
    Gauge,        //  ゲージ本体
    GaugeFrame,   //  ゲージの枠

    GameBackGroundCirCle,

    //  リザルト
    ResultBack,        //  背景
    ResultText,        //  リザルト
    Return,            //  スタートの文字

    //  enumのラスト
    EndDescriptors
}; 
