#pragma once

//  PMDModel�̎��
enum class PMDModelType
{
    //  �v���C���[
    Player = 0,

    //  �G�l�~�[
    RedEnemy,
    BlueEnemy,
    YellowEnemy,

    //  �e
    AimingBullet,       //  �v���C���[��_���e
    NoAimingBullet,     //  �v���C���[��_��Ȃ���
    ZigzagBullet,   //  �W�O�U�O�U���̒e
    HitZigzagBullet,    //  �Փˌ�̃W�O�U�O�U���̒e
    BulletShadow,   //  �e

    //  �G�l�~�[��|����
    //  �y��
    Pedestal,
    //  ���ɕ����Ă��闧���̕���
    RedEnemyDefeater,
    BlueEnemyDefeater,
    YellowEnemyDefeater,

    //  �n��
    Ground,

    //  �w�i
    BackGround
};