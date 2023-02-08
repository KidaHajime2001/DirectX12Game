#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <memory>

#include"DirectXManager.h"
using namespace Microsoft::WRL;
class Fade
{
public:
	Fade(DirectXManager& _dx12);
	~Fade();
    // ゲッター
    ID3D12PipelineState * GetPipelineState()const { return m_pipeline.Get(); }            //  パイプラインステート
    ID3D12RootSignature* GetRootSignature()const { return m_rootSignature.Get(); }       //  ルートシグネチャ
    void FadeStart();
    void FadeEnd();
    enum class FadeState
    {
        neutral,
        Fadeing,
    };
    const FadeState GetState();

    bool IsEnd() { return m_isEnd; };
	void Update();
	void Draw();
private:
    DirectXManager& m_dx12;

    //  Fade用パイプライン
    ComPtr<ID3D12PipelineState> m_pipeline = nullptr;
    //  Fade用ルートシグネチャ
    ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;

    //  PMD用のパイプラインの生成
    HRESULT CreateGraphicsPipelineForFade();

    //  ルートシグネチャの生成
    HRESULT CreateRootSignature();

    void CreateVB();
    void CreateIB();
    ComPtr<ID3D12Resource>vertBuff = nullptr;
    D3D12_VERTEX_BUFFER_VIEW vbView = {};
    ComPtr<ID3D12Resource> idxBuff = nullptr;
    D3D12_INDEX_BUFFER_VIEW ibView = {};
    struct WipeParam {
        XMFLOAT2 wipeDir;    //【注目】ワイプする方向
        float wipeSize;     //ワイプサイズ
        XMFLOAT2 rectSize;
    };
    WipeParam* m_wipeSize;
    ComPtr<ID3D12DescriptorHeap> basicDescHeap = nullptr;
    D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
    //通常テクスチャビュー作成
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};

    //  シェーダーに渡せたかのチェック
    bool CheckShaderCompileResult(HRESULT _result, ID3DBlob* _error = nullptr);
    //-1
    const float WIPECODE_FADEIN = -1;
    //1
    const float WIPECODE_FADEOUT = 1;
    const float FADESPEED = 50.0f;
    const float WIPESIZE_MAX=3500.0f;
    const float WIPESIZE_MIN=0.0f;
    const XMFLOAT2 WIPEDIR_FADE_OUT = { 1.0f,1.0f };

    bool m_nowFadeIn;
    bool m_isEnd=false;
    bool m_once=false;
    bool m_fadeOut=false;
    FadeState m_state;
    void Init();
};