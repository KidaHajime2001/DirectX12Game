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
        {PMDModelType::Player,"Data/Model/Player/newPlayer.pmd"},
         {PMDModelType::PlayerCube,"Data/Model/Player/cube.pmd"},
        //  エネミー
        {PMDModelType::StraightEnemy,"Data/Model/Enemy/Enemy_St.pmd"},
        {PMDModelType::SpreadEnemy,"Data/Model/Enemy/Enemy_S.pmd"},
        {PMDModelType::LesserEnemy,"Data/Model/Enemy/Enemy_L.pmd"},
        {PMDModelType::BlueEnemy,"Data/Model/TestPMX/box.pmd"},
        {PMDModelType::YellowEnemy,"Data/Model/Enemy/YellowEnemy.pmd"},

        //  弾
        {PMDModelType::AimingBullet,"Data/Model/Bullet/bullet.pmd"},
        {PMDModelType::NoAimingBullet,"Data/Model/Bullet/BlueBullet.pmd"},
        {PMDModelType::PlayerBullet,"Data/Model/Bullet/PlayerShot.pmd"},
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
        {PMDModelType::Ground,"Data/Model/Others/testg.pmd"},
        {PMDModelType::GroundCube,"Data/Model/Others/BackGroundCube.pmd"},
        //  背景
        {PMDModelType::BackGround,"Data/Model/Others/BackGroundCircle.pmd"}
    };
};