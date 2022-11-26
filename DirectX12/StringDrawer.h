#pragma once
#include <wrl.h>
#include <SpriteFont.h>
#include <ResourceUploadBatch.h>

#pragma comment(lib,"DirectXTK12.lib")
#pragma comment(lib,"dxguid.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

//  定数
const float SHIFT_STRING = 2.0f;
//  文字を描画するクラス
class StringDrawer
{
public:
    StringDrawer();
    ~StringDrawer();

    //  黒い影付き白色文字の描画
    void DrawStringBlackAndWhite(const char* _string, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alpha = 1.0f, const float _rotation = 0.0f);

    //  黒い影付き白色文字の描画
    void DrawStringTitle(const char* _string, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alpha = 1.0f, const XMVECTORF32 _color=Colors::White, const float _rotation = 0.0f);
    //  黒い影付き白色整数の描画
    void DrawStringTitleForNumber(const int _num, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alpha = 1.0f, const XMVECTORF32 _color = Colors::White, const float _rotation = 0.0f);



    //  黒い影付き白色整数の描画
    void DrawStringBlackAndWhiteForNumber(const int _num, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alpha = 1.0f, const float _rotation = 0.0f);

    //  黒い影付き白色小数の描画
    void DrawStringBlackAndWhiteForFewNumber(const float _num, const XMFLOAT2& _pos, const float _scale = 1.0f, const float _alpha = 1.0f, const float _rotation = 0.0f);
    //  色を指定する時に呼び出す関数
//  ColorTypeとアルファ値を指定
    XMVECTORF32 GetColorWithalpha(const float _alpha, const XMVECTORF32 _color);
    
private:

    //  シングルトンクラスへの参照
    class D12Device& m_device;     //  デバイスの管理


};