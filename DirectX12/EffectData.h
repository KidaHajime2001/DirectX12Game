#pragma once
#pragma once
#include <string>
#include <unordered_map>

#include "EffectType.h"

//  �G�t�F�N�g�̃��[�h�ɕK�v�ȃf�[�^�̏W����
namespace EffectData
{
    //  �t�@�C���ւ̃p�X
    std::unordered_map<EffectType, const wchar_t*> PATH_MAP =
    {
        {EffectType::AppearancePlayer,L"Data/Effect/Player/Appearance.efk"},
        {EffectType::DamagePlayer,L"Data/Effect/Player/Damage.efk"},
        {EffectType::DefeatPlayer,L"Data/Effect/Player/Defeat.efk"},

        {EffectType::AppearanceEnemy,L"Data/Effect/Enemy/Appearance.efk"},
        {EffectType::DefeatRedEnemy, L"Data/Effect/Enemy/Red.efk"},
        {EffectType::DefeatBlueEnemy, L"Data/Effect/Enemy/Blue.efk"},
        {EffectType::DefeatYellowEnemy, L"Data/Effect/Enemy/Yellow.efk"},

        {EffectType::Bullet, L"Data/Effect/Bullet/Bullet.efk"},
        {EffectType::Shoot, L"Data/Effect/Bullet/OrangeBall.efk"},

        {EffectType::BlackObstacle, L"Data/Effect/Obstacle/Black.efk"},
        {EffectType::RedObstacle, L"Data/Effect/Obstacle/Red.efk"},
        {EffectType::BlueObstacle, L"Data/Effect/Obstacle/Blue.efk"},
        {EffectType::YellowObstacle, L"Data/Effect/Obstacle/Yellow.efk"},
        {EffectType::RainbowObstacle, L"Data/Effect/Obstacle/Rainbow.efk"},
        {EffectType::BreakRedObstacle, L"Data/Effect/Obstacle/HitRedCube.efk"},
        {EffectType::BreakBlueObstacle, L"Data/Effect/Obstacle/HitBlueCube.efk"},
        {EffectType::BreakYellowObstacle, L"Data/Effect/Obstacle/HitYellowCube.efk"},
        {EffectType::BreakRainbowObstacle, L"Data/Effect/Obstacle/BreakRainbow.efk"},
        {EffectType::ActivateRedTower,L"Data/Effect/Obstacle/ActivateRedCube.efk"},
        {EffectType::ActivateBlueTower,L"Data/Effect/Obstacle/ActivateBlueCube.efk"},
        {EffectType::ActivateYellowTower,L"Data/Effect/Obstacle/ActivateYellowCube.efk"},
        {EffectType::ActivatePedestal,L"Data/Effect/Obstacle/ActivatePedestal.efk"},

        {EffectType::DebugPos,L"Data/Effect/debug.efk" }
    };

    //  �e�N�X�`���Ȃǂ��ۑ�����Ă�t�@�C���ւ̃p�X
    std::unordered_map<EffectType, const wchar_t*> FILE_MAP =
    {
        {EffectType::AppearancePlayer,L"Data/Effect/Player"},
        {EffectType::DamagePlayer,L"Data/Effect/Player"},
        {EffectType::DefeatPlayer,L"Data/Effect/Player"},

        {EffectType::AppearanceEnemy,L"Data/Effect/Enemy"},
        {EffectType::DefeatRedEnemy, L"Data/Effect/Enemy"},
        {EffectType::DefeatBlueEnemy, L"Data/Effect/Enemy"},
        {EffectType::DefeatYellowEnemy, L"Data/Effect/Enemy"},

        {EffectType::Bullet, L"Data/Effect/Bullet"},
        {EffectType::Shoot, L"Data/Effect/Bullet"},

        {EffectType::BlackObstacle, L"Data/Effect/Obstacle"},
        {EffectType::RedObstacle, L"Data/Effect/Obstacle"},
        {EffectType::BlueObstacle, L"Data/Effect/Obstacle"},
        {EffectType::YellowObstacle, L"Data/Effect/Obstacle"},
        {EffectType::RainbowObstacle, L"Data/Effect/Obstacle"},
        {EffectType::BreakRedObstacle, L"Data/Effect/Obstacle"},
        {EffectType::BreakBlueObstacle, L"Data/Effect/Obstacle"},
        {EffectType::BreakYellowObstacle, L"Data/Effect/Obstacle"},
        {EffectType::BreakRainbowObstacle, L"Data/Effect/Obstacle"},
        {EffectType::ActivateRedTower, L"Data/Effect/Obstacle"},
        {EffectType::ActivateBlueTower, L"Data/Effect/Obstacle"},
        {EffectType::ActivateYellowTower, L"Data/Effect/Obstacle"},
        {EffectType::ActivatePedestal, L"Data/Effect/Obstacle"},

        {EffectType::DebugPos,L"Data/Effect"}
    };

    //  �g�嗦
    std::unordered_map<EffectType, const float> MAGNIFICATION_MAP =
    {
        {EffectType::AppearancePlayer, 1.5f},
        {EffectType::DamagePlayer,1.0f},
        {EffectType::DefeatPlayer, 1.0f},

        {EffectType::AppearanceEnemy, 1.5f},
        {EffectType::DefeatRedEnemy, 3.0f},
        {EffectType::DefeatBlueEnemy, 3.0f},
        {EffectType::DefeatYellowEnemy, 3.0f},

        {EffectType::Bullet, 10.0f},
        {EffectType::Shoot, 2.0f},

        {EffectType::BlackObstacle, 2.0f},
        {EffectType::RedObstacle, 2.0f},
        {EffectType::BlueObstacle, 2.0f},
        {EffectType::YellowObstacle, 2.0f},
        {EffectType::RainbowObstacle, 2.0f},
        {EffectType::BreakRedObstacle, 2.0f},
        {EffectType::BreakBlueObstacle, 2.0f},
        {EffectType::BreakYellowObstacle, 2.0f},
        {EffectType::BreakRainbowObstacle, 2.0f},
        {EffectType::ActivateRedTower, 1.0f},
        {EffectType::ActivateBlueTower, 1.0f},
        {EffectType::ActivateYellowTower, 1.0f},
        {EffectType::ActivatePedestal, 1.0f},

        {EffectType::DebugPos,1.0f}
    };
};