#include "PeraRender.h"
#include <d3dx12.h>
#include <d3dcompiler.h>

PeraRender::PeraRender(DirectXManager& _dx12)
	:m_dx12(_dx12)
{
	CreatePeraPolygonResouce();
	CreateRTV();
	CreateRootSignature();
	CreateVartex();

}

PeraRender::~PeraRender()
{
}

void PeraRender::CreatePeraPolygonResouce()
{
	auto heapDesc = m_dx12.getrtv();
	auto bbuff = m_dx12.getbb();
	auto resDesc = bbuff->GetDesc();

	D3D12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

	float clsClr[4] = { 0.5f,0.5f,0.5f,1.0f };
	D3D12_CLEAR_VALUE clearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM, clsClr);

	auto result = m_dx12.GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&clearValue,
		IID_PPV_ARGS(_peraResouce.ReleaseAndGetAddressOf())
	);
}

void PeraRender::CreateRTV()
{
	auto heapDesc = m_dx12.getrtv();
	heapDesc.NumDescriptors = 1;
	auto result = m_dx12.GetDevice()->CreateDescriptorHeap(
		&heapDesc,IID_PPV_ARGS(_peraRTVHeap.ReleaseAndGetAddressOf())
	);
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_dx12.GetDevice()->CreateRenderTargetView(
		_peraResouce.Get(),
		&rtvDesc,
		_peraRTVHeap->GetCPUDescriptorHandleForHeapStart()
	);

	heapDesc.NumDescriptors = 1;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	result = m_dx12.GetDevice()->CreateDescriptorHeap(
		&heapDesc,
		IID_PPV_ARGS(_peraSRVHeap.ReleaseAndGetAddressOf())
	);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Format = rtvDesc.Format;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	m_dx12.GetDevice()->CreateShaderResourceView(
		_peraResouce.Get(),
		&srvDesc,
		_peraSRVHeap->GetCPUDescriptorHandleForHeapStart()
	);

}

void PeraRender::CreateSRV()
{

}

void PeraRender::BeginDraw()
{
	auto rtvHeapPointer = _peraRTVHeap->GetCPUDescriptorHandleForHeapStart();
	
	auto temp = CD3DX12_RESOURCE_BARRIER::Transition(
		_peraResouce.Get(), 
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);

	m_dx12.GetCommandList()->ResourceBarrier(
		1,
		&temp
	);
	auto dsvHeap = m_dx12.getdsv()->GetCPUDescriptorHandleForHeapStart();
	m_dx12.GetCommandList()->OMSetRenderTargets(1, &rtvHeapPointer,
		false, &dsvHeap);
}

void PeraRender::Draw()
{
	m_dx12.GetCommandList()->SetDescriptorHeaps(1,_peraSRVHeap.GetAddressOf());

	auto handle = _peraSRVHeap->GetGPUDescriptorHandleForHeapStart();

	m_dx12.GetCommandList()->SetGraphicsRootDescriptorTable(0,handle);
	m_dx12.GetCommandList()->SetGraphicsRootSignature(m_rootSignature.Get());
	m_dx12.GetCommandList()->SetPipelineState(m_pipeline.Get());


	m_dx12.GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_dx12.GetCommandList()->IASetVertexBuffers(0,1,&m_pfVBV);
	m_dx12.GetCommandList()->DrawInstanced(4,1,0,0);

}

void PeraRender::AfterDraw()
{
	auto rtvHeapPointer = _peraRTVHeap->GetCPUDescriptorHandleForHeapStart();
	auto temp = CD3DX12_RESOURCE_BARRIER::Transition(
		_peraResouce.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET
		,D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

	m_dx12.GetCommandList()->ResourceBarrier(
		1,
		&temp
	);
}

void PeraRender::CreateVartex()
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

	m_pfVBV.BufferLocation = m_pfVertBuff->GetGPUVirtualAddress();
	m_pfVBV.SizeInBytes = sizeof(m_postEffectVertex);
	m_pfVBV.StrideInBytes = sizeof(PostEffectVertex);

	PostEffectVertex* mapVertex = nullptr;

	m_pfVertBuff->Map(0, nullptr, (void**)&mapVertex);
	std::copy(std::begin(m_postEffectVertex), std::end(m_postEffectVertex), mapVertex);
	m_pfVertBuff->Unmap(0, nullptr);






	ComPtr<ID3DBlob> vsBlob = nullptr;
	ComPtr<ID3DBlob> psBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	
		
	
	//  �V�F�[�_�[���R���p�C��
	//�@BasicShader.hlsl�����_�V�F�[�_�[
	result = D3DCompileFromFile(L"TestVertexShader.hlsl",
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"BasicVS", "vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0, &vsBlob, &errorBlob);


	//  �V�F�[�_�[���R���p�C��
   //�@BasicShader.hlsl���s�N�Z���V�F�[�_�[
	result = D3DCompileFromFile(L"TestPixelShader.hlsl",
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"BasicPS", "ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0, &psBlob, &errorBlob);




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

	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	gpipeline.SampleDesc.Count = 1;        //  �T���v�����O��1�s�N�Z���ɂ��P
	gpipeline.SampleDesc.Quality = 0;      //  �N�I���e�B�͍Œ�
	gpipeline.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;

	gpipeline.pRootSignature = m_rootSignature.Get();
	result = m_dx12.GetDevice()->CreateGraphicsPipelineState(
		&gpipeline,
		IID_PPV_ARGS(m_pipeline.ReleaseAndGetAddressOf())
	);



}

void PeraRender::CreateRootSignature()
{
	//  �����W
	CD3DX12_DESCRIPTOR_RANGE  descTblRanges= {};    //  �e�N�X�`���ƒ萔�̂Q��
	descTblRanges.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);    //  �萔[b0](�r���[�v���W�F�N�V�����p)


	D3D12_ROOT_PARAMETER rootparam = {};
	rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootparam.DescriptorTable.pDescriptorRanges = &descTblRanges;//�f�X�N���v�^�����W�̃A�h���X
	rootparam.DescriptorTable.NumDescriptorRanges = 1;//�f�X�N���v�^�����W��
	rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;//�S�ẴV�F�[�_���猩����

	D3D12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);
	//samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//���J��Ԃ�
	//samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//�c�J��Ԃ�
	//samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//���s�J��Ԃ�
	//samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;//�{�[�_�[�̎��͍�
	//samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;//��Ԃ��Ȃ�(�j�A���X�g�l�C�o�[)
	//samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;//�~�b�v�}�b�v�ő�l
	//samplerDesc.MinLOD = 0.0f;//�~�b�v�}�b�v�ŏ��l
	//samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;//�I�[�o�[�T���v�����O�̍ۃ��T���v�����O���Ȃ��H
	//samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;//�s�N�Z���V�F�[�_����̂݉�amplerDescs[1].Init(1, D3D12_FILTER_ANISOTROPIC, D3D12_TEXTURE_ADDRESS_MODE_CLAMP, D3D12_TEXTURE_ADDRESS_MODE_CLAMP);






	D3D12_ROOT_SIGNATURE_DESC rsDesc = {};
	rsDesc.NumParameters = 1;
	rsDesc.NumStaticSamplers  = 1;
	rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rsDesc.pParameters = &rootparam;
	rsDesc.pStaticSamplers = &samplerDesc;

	ComPtr<ID3DBlob> rsBlob;
	ComPtr<ID3DBlob> errBlob;

	auto result = D3D12SerializeRootSignature(
		&rsDesc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		rsBlob.ReleaseAndGetAddressOf(),
		errBlob.ReleaseAndGetAddressOf()
	);

	result = m_dx12.GetDevice()->CreateRootSignature(
		0, rsBlob->GetBufferPointer(),
		rsBlob->GetBufferSize(), IID_PPV_ARGS(m_rootSignature.ReleaseAndGetAddressOf())
	);

}
