#pragma once
#include <tchar.h>
#include <DirectXTex.h>
#include <wrl.h>
#include"DirectXManager.h"
#include"PmdRenderer.h"
//  DXTK12
#include <SpriteFont.h>
#include <ResourceUploadBatch.h>

#pragma comment(lib,"DirectXTK12.lib")
#pragma comment(lib,"dxguid.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

class D12Device
{
public:
    D12Device();
    ~D12Device();

    //  初期化
    bool Init();

    //  デバイス
    std::shared_ptr<DirectXManager> dx12;

    class Fade* m_fade;
    //  レンダラー
    std::shared_ptr<PMDRenderer> pmdRenderer;

    //  ウィンドウハンドル
    HWND hwnd;
    
    
    //  カメラの座標を更新
    void UpdateCameraPos(const XMFLOAT3& _eye, const XMFLOAT3& _target, const XMFLOAT3& _up);
    void SetFov(float fov);
    void SetBackGroundColor(const DirectX::XMFLOAT3& _colors);
    //  フォント用ヒープ
    ComPtr<ID3D12DescriptorHeap> heapForSpriteFont;

    //  グラフィックスメモリオブジェクト
    GraphicsMemory* gmemory = nullptr;
    //  フォント表示用オブジェクト
    SpriteFont* spriteFont = nullptr;
    //  スプライト表示用オブジェクト
    SpriteBatch* spriteBatch = nullptr;

    //  後処理
    void Finalize();

    //  ウィンドウのサイズのゲッター
    SIZE GetWindowSize()const;
private:
    //  ウィンドウクラス周り
    WNDCLASSEX m_windowClass = {};

    //  ゲーム用ウィンドウの生成
    void CreateGameWindow();
};

