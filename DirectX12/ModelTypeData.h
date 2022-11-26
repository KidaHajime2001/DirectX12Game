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
    YellowEnemy,

    //  弾
    AimingBullet,       //  プレイヤーを狙う弾
    NoAimingBullet,     //  プレイヤーを狙わない球
    PlayerBullet,   //  ジグザグ攻撃の弾
    HitZigzagBullet,    //  衝突後のジグザグ攻撃の弾
    BulletShadow,   //  影

    //  エネミーを倒す塔
    //  土台
    Pedestal,
    //  宙に浮いている立方体部分
    RedEnemyDefeater,
    BlueEnemyDefeater,
    YellowEnemyDefeater,
    SpreadEnemy,
    LesserEnemy,

    //  地面
    Ground,
    GroundCube,
    //  背景
    BackGround
};