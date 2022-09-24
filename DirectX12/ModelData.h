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
        {PMDModelType::Player,"Data/Model/Player/Player.pmd"},

        //  �G�l�~�[
        {PMDModelType::RedEnemy,"Data/Model/Enemy/RedEnemy.pmd"},
        {PMDModelType::BlueEnemy,"Data/Model/��������.pmd"},
        {PMDModelType::YellowEnemy,"Data/Model/Enemy/YellowEnemy.pmd"},

        //  �e
        {PMDModelType::AimingBullet,"Data/Model/Bullet/RedBullet.pmd"},
        {PMDModelType::NoAimingBullet,"Data/Model/Bullet/BlueBullet.pmd"},
        {PMDModelType::ZigzagBullet,"Data/Model/Bullet/Zigzag.pmd"},
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
        {PMDModelType::Ground,"Data/Model/Others/Ground.pmd"},

        //  �w�i
        {PMDModelType::BackGround,"Data/Model/Others/UnderGround.pmd"}
    };
};