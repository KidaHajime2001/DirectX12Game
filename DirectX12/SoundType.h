#pragma once

//  ���̎��
enum class SoundType {
    //  �^�C�g��
    TitleBGM = 0,           //  BGM
    SelectSE,
    //  �Q�[���V�[��
    GameSceneBGM,       //  BGM

    //  ���U���g
    ResultBGM,          //  BGM

    //  �v���C���[
    DefeatPlayerSE,     //  ���j

    //  �G�l�~�[
    DefeatEnemySE,      //  ���j
    DefeatLesserEnemySE,
    ScoreSE,
    //  �e
    ShootSE,        //  ����

    //  enum�̃��X�g
    EndSound
};
enum class SoundVolumeType
{
    BGM,
    SE,
};