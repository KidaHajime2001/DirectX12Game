#include "PostEffectPolygon.h"
#include <d3dx12.h>
#include <d3dcompiler.h>
#include <cassert>
#include <string>
#include <algorithm>
#include"Controller.h"
#include"Singleton.h"
PostEffectPolygon::PostEffectPolygon(DirectXManager& _dx12)
	:m_dx12(_dx12)
{
}

PostEffectPolygon::~PostEffectPolygon()
{
}

void PostEffectPolygon::InitData(const LPCWSTR& _vertexShaderFileName, const LPCWSTR& _pixelShaderFileName, RenderTargetTexture* _renderTargetTexture)
{
	m_vertexSharderFileName	=	_vertexShaderFileName;
	m_pixelSharderFileName	=	_pixelShaderFileName;
	m_renderTargetTexture	=	_renderTargetTexture;
}

bool PostEffectPolygon::Create()
{
	if (CreateVB())
	{
		return false;
	};
	if (CreateRootSignature())
	{
		return false;
	};
	if (CreateGraphicsPipeline())
	{
		return false;
	}
	
	return true;
}

bool PostEffectPolygon::CreateVB()
{
	auto resDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(m_postEffectVertex));
	auto prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto result = m_dx12.GetDevice()->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(m_pfVertBuff.ReleaseAndGetAddressOf())
	);

	m_pfVBV.BufferLocation=m_pfVertBuff->GetGPUVirtualAddress();
	m_pfVBV.StrideInBytes = sizeof(m_postEffectVertex);
	m_pfVBV.StrideInBytes = sizeof(PostEffectVertex);

	PostEffectVertex* mapVertex = nullptr;

	m_pfVertBuff->Map(0, nullptr, (void**)&mapVertex);
	std::copy(std::begin(m_postEffectVertex), std::end(m_postEffectVertex),mapVertex);
	m_pfVertBuff->Unmap(0, nullptr);
	

	return result;
}

bool PostEffectPolygon::CreateRootSignature()
{
	//  �����W
	CD3DX12_DESCRIPTOR_RANGE  descTblRanges[1] = {};    //  �e�N�X�`���ƒ萔�̂Q��
	descTblRanges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);    //  �萔[b0](�r���[�v���W�F�N�V�����p)
	//descTblRanges[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);    //  �萔[b1](���[���h�A�{�[���p)
	/*D3D12_DESCRIPTOR_RANGE range = {};
	range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	range.BaseShaderRegister = 0;
	range.NumDescriptors = 1;*/



	D3D12_ROOT_PARAMETER rootparam = {};
	rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootparam.DescriptorTable.pDescriptorRanges = &descTblRanges[0];//�f�X�N���v�^�����W�̃A�h���X
	rootparam.DescriptorTable.NumDescriptorRanges = 1;//�f�X�N���v�^�����W��
	rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//�S�ẴV�F�[�_���猩����

	//D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
	//samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//���J��Ԃ�
	//samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//�c�J��Ԃ�
	//samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//���s�J��Ԃ�
	//samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;//�{�[�_�[�̎��͍�
	//samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;//��Ԃ��Ȃ�(�j�A���X�g�l�C�o�[)
	//samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;//�~�b�v�}�b�v�ő�l
	//samplerDesc.MinLOD = 0.0f;//�~�b�v�}�b�v�ŏ��l
	//samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;//�I�[�o�[�T���v�����O�̍ۃ��T���v�����O���Ȃ��H
	//samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;//�s�N�Z���V�F�[�_����̂݉�amplerDescs[1].Init(1, D3D12_FILTER_ANISOTROPIC, D3D12_TEXTURE_ADDRESS_MODE_CLAMP, D3D12_TEXTURE_ADDRESS_MODE_CLAMP);

	D3D12_STATIC_SAMPLER_DESC sampler = CD3DX12_STATIC_SAMPLER_DESC(0);


	//  ���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};/*
	rootSignatureDesc.Init(1, &rootparam, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);*/
	rootSignatureDesc.NumParameters = 1;
	rootSignatureDesc.pParameters = &rootparam;
	rootSignatureDesc.NumStaticSamplers = 1;
	rootSignatureDesc.pStaticSamplers = &sampler;
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//  ���[�g�V�O�l�`���̐���
	ComPtr<ID3DBlob> rootSigBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	auto result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &rootSigBlob, &errorBlob);
	if (FAILED(result)) {
		assert(SUCCEEDED(result));
		return result;
	}
	result = m_dx12.GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(m_rootSignature.ReleaseAndGetAddressOf()));
	if (FAILED(result)) {
		assert(SUCCEEDED(result));
		return result;
	}
	return result;
}

bool PostEffectPolygon::CreateGraphicsPipeline()
{

	//  �V�F�[�_�[�̐ݒ�
	 //�@�o�C�i���f�[�^�\����
	ComPtr<ID3DBlob> vsBlob = nullptr;
	ComPtr<ID3DBlob> psBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;


	if (m_vertexSharderFileName == nullptr) {
		MessageBoxA(nullptr, "���_�V�F�[�_�[�t�@�C�����w�肳��Ă��܂���B", "�G���[", MB_OK);
		std::abort();
	}
	

	if (m_pixelSharderFileName== nullptr) {
		MessageBoxA(nullptr, "���_�V�F�[�_�[�t�@�C�����w�肳��Ă��܂���B", "�G���[", MB_OK);
		std::abort();
	}
	




	//  �V�F�[�_�[���R���p�C��
	//�@BasicShader.hlsl�����_�V�F�[�_�[
	auto result = D3DCompileFromFile(m_vertexSharderFileName,
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"BasicVS", "vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0, &vsBlob, &errorBlob);
	if (!CheckShaderCompileResult(result, errorBlob.Get())) {
		assert(0);
		return result;
	}

	//  �V�F�[�_�[���R���p�C��
   //�@BasicShader.hlsl���s�N�Z���V�F�[�_�[
	result = D3DCompileFromFile(m_pixelSharderFileName,
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"BasicPS", "ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0, &psBlob, &errorBlob);
	if (!CheckShaderCompileResult(result, errorBlob.Get())) {
		assert(0);
		return result;
	}



	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 },
	};


	//  �O���t�B�b�N�X�p�C�v���C���X�e�[�g�̐ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline = {};
	gpipeline.pRootSignature = m_rootSignature.Get();
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;    //  ���g��0xffffffff

	gpipeline.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);

	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;    //  �J�����O���Ȃ�
	gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;

	gpipeline.DepthStencilState.DepthEnable = true;    //  �[�x�o�b�t�@���g��
	gpipeline.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;    //  �S�ď�������
	gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;        //  �����������̗p
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	gpipeline.DepthStencilState.StencilEnable = false;

	gpipeline.InputLayout.pInputElementDescs = inputLayout;       //  ���C�A�E�g�擪�A�h���X
	gpipeline.InputLayout.NumElements = _countof(inputLayout);    //  ���C�A�E�g�z��

	gpipeline.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;     //  �X�g���b�v���̃J�b�g�Ȃ�
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;    //  �O�p�`�ō\��

	gpipeline.NumRenderTargets = 1;    //  ���͂P�̂�
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;    //  0�`1�ɐ��K�����ꂽRGBA

	gpipeline.SampleDesc.Count = 1;        //  �T���v�����O��1�s�N�Z���ɂ��P
	gpipeline.SampleDesc.Quality = 0;      //  �N�I���e�B�͍Œ�
		//  �O���t�B�b�N�X�p�C�v���C���X�e�[�g�̐���
	result = m_dx12.GetDevice()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(m_pipeline.ReleaseAndGetAddressOf()));
	if (FAILED(result)) {
		assert(SUCCEEDED(result));
	}
	return result;
}

bool PostEffectPolygon::CheckShaderCompileResult(HRESULT _result, ID3DBlob* _error)
{
	if (FAILED(_result)) {
		if (_result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) {
			::OutputDebugStringA("�t�@�C������������܂���");
		}
		else {
			std::string errstr;
			errstr.resize(_error->GetBufferSize());
			std::copy_n((char*)_error->GetBufferPointer(), _error->GetBufferSize(), errstr.begin());
			errstr += "\n";
			OutputDebugStringA(errstr.c_str());
		}
		return false;
	}
	else {
		return true;
	}
}
