#pragma once
#include"DirectXManager.h"
class PeraRender
{
public:
	PeraRender(DirectXManager& _dx12);
	~PeraRender();
	void CreatePeraPolygonResouce();
	void CreateRTV();
	void CreateSRV();
	void BeginDraw();
	void Draw();

	void AfterDraw();

	void CreateVartex();
	void CreateRootSignature();
private:
	ComPtr<ID3D12Resource> _peraResouce;

	DirectXManager& m_dx12;
	ComPtr<ID3D12DescriptorHeap> _peraRTVHeap;
	ComPtr<ID3D12DescriptorHeap> _peraSRVHeap;

	struct PostEffectVertex
	{
		XMFLOAT3 pos;
		XMFLOAT2 uv;
	};
	PostEffectVertex m_postEffectVertex[4] = {
		{{	-1.0f,	-1.0f,	0.0f},		{0.0f,1.0f}},
		{{	-1.0f,	1.0f,	0.0f},		{0.0f,0.0f}},
		{{	1.0f,	-1.0f,	0.0f},		{1.0f,1.0f}},
		{{	1.0f,	1.0f,	0.0f},		{1.0f,0.0f}},
	};

	ComPtr<ID3D12Resource>		m_pfVertBuff = nullptr;
	D3D12_VERTEX_BUFFER_VIEW	m_pfVBV = {};

	//  Fade用パイプライン
	ComPtr<ID3D12PipelineState> m_pipeline = nullptr;
	//  Fade用ルートシグネチャ
	ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;
};