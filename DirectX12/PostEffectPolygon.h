#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <memory>

#include"DirectXManager.h"
class RenderTargetTexture;
using namespace Microsoft::WRL;
class PostEffectPolygon
{
public:
	// �Q�b�^�[
	ID3D12PipelineState* GetPipelineState()const { return m_pipeline.Get(); }            //  �p�C�v���C���X�e�[�g
	ID3D12RootSignature* GetRootSignature()const { return m_rootSignature.Get(); }       //  ���[�g�V�O�l�`��

	D3D12_VERTEX_BUFFER_VIEW GetVBV()const { return m_pfVBV; };



	PostEffectPolygon(DirectXManager& _dx12);
	~PostEffectPolygon();
	void InitData(const LPCWSTR& _vertexShaderFileName, const LPCWSTR& _pixelShaderFileName,RenderTargetTexture* _renderTargetTexture);
	bool Create();
private:
	bool CreateVB();
	bool CreateRootSignature();
	bool CreateGraphicsPipeline();

	//  �V�F�[�_�[�ɓn�������̃`�F�b�N
	bool CheckShaderCompileResult(HRESULT _result, ID3DBlob* _error = nullptr);
	DirectXManager& m_dx12;
	ComPtr<ID3D12Resource>		m_pfVertBuff		=	nullptr;
	D3D12_VERTEX_BUFFER_VIEW	m_pfVBV				=	{};

	//  Fade�p�p�C�v���C��
	ComPtr<ID3D12PipelineState> m_pipeline = nullptr;
	//  Fade�p���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;


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
	LPCWSTR m_vertexSharderFileName;
	LPCWSTR m_pixelSharderFileName;
	RenderTargetTexture* m_renderTargetTexture;
};
