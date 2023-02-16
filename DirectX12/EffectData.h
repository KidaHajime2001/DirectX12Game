#pragma once
#pragma once
#include <string>
#include <unordered_map>

#include "EffectType.h"

//  エフェクトのロードに必要なデータの集合体
namespace EffectData
{
    //  ファイルへのパス
    std::unordered_map<EffectType, const wchar_t*> PATH_MAP =
    {
        {EffectType::AppearancePlayer,L"Data/Effect/Player/Appearance.efk"},
        {EffectType::DamagePlayer,L"Data/Effect/Player/Damage.efk"},
        {EffectType::DefeatPlayer,L"Data/Effect/Player/diff.efk"},
        {EffectType::PlayerMove,L"Data/Effect/Player/move.efk"},

        {EffectType::AppearanceEnemy,L"Data/Effect/Enemy/Appearance.efk"},
        {EffectType::DefeatHigherEnemy, L"Data/Effect/Enemy/BossEffect.efk"},
        {EffectType::DefeatLesserEnemy, L"Data/Effect/Enemy/EnemyDie.efk"},
        {EffectType::DefeatYellowEnemy, L"Data/Effect/Enemy/Yellow.efk"},

        {EffectType::Bullet, L"Data/Effect/Bullet/Bullet.efk"},
        {EffectType::Shoot, L"Data/Effect/Bullet/OrangeBall.efk"},


        {EffectType::DebugPos,L"Data/Effect/debug.efk" }
    };

    //  テクスチャなどが保存されてるファイルへのパス
    std::unordered_map<EffectType, const wchar_t*> FILE_MAP =
    {
        {EffectType::AppearancePlayer,L"Data/Effect/Player"},
        {EffectType::DamagePlayer,L"Data/Effect/Player"},
        {EffectType::DefeatPlayer,L"Data/Effect/Player"},
        {EffectType::PlayerMove,L"Data/Effect/Enemy"},
        {EffectType::AppearanceEnemy,L"Data/Effect/Enemy"},
        {EffectType::DefeatHigherEnemy, L"Data/Effect/Enemy"},
        {EffectType::DefeatLesserEnemy, L"Data/Effect/Enemy"},
        {EffectType::DefeatYellowEnemy, L"Data/Effect/Enemy"},

        {EffectType::Bullet, L"Data/Effect/Bullet"},
        {EffectType::Shoot, L"Data/Effect/Bullet"},


        {EffectType::DebugPos,L"Data/Effect"}
    };

    //  拡大率
    std::unordered_map<EffectType, const float> MAGNIFICATION_MAP =
    {
        {EffectType::AppearancePlayer, 1.5f},
        {EffectType::DamagePlayer,1.0f},
        {EffectType::DefeatPlayer, 1.0f},
        {EffectType::PlayerMove, 1.0f},
        {EffectType::AppearanceEnemy, 1.5f},
        {EffectType::DefeatHigherEnemy, 3.0f},
        {EffectType::DefeatLesserEnemy, 3.0f},
        {EffectType::DefeatYellowEnemy, 3.0f},

        {EffectType::Bullet, 10.0f},
        {EffectType::Shoot, 2.0f},

        {EffectType::DebugPos,1.0f}
    };
};