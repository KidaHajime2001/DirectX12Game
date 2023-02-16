#pragma once

//  エフェクトの種類
enum class EffectType {
    //  プレイヤー
    AppearancePlayer = 0,    //  登場
    DamagePlayer,            //  ダメージ
    DefeatPlayer,            //  撃破
    PlayerMove,

    //  エネミー
    AppearanceEnemy,    //  登場
    DefeatHigherEnemy,     //  各色ごとの撃破
    DefeatLesserEnemy,
    DefeatYellowEnemy,

    //  弾
    Bullet,       //  弾
    Shoot,        //  発射

  

    //  デバッグ
    DebugPos,            //  座標確認用

    //  enumのラスト
    EndEffect
};