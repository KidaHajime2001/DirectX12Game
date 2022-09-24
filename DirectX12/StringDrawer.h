#pragma once
#include <wrl.h>
#include <SpriteFont.h>
#include <ResourceUploadBatch.h>

#pragma comment(lib,"DirectXTK12.lib")
#pragma comment(lib,"dxguid.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

//  �萔
const float SHIFT_STRING = 2.0f;
//  ������`�悷��N���X
class StringDrawer
{
public:
    StringDrawer();
    ~StringDrawer();

    //  �����e�t�����F�����̕`��
    void DrawStringBlackAndYellow(const char* _string, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alfa = 1.0f, const float _rotation = 0.0f);

    //  �����e�t�����F�����̕`��
    void DrawStringBlackAndYellowForNumber(const int _num, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alfa = 1.0f, const float _rotation = 0.0f);

    //  �����e�t�����F�����̕`��
    void DrawStringBlackAndYellowForFewNumber(const float _num, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alfa = 1.0f, const float _rotation = 0.0f);

private:

    //  �V���O���g���N���X�ւ̎Q��
    class D12Device& m_device;     //  �f�o�C�X�̊Ǘ�

   
};