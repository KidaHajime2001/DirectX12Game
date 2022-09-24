#pragma once
#include <DirectXMath.h>
#include <string>

using namespace DirectX;

//  �V�F�[�_�[���ɓ�������}�e���A���f�[�^
struct MaterialForHlsl
{
    XMFLOAT3 diffuse;     //  �f�B�t���[�Y�F
    float alpha;          //  �f�B�t���[�Y��
    XMFLOAT3 specular;    //  �X�y�L�����F
    float specularity;    //  �X�y�L�����̋����i��Z�l�j
    XMFLOAT3 ambient;     //  �A���r�G���g�F
};
//  ����ȊO�̃}�e���A���f�[�^
struct AdditionalMaterial
{
    std::string texPath;   //  �e�N�X�`���t�@�C���p�X
    int toonIdx;           //  �g�D�[���ԍ�
    bool edgeFlg;          //  �}�e���A�����̗֊s���t���O
};
//  �܂Ƃ߂�����
struct Material
{
    unsigned int indicesNum;    //  �C���f�b�N�X��
    MaterialForHlsl material;
    AdditionalMaterial additional;
};