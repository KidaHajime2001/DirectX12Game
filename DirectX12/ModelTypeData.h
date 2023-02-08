#pragma once

//  PMDModelΜνή
enum class PMDModelType
{
    //  vC[
    Player = 0,
    PlayerCube,
    //  Gl~[
    StraightEnemy,
    BlueEnemy,
    EnergyItem,

    //  e
    AimingBullet,       //  vC[π_€e
    NoAimingBullet,     //  vC[π_νΘ’
    PlayerBullet,   //  WOUOUΜe
    Shield,    //  ΥΛγΜWOUOUΜe
    ShieldRing,   //  e

    //  Gl~[π|·
    //  yδ
    Pedestal,
    PowerUpItemCore,       //  vC[π_€e
    PowerUpItemShell,
    YellowEnemyDefeater,
    SpreadEnemy,
    LesserEnemy,

    //  nΚ
    Ground,
    GroundCube,
    //  wi
    BackGround
};