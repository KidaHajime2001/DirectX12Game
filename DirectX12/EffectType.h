#pragma once

//  エフェクトの種類
enum class EffectType {
    //  プレイヤー
    AppearancePlayer = 0,    //  登場
    DamagePlayer,            //  ダメージ
    DefeatPlayer,            //  撃破

    //  エネミー
    AppearanceEnemy,    //  登場
    DefeatRedEnemy,     //  各色ごとの撃破
    DefeatBlueEnemy,
    DefeatYellowEnemy,

    //  弾
    Bullet,       //  弾
    Shoot,        //  発射

    //  障害物
    BlackObstacle,        //  各色
    RedObstacle,
    BlueObstacle,
    YellowObstacle,
    RainbowObstacle,
    BreakRedObstacle,            //  各色ごとの撃破
    BreakBlueObstacle,
    BreakYellowObstacle,
    BreakRainbowObstacle,
    ActivateRedTower,           //  塔の起動
    ActivateBlueTower,
    ActivateYellowTower,
    ActivatePedestal,

    //  デバッグ
    DebugPos,            //  座標確認用

    //  enumのラスト
    EndEffect
};