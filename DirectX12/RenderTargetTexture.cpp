#include"RenderTargetTexture.h"
#include <d3dx12.h>
#include"DirectXManager.h"
#include"Singleton.h"

RenderTargetTexture::RenderTargetTexture(DirectXManager& _dx12)
	:m_dx12(_dx12)
{
	
}

RenderTargetTexture::~RenderTargetTexture()
{
}

void RenderTargetTexture::BeginDraw()
{
	auto rtvHeapPointer = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();

	auto dsv=m_dsvHeap->GetCPUDescriptorHandleForHeapStart();

	auto temp = CD3DX12_RESOURCE_BARRIER::Transition(
		m_renderTargetTexture.Get(), 
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	m_dx12.GetCommandList()->ResourceBarrier(
		1,
		&temp
	);

	m_dx12.GetCommandList()->OMSetRenderTargets(
		1,
		&rtvHeapPointer,
		false, &dsv);
	//m_dx12.GetCommandList()->ClearDepthStencilView(
	//	dsv,
	//	D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
	//	1,
	//	0,
	//	0,
	//	nullptr);

}

void RenderTargetTexture::AfterDraw()
{
	auto temp = CD3DX12_RESOURCE_BARRIER::Transition(
		m_renderTargetTexture.Get(),
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET);

	m_dx12.GetCommandList()->ResourceBarrier(
		1,
		&temp
	);
}

bool RenderTargetTexture::Create(int w, int h, int mipLevel, int arraySize, DXGI_FORMAT format, DXGI_FORMAT depthStencilFormat)
{
	
	auto d3dDevice = m_dx12.GetDevice();
	m_width = w;
	m_height = h;
	//�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬����B
	if (!CreateRenderTargetTexture( d3dDevice, w, h, mipLevel, arraySize, format)) {
		//	TK_ASSERT(false, "�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���̍쐬�Ɏ��s���܂����B");
		MessageBoxA(nullptr, "�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���̍쐬�Ɏ��s���܂����B", "�G���[", MB_OK);
		return false;
	}
	//�[�x�X�e���V���o�b�t�@�ƂȂ�e�N�X�`�����쐬����B
	if (depthStencilFormat != DXGI_FORMAT_UNKNOWN) {
		if (!CreateDepthStencilTexture(d3dDevice, w, h, depthStencilFormat)) {
			MessageBoxA(nullptr, "�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���̍쐬�Ɏ��s���܂����B", "�G���[", MB_OK);
			return false;
		}
	}
	if (!CreateDescriptorHeap( d3dDevice)) {
		//�f�B�X�N���v�^�q�[�v�̍쐬�Ɏ��s�����B
		MessageBoxA(nullptr, "�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���̍쐬�Ɏ��s���܂����B", "�G���[", MB_OK);
		return false;
	}
	//�f�B�X�N���v�^���쐬����B
	CreateDescriptor(d3dDevice);
	CreateSRV(d3dDevice);
	return true;
}

bool RenderTargetTexture::CreateRenderTargetTexture(ComPtr<ID3D12Device> d3dDevice, int w, int h, int mipLevel, int arraySize, DXGI_FORMAT format)
{

	CD3DX12_RESOURCE_DESC desc(
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		0,
		static_cast<UINT>(w),
		static_cast<UINT>(h),
		arraySize,
		mipLevel,
		format,
		1,
		0,
		D3D12_TEXTURE_LAYOUT_UNKNOWN,
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	D3D12_CLEAR_VALUE clearValue;
	clearValue.Format = format;
	clearValue.Color[0] = 1.0f;
	clearValue.Color[1] = 0.0f;
	clearValue.Color[2] = 0.0f;
	clearValue.Color[3] = 1.0f;
	//���\�[�X���쐬�B
	auto prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	auto hr = d3dDevice->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&clearValue,
		IID_PPV_ARGS(m_renderTargetTexture.ReleaseAndGetAddressOf())
	);

	if (FAILED(hr)) {
		//�쐬�Ɏ��s�B
		return false;
	}
	//m_renderTargetTexture.InitFromD3DResource(m_renderTargetTextureDx12);
	return true;
}


bool RenderTargetTexture::CreateDepthStencilTexture(ComPtr<ID3D12Device> d3dDevice, int w, int h, DXGI_FORMAT format)
{
	D3D12_CLEAR_VALUE dsvClearValue;
	dsvClearValue.Format = format;
	dsvClearValue.DepthStencil.Depth = 1.0f;
	dsvClearValue.DepthStencil.Stencil = 0;

	CD3DX12_RESOURCE_DESC desc(
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		0,
		static_cast<UINT>(w),
		static_cast<UINT>(h),
		1,
		1,
		format,
		1,
		0,
		D3D12_TEXTURE_LAYOUT_UNKNOWN,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL | D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE);

	auto prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	auto hr = d3dDevice->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&dsvClearValue,
		IID_PPV_ARGS(&m_depthStencilTexture)
	);
	if (FAILED(hr)) {
		//�[�x�X�e���V���o�b�t�@�̍쐬�Ɏ��s�B
		return false;
	}
	return true;
}

void RenderTargetTexture::CreateDescriptor(ComPtr<ID3D12Device> d3dDevice)
{
	//�J���[�e�N�X�`���̃f�B�X�N���v�^���쐬�B
	auto rtvHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	d3dDevice->CreateRenderTargetView(m_renderTargetTexture.Get(), nullptr, rtvHandle);
	if (m_depthStencilTexture) {
		//�[�x�e�N�X�`���̃f�B�X�N���v�^���쐬
		auto dsvHandle = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
		d3dDevice->CreateDepthStencilView(m_depthStencilTexture.Get(), nullptr, dsvHandle);
	}
}

bool RenderTargetTexture::CreateDescriptorHeap(ComPtr<ID3D12Device> d3dDevice)
{
	//RTV�p�̃f�B�X�N���v�^�q�[�v���쐬����B
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = 1;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	d3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(m_rtvHeap.ReleaseAndGetAddressOf()));
	if (m_rtvHeap == nullptr) {
		//RTV�p�̃f�B�X�N���v�^�q�[�v�̍쐬�Ɏ��s�����B
		return false;
	}
	//�f�B�X�N���v�^�̃T�C�Y���擾�B
	m_rtvDescriptorSize = d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);


	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	//�J���[�e�N�X�`���̃f�B�X�N���v�^���쐬�B
	auto rtvHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	d3dDevice->CreateRenderTargetView(m_renderTargetTexture.Get(), &rtvDesc, rtvHandle);


	if (m_depthStencilTexture) {
		//DSV�p�̃f�B�X�N���v�^�q�[�v���쐬����B
		desc.NumDescriptors = 1;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		d3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_dsvHeap));
		if (m_dsvHeap == nullptr) {
			//DSV�p�̃f�B�X�N���v�^�q�[�v�̍쐬�Ɏ��s�����B
			return false;
		}
		//�f�B�X�N���v�^�̃T�C�Y���擾�B
		m_dsvDescriptorSize = d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	}
	return true;
}

bool RenderTargetTexture::CreateSRV(ComPtr<ID3D12Device> d3dDevice)
{
	//SRV�p�q�[�v�����
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = 1;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	auto result = d3dDevice->CreateDescriptorHeap(&desc,IID_PPV_ARGS(m_srvHeap.ReleaseAndGetAddressOf()));

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.Texture2D.MipLevels=1;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	
	if (m_srvHeap == nullptr) {
		//RTV�p�̃f�B�X�N���v�^�q�[�v�̍쐬�Ɏ��s�����B
		return false;
	}

	d3dDevice->CreateShaderResourceView(m_renderTargetTexture.Get(),
		&srvDesc,
		m_srvHeap->GetCPUDescriptorHandleForHeapStart()
	);

	return true;
}
