#pragma once
#include <unordered_map>
#include <string>

#include "ModelTypeData.h"

//  PMDModelのロード用データ
namespace PMDModelData
{
    //  各モデルのファイルへのパス
    std::unordered_map<PMDModelType, const std::string> FILE_PATH =
    {
        //  プレイヤー
        {PMDModelType::Player,"Data/Model/Player/Player.pmd"},

        //  エネミー
        {PMDModelType::RedEnemy,"Data/Model/Enemy/RedEnemy.pmd"},
        {PMDModelType::BlueEnemy,"Data/Model/鏡音リン.pmd"},
        {PMDModelType::YellowEnemy,"Data/Model/Enemy/YellowEnemy.pmd"},

        //  弾
        {PMDModelType::AimingBullet,"Data/Model/Bullet/RedBullet.pmd"},
        {PMDModelType::NoAimingBullet,"Data/Model/Bullet/BlueBullet.pmd"},
        {PMDModelType::ZigzagBullet,"Data/Model/Bullet/Zigzag.pmd"},
        {PMDModelType::HitZigzagBullet,"Data/Model/Bullet/HitZigzag.pmd"},
        {PMDModelType::BulletShadow,"Data/Model/Bullet/BulletShadow.pmd"},

        //  エネミーを倒す塔
        //  TODO: 各ファイルの名称をObstacleからEnemyDefeaterに修正
        //  土台
        {PMDModelType::Pedestal,"Data/Model/Obstacle/Pedestal.pmd"},
        //  宙に浮いている立方体部分
        {PMDModelType::RedEnemyDefeater,"Data/Model/Obstacle/RedObstacle.pmd"},
        {PMDModelType::BlueEnemyDefeater,"Data/Model/Obstacle/BlueObstacle.pmd"},
        {PMDModelType::YellowEnemyDefeater,"Data/Model/Obstacle/YellowObstacle.pmd"},

        //  地面
        {PMDModelType::Ground,"Data/Model/Others/Ground.pmd"},

        //  背景
        {PMDModelType::BackGround,"Data/Model/Others/UnderGround.pmd"}
    };
};