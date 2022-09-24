#pragma once
#include <d3d12.h>
#include <DirectXHelpers.h>
#include <DirectXMath.h>
#include <DescriptorHeap.h>
#include <SpriteBatch.h>
#include <vector>
#include <iostream>

using namespace Microsoft::WRL;
using namespace DirectX;

enum SpriteType;
//  �摜�̃��[�h��`����s���N���X
//  �V���O���g���ň���
class SpriteDrawer {
public:
    SpriteDrawer();
    ~SpriteDrawer();

    //  �`��
    void Draw(const SpriteType _handle, const XMFLOAT2& _pos, const float _magnification = 1.0f, const XMVECTOR& _color = Colors::White);
    //  �摜�̕`��͈͂��w�肷��ꍇ
    void Draw(const SpriteType _handle, const XMFLOAT2& _pos
        , const float _topMagnification, const float _leftMagnification, const float _bottomMagnification, const float _rightMagnification
        , const float _magnification = 1.0f, const XMVECTOR& _color = Colors::White);
    XMVECTORF32 GetColorWithAlfa(const float _alfa);
private:
    //  ���[�h
    int Load();

    //  �e�N�X�`���̃��[�h�֘A
    std::unique_ptr<DescriptorHeap> m_resourceDescriptors;
    std::vector<ComPtr<ID3D12Resource>> m_texture;
    std::unique_ptr<SpriteBatch> m_spriteBatch;

    //  �V���O���g���N���X�ւ̎Q��
    class D12Device& m_device;     //  �f�o�C�X�̊Ǘ�
    class CheckError& m_error;
};