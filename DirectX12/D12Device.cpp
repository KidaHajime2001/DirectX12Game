#include "D12Device.h"
#include <d3dx12.h>

//  ウィンドウ定数
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;


LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    //  ウィンドウが破棄されたら呼ばれる
    if (msg == WM_DESTROY) {
        //  OSに対して「もうこのアプリは終わる」と伝える
        PostQuitMessage(0);
        return 0;
    }
    //  規定の処理を行う
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

SIZE D12Device::GetWindowSize() const
{
    SIZE ret;
    ret.cx = WINDOW_WIDTH;
    ret.cy = WINDOW_HEIGHT;
    return ret;
}


D12Device::D12Device()
{
}

D12Device::~D12Device()
{
}

bool D12Device::Init()
{
    //このスレッドでCOMを使用するための準備
    auto result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    CreateGameWindow();

    //  DirectX12ラッパー生成＆初期化
    dx12.reset(new DirectXManager(hwnd));


    pmdRenderer.reset(new PMDRenderer(*dx12));

    //font関連初期化
    {
        //  GraphicsMemoryオブジェクトの初期化
        //　直接の操作はない
        //　Font表示の際に必要
        gmemory = new GraphicsMemory(dx12->GetDevice().Get());

        //  SpriteBatchMemoryオブジェクトの初期化
        ResourceUploadBatch resUploadBatch(dx12->GetDevice().Get());
        resUploadBatch.Begin();
        RenderTargetState rtState(
            DXGI_FORMAT_R8G8B8A8_UNORM,
            DXGI_FORMAT_D32_FLOAT);
        
        SpriteBatchPipelineStateDescription pd(rtState);
        pd.blendDesc=CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        pd.blendDesc.RenderTarget->BlendEnable = true;//今のところfalse
        pd.blendDesc.RenderTarget->BlendOp = D3D12_BLEND_OP_ADD;
        pd.blendDesc.RenderTarget->BlendOpAlpha = D3D12_BLEND_OP_ADD;
        pd.blendDesc.RenderTarget->SrcBlend = D3D12_BLEND_SRC_ALPHA;
        pd.blendDesc.RenderTarget->DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
        pd.blendDesc.RenderTarget->SrcBlendAlpha = D3D12_BLEND_SRC_ALPHA;
        pd.blendDesc.RenderTarget->DestBlendAlpha = D3D12_BLEND_INV_SRC_ALPHA;
        spriteBatch = new SpriteBatch(dx12->GetDevice().Get(), resUploadBatch, pd);

        //  SpriteFontオブジェクトの初期化
        heapForSpriteFont = dx12->CreateDescriptorHeapForSpriteFont();
        spriteFont = new SpriteFont(
            dx12->GetDevice().Get(),
            resUploadBatch,
            L"Data/Font/meiryo.spritefont",
            heapForSpriteFont->GetCPUDescriptorHandleForHeapStart(),
            heapForSpriteFont->GetGPUDescriptorHandleForHeapStart());

        auto future = resUploadBatch.End(dx12->GetCmdQue());        //  転送


         //  待ち
        dx12->WaitForCommandQueue();
        future.wait();
        spriteBatch->SetViewport(dx12->GetViewPort());
        
    }
	return true;
}

void D12Device::UpdateCameraPos(const XMFLOAT3& _eye, const XMFLOAT3& _target, const XMFLOAT3& _up)
{
    dx12->UpdateCameraPos(_eye,_target,_up);
}

void D12Device::SetFov(float fov)
{
    dx12->SetFov(fov);
}

void D12Device::SetBackGroundColor(const DirectX::XMFLOAT3& _colors)
{
    dx12->SetBackGroundColor(_colors);
}

void D12Device::Finalize()
{
    //  もうクラスは使わないから登録解除
    UnregisterClass(m_windowClass.lpszClassName, m_windowClass.hInstance);
}




void D12Device::CreateGameWindow()
{
    HINSTANCE hInst = GetModuleHandle(nullptr);
    //  ウィンドウクラス生成＆登録
    m_windowClass.cbSize = sizeof(WNDCLASSEX);
    m_windowClass.lpfnWndProc = (WNDPROC)WindowProcedure;    //  コールバック関数の指定
    m_windowClass.lpszClassName = _T("DirectXTest");         //  アプリケーションクラス名
    m_windowClass.hInstance = GetModuleHandle(0);            //  ハンドルの取得
    RegisterClassEx(&m_windowClass);    //  アプリケーションクラス(こういうの作るからよろしくってOSに予告する)

    RECT wrc = { 0,0, WINDOW_WIDTH, WINDOW_HEIGHT };       //  ウィンドウサイズを決める
    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);    //  ウィンドウのサイズはちょっと面倒なので関数を使って補正する
    
    //  ウィンドウオブジェクトの生成
    hwnd = CreateWindow(m_windowClass.lpszClassName,    //  クラス名指定
        _T("Game"),    //  タイトルバーの文字
        WS_POPUP | WS_BORDER,    //  タイトルバーと境界線があるウィンドウです
        CW_USEDEFAULT,    //  表示X座標はOSにお任せします
        CW_USEDEFAULT,    //  表示Y座標はOSにお任せします
        wrc.right - wrc.left,    //  ウィンドウ幅
        wrc.bottom - wrc.top,    //  ウィンドウ高
        nullptr,    //  親ウィンドウハンドル
        nullptr,    //  メニューハンドル
        m_windowClass.hInstance,    //  呼び出しアプリケーションハンドルaa
        nullptr);    //  追加パラメータ
    //SetMenu(hwnd, NULL);
}
