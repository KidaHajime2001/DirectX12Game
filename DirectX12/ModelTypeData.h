#pragma once

//  PMDModel�̎��
enum class PMDModelType
{
    //  �v���C���[
    Player = 0,
    PlayerCube,
    //  �G�l�~�[
    StraightEnemy,
    BlueEnemy,
    EnergyItem,

    //  �e
    AimingBullet,       //  �v���C���[��_���e
    NoAimingBullet,     //  �v���C���[��_��Ȃ���
    PlayerBullet,   //  �W�O�U�O�U���̒e
    Shield,    //  �Փˌ�̃W�O�U�O�U���̒e
    ShieldRing,   //  �e

    //  �G�l�~�[��|����
    //  �y��
    Pedestal,
    PowerUpItemCore,       //  �v���C���[��_���e
    PowerUpItemShell,
    YellowEnemyDefeater,
    SpreadEnemy,
    LesserEnemy,

    //  �n��
    Ground,
    GroundCube,
    //  �w�i
    BackGround
};