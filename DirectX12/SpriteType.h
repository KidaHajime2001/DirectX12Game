#pragma once

//  画像の種類
//  NOTE: enum classにするとエラーが発生
//  TODO: 上記のエラーの原因調査
enum SpriteType
{
    //  タイトル
    TitleBack = 0,    //  背景


    Credit,
    //  ゲームシーン
    GameScoreTest,
    GameBackGround,
    Wave1Start,
    ControllTitle,
    ControllGame,
    ControllResult,
    ControllCredit,
    count1,
    count2,
    count3,
    count4,
    count5,
    count6,
    count7,
    count8,
    count9,
    count10,
    shieldGauge, 
    shieldGaugeFlame,

    matrix0,
    matrix1,
    //  リザルト
    ResultBack,        //  背景
    ResultText,        //  リザルト
    ResultLine,

    //  enumのラスト
    EndDescriptors
}; 
