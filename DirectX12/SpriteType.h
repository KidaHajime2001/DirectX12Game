#pragma once

//  �摜�̎��
//  NOTE: enum class�ɂ���ƃG���[������
//  TODO: ��L�̃G���[�̌�������
enum SpriteType
{
    //  �^�C�g��
    TitleBack = 0,    //  �w�i
    TitleText,        //  �^�C�g��
    TitleStart,            //  �X�^�[�g�̕���
    TitleStartFalse,
    TitleOption,
    TitleOptionFalse,
    //  �Q�[���V�[��
    GameBackGround,
    Gauge,        //  �Q�[�W�{��
    GaugeFrame,   //  �Q�[�W�̘g

    GameBackGroundCirCle,

    //  ���U���g
    ResultBack,        //  �w�i
    ResultText,        //  ���U���g
    Return,            //  �X�^�[�g�̕���

    //  enum�̃��X�g
    EndDescriptors
}; 
