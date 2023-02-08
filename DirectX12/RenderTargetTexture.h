#pragma once
#include<d3d12.h>
#include"DirectXManager.h"
#include"D12Device.h"
class RenderTargetTexture
{
public:
	RenderTargetTexture(DirectXManager& _dx12);
	~RenderTargetTexture();

	/// <summary>
	/// �`��O����
	/// </summary>
	void BeginDraw();
	void AfterDraw();
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̍쐬�B
	/// </summary>
	/// <param name="w">�����_�����O�^�[�Q�b�g�̕�</param>
	/// <param name="h">�����_�����O�^�[�Q�b�g�̍���</param>
	/// <param name="mipLevel">�~�b�v�}�b�v���x���B0���w�肵���ꍇ�̓~�b�v�}�b�v���T�|�[�g����Ă���GPU�ł�1*1�s�N�Z���܂ł̃~�b�v�}�b�v���쐬�����B</param>
	/// <param name="arraySize">�e�N�X�`���z��̃T�C�Y</param>
	/// <param name="colorFormat">�J���[�o�b�t�@�̃t�H�[�}�b�g�B</param>
	/// <param name="depthStencilFormat">�[�x�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B</param>
	/// <returns>true���Ԃ��Ă�����쐬����</returns>
	bool Create(
		int w,
		int h,
		int mipLevel,
		int arraySize,
		DXGI_FORMAT colorFormat,
		DXGI_FORMAT depthStencilFormat
	);
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬�B
	/// </summary>
	/// <param name="ge">�O���t�B�b�N�G���W��</param>
	/// <param name="d3dDevice">D3D�f�o�C�X</param>
	/// <param name="w">�e�N�X�`���̕�</param>
	/// <param name="h">�e�N�X�`���̍���</param>
	/// <param name="mipLevel">�~�b�v�}�b�v���x��</param>
	/// <param name="arraySize">�e�N�X�`���z��̃T�C�Y</param>
	/// <param name="format">�e�N�X�`���̃t�H�[�}�b�g</param>
	/// <returns>true���Ԃ��Ă����琬���B</returns>
	bool CreateRenderTargetTexture(
		ComPtr<ID3D12Device> d3dDevice,
		int w,
		int h,
		int mipLevel,
		int arraySize,
		DXGI_FORMAT format
	);
	/// <summary>
	/// �[�x�X�e���V���o�b�t�@�ƂȂ�e�N�X�`�����쐬�B
	/// </summary>
	/// <param name="ge">�O���t�B�b�N�G���W��</param>
	/// <param name="d3dDevice">D3D�f�o�C�X</param>
	/// <param name="w">�e�N�X�`���̕�</param>
	/// <param name="h">�e�N�X�`���̍���</param>
	/// <param name="format">�e�N�X�`���̃t�H�[�}�b�g</param>
	/// <returns>true���Ԃ��Ă����琬��</returns>
	bool CreateDepthStencilTexture(
		ComPtr<ID3D12Device> d3dDevice,
		int w,
		int h,
		DXGI_FORMAT format);
	/// <summary>
	/// �f�B�X�N���v�^�̍쐬�B
	/// </summary>
	/// <param name="d3dDevice">D3D�f�o�C�X</param>
	/// <returns>true���Ԃ��Ă��`�A�琬���B</returns>
	void CreateDescriptor(ComPtr<ID3D12Device> d3dDevice);

	/// <summary>
	/// �f�B�X�N���v�^�q�[�v���쐬�B
	/// </summary>
	/// <param name="ge">�O���t�B�b�N�G���W��</param>
	/// <param name="d3dDevice">D3D�f�o�C�X</param>
	/// <returns></returns>
	bool CreateDescriptorHeap(ComPtr<ID3D12Device> d3dDevice);

	bool CreateSRV(ComPtr<ID3D12Device> d3dDevice);

	ComPtr<ID3D12DescriptorHeap> GetSRV() { return m_srvHeap; };


private:
	template<typename T>
	using ComPtr = ComPtr<T>;

	DirectXManager& m_dx12;
	ComPtr<ID3D12DescriptorHeap> m_srvHeap;


	ComPtr<ID3D12Resource> m_renderTargetTexture;//�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���BperaResource

	ComPtr<ID3D12Resource> m_depthStencilTexture;//�[�x�X�e���V���o�b�t�@�ƂȂ�e�N�X�`���B
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;		//RTV�p�̃f�B�X�N���v�^�q�[�v�B
	ComPtr<ID3D12DescriptorHeap> m_dsvHeap;		//�[�x�X�e���V���o�b�t�@�r���[�̃f�B�X�N���v�^�q�[�v�B
	UINT m_rtvDescriptorSize = 0;
	UINT m_dsvDescriptorSize = 0;
	int m_width = 0;
	int m_height= 0;
	float m_dsvClearValue = 1.0f;
	
};
