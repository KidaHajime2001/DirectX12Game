#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <memory>

#include"DirectXManager.h"
using namespace Microsoft::WRL;

//  PMD用のレンダラーの設定を行うクラス
class PMDRenderer
{
    friend class PMDLoader;
public:
    PMDRenderer(class DirectXManager& _dx12);
    ~PMDRenderer();

    //  ゲッター
    ID3D12PipelineState* GetPipelineState()const { return m_pipeline.Get(); }            //  パイプラインステート
    ID3D12PipelineState* GetLinePipelineState()const { return m_lineDrawerPipeline.Get(); }            //  パイプラインステート
    ID3D12RootSignature* GetRootSignature()const { return m_rootSignature.Get(); }       //  ルートシグネチャ

private:
    DirectXManager& m_dx12;
    template<typename T>
    using ComPtr = ComPtr<T>;

    //  PMD用パイプライン
    ComPtr<ID3D12PipelineState> m_pipeline = nullptr;
    //  PMD用パイプライン
    ComPtr<ID3D12PipelineState> m_lineDrawerPipeline = nullptr;
    //  PMD用ルートシグネチャ
    ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;    

    //  PMD用共通テクスチャ
    ComPtr<ID3D12Resource> m_whiteTex = nullptr;    //  白
    ComPtr<ID3D12Resource> m_blackTex = nullptr;    //  黒    
    ComPtr<ID3D12Resource> m_gradTex = nullptr;     //  グレースケールグラデーション

    //  テクスチャの生成
    ID3D12Resource* CreateDefaultTexture(const size_t _width, const size_t _height);    //  標準
    ID3D12Resource* CreateWhiteTexture();                //  白
    ID3D12Resource* CreateBlackTexture();                //  黒
    ID3D12Resource* CreateGrayGradationTexture();        //  グレースケールグラデーション

    //  PMD用のパイプラインの生成
    HRESULT CreateGraphicsPipelineForPMD();
    //  PMD用のパイプラインの生成
    HRESULT CreateGraphicsPipelineForLinePMD();
    
    //  ルートシグネチャの生成
    HRESULT CreateRootSignature();

    //  シェーダーに渡せたかのチェック
    bool CheckShaderCompileResult(HRESULT _result, ID3DBlob* _error = nullptr);
};