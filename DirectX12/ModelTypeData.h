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
    YellowEnemy,

    //  �e
    AimingBullet,       //  �v���C���[��_���e
    NoAimingBullet,     //  �v���C���[��_��Ȃ���
    PlayerBullet,   //  �W�O�U�O�U���̒e
    HitZigzagBullet,    //  �Փˌ�̃W�O�U�O�U���̒e
    BulletShadow,   //  �e

    //  �G�l�~�[��|����
    //  �y��
    Pedestal,
    //  ���ɕ����Ă��闧���̕���
    RedEnemyDefeater,
    BlueEnemyDefeater,
    YellowEnemyDefeater,
    SpreadEnemy,
    LesserEnemy,

    //  �n��
    Ground,
    GroundCube,
    //  �w�i
    BackGround
};