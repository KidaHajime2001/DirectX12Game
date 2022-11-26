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
    void DrawStringBlackAndWhite(const char* _string, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alpha = 1.0f, const float _rotation = 0.0f);

    //  �����e�t�����F�����̕`��
    void DrawStringTitle(const char* _string, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alpha = 1.0f, const XMVECTORF32 _color=Colors::White, const float _rotation = 0.0f);
    //  �����e�t�����F�����̕`��
    void DrawStringTitleForNumber(const int _num, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alpha = 1.0f, const XMVECTORF32 _color = Colors::White, const float _rotation = 0.0f);



    //  �����e�t�����F�����̕`��
    void DrawStringBlackAndWhiteForNumber(const int _num, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alpha = 1.0f, const float _rotation = 0.0f);

    //  �����e�t�����F�����̕`��
    void DrawStringBlackAndWhiteForFewNumber(const float _num, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alpha = 1.0f, const float _rotation = 0.0f);
    //  �F���w�肷�鎞�ɌĂяo���֐�
//  ColorType�ƃA���t�@�l���w��
    XMVECTORF32 GetColorWithalpha(const float _alpha, const XMVECTORF32 _color);
    
private:

    //  �V���O���g���N���X�ւ̎Q��
    class D12Device& m_device;     //  �f�o�C�X�̊Ǘ�


};