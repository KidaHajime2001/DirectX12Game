#pragma once
#include <unordered_map>
#include <string>

#include "ModelTypeData.h"

//  PMDModel�̃��[�h�p�f�[�^
namespace PMDModelData
{
    //  �e���f���̃t�@�C���ւ̃p�X
    std::unordered_map<PMDModelType, const std::string> FILE_PATH =
    {
        //  �v���C���[
        {PMDModelType::Player,"Data/Model/Player/newPlayer.pmd"},
         {PMDModelType::PlayerCube,"Data/Model/Player/cube.pmd"},
        //  �G�l�~�[
        {PMDModelType::StraightEnemy,"Data/Model/Enemy/Enemy_St.pmd"},
        {PMDModelType::SpreadEnemy,"Data/Model/Enemy/Enemy_S.pmd"},
        {PMDModelType::LesserEnemy,"Data/Model/Enemy/Enemy_L.pmd"},
        {PMDModelType::BlueEnemy,"Data/Model/TestPMX/box.pmd"},
        {PMDModelType::YellowEnemy,"Data/Model/Enemy/YellowEnemy.pmd"},

        //  �e
        {PMDModelType::AimingBullet,"Data/Model/Bullet/bullet.pmd"},
        {PMDModelType::NoAimingBullet,"Data/Model/Bullet/BlueBullet.pmd"},
        {PMDModelType::PlayerBullet,"Data/Model/Bullet/PlayerShot.pmd"},
        {PMDModelType::HitZigzagBullet,"Data/Model/Bullet/HitZigzag.pmd"},
        {PMDModelType::BulletShadow,"Data/Model/Bullet/BulletShadow.pmd"},

        //  �G�l�~�[��|����
        //  TODO: �e�t�@�C���̖��̂�Obstacle����EnemyDefeater�ɏC��
        //  �y��
        {PMDModelType::Pedestal,"Data/Model/Obstacle/Pedestal.pmd"},
        //  ���ɕ����Ă��闧���̕���
        {PMDModelType::RedEnemyDefeater,"Data/Model/Obstacle/RedObstacle.pmd"},
        {PMDModelType::BlueEnemyDefeater,"Data/Model/Obstacle/BlueObstacle.pmd"},
        {PMDModelType::YellowEnemyDefeater,"Data/Model/Obstacle/YellowObstacle.pmd"},

        //  �n��
        {PMDModelType::Ground,"Data/Model/Others/testg.pmd"},
        {PMDModelType::GroundCube,"Data/Model/Others/BackGroundCube.pmd"},
        //  �w�i
        {PMDModelType::BackGround,"Data/Model/Others/BackGroundCircle.pmd"}
    };
};