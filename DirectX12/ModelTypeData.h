#pragma once

//  PMDModelの種類
enum class PMDModelType
{
    //  プレイヤー
    Player = 0,
    PlayerCube,
    //  エネミー
    StraightEnemy,
    BlueEnemy,
    EnergyItem,

    //  弾
    AimingBullet,       //  プレイヤーを狙う弾
    NoAimingBullet,     //  プレイヤーを狙わない球
    PlayerBullet,   //  ジグザグ攻撃の弾
    Shield,    //  衝突後のジグザグ攻撃の弾
    ShieldRing,   //  影

    //  エネミーを倒す塔
    //  土台
    Pedestal,
    PowerUpItemCore,       //  プレイヤーを狙う弾
    PowerUpItemShell,
    YellowEnemyDefeater,
    SpreadEnemy,
    LesserEnemy,

    //  地面
    Ground,
    GroundCube,
    //  背景
    BackGround
};