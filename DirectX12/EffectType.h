#pragma once

//  �G�t�F�N�g�̎��
enum class EffectType {
    //  �v���C���[
    AppearancePlayer = 0,    //  �o��
    DamagePlayer,            //  �_���[�W
    DefeatPlayer,            //  ���j
    PlayerMove,

    //  �G�l�~�[
    AppearanceEnemy,    //  �o��
    DefeatHigherEnemy,     //  �e�F���Ƃ̌��j
    DefeatLesserEnemy,
    DefeatYellowEnemy,

    //  �e
    Bullet,       //  �e
    Shoot,        //  ����

  

    //  �f�o�b�O
    DebugPos,            //  ���W�m�F�p

    //  enum�̃��X�g
    EndEffect
};