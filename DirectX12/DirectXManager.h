#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <map>
#include <unordered_map>
#include<SpriteBatch.h>
#include <wrl.h>
#include <functional>
#include <iostream>
#include <DirectXTex.h>

#pragma comment(lib,"DirectXTK12.lib")

using namespace Microsoft::WRL;
using namespace DirectX;

//DirextX12�̐ݒ���s���N���X�B
class DirectXManager
{
public:
	//�R���X�g���N�^
	DirectXManager(HWND _hwnd);
	//�f�X�g���N�^
	~DirectXManager();

	/// <summary>
	/// �`��̊J�n�̏���
	/// </summary>
	void BeginDraw();

	/// <summary>
	/// �`��I���̏���
	/// </summary>
	void EndDraw();

	/// <summary>
	/// �e�N�X�`���p�X����K�v�ȃe�N�X�`���o�b�t�@��Ԃ��B
	/// ���łɃ��[�h�ς݂̂��̂͂�����̃��\�[�X��Ԃ��B
	/// </summary>
	/// <param name="_texpath">�e�N�X�`���̃p�X��</param>
	/// <returns>�e�N�X�`���̃��\�[�X</returns>
	ComPtr<ID3D12Resource> GetTextureByPath(const char* _texpath);

	//  �Q�b�^�[
	ComPtr<ID3D12Device> GetDevice()const { return m_dev; }    //  �f�o�C�X
	ComPtr<ID3D12GraphicsCommandList> GetCommandList()const { return m_cmdList; }    //  CommandList
	ComPtr<IDXGISwapChain4> GetSwapchain()const { return m_swapchain; }        //  Swapchain
	ID3D12CommandQueue* GetCmdQue()const { return m_cmdQueue.Get(); }          //  CommandQue

	 //  ViewPort��Ԃ�
	D3D12_VIEWPORT GetViewPort()const;

	//  SpriteFont�p��DescriptorHeap��Ԃ�
	ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeapForSpriteFont();

	//  CommandQueue�̏����҂�
	void WaitForCommandQueue();

	//  �V�[��(�r���[�v���W�F�N�V����)���Z�b�g
	void SetScene();

	//  �J�����̍��W���X�V
	void UpdateCameraPos(const XMFLOAT3& _eye, const XMFLOAT3& _target, const XMFLOAT3& _up);

	//�J������FOV�ύX
	void SetFov(float fov);

	void SetBackGroundColor(const DirectX::XMFLOAT3& _colors);
	//  �Q�b�^�[
	XMMATRIX GetViewMatrix()const { return m_mappedSceneData->view; }    //  �r���[�s��
	XMMATRIX GetProjMatrix()const { return m_mappedSceneData->proj; }    //  �v���W�F�N�V�����s��



private:
	//windowSize
	SIZE m_winSize;

	template<typename T>
	using ComPtr = ComPtr<T>;

	 //  DirectX12�ݒ�̕���
	ComPtr<ID3D12Device> m_dev = nullptr;        //  �f�o�C�X
	ComPtr<ID3D12CommandAllocator> m_cmdAllocator = nullptr;    //  �R�}���h�A���P�[�^
	ComPtr<ID3D12GraphicsCommandList> m_cmdList = nullptr;      //  �R�}���h���X�g
	ComPtr<ID3D12CommandQueue> m_cmdQueue = nullptr;            //  �R�}���h�L���[

	//  DXGI�܂��
	ComPtr<IDXGIFactory4> m_dxgiFactory = nullptr;    //  DXGI�C���^�[�t�F�C�X
	ComPtr<IDXGISwapChain4> m_swapchain = nullptr;    //  �X���b�v�`�F�C��

	//  �\���Ɋւ�镔��
	ComPtr<ID3D12Resource> m_depthBuffer = nullptr;    //  �[�x�o�b�t�@
	std::vector<ID3D12Resource*> m_backBuffers;    //  �o�b�N�o�b�t�@
	ComPtr<ID3D12DescriptorHeap> m_rtvHeaps = nullptr;    //  �����_�[�^�[�Q�b�g�p�f�B�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> m_dsvHeap = nullptr;     //  �[�x�o�b�t�@�r���[�p�f�B�X�N���v�^�q�[�v
	std::unique_ptr<D3D12_VIEWPORT> m_viewport;    //  �r���[�|�[�g
	std::unique_ptr<D3D12_RECT> m_scissorrect;     //  �V�U�[��`

	//  Fence
	ComPtr<ID3D12Fence> m_fence = nullptr;
	UINT64 m_fenceVal = 0;

	 //  �V�[�����\������o�b�t�@�܂��
	ComPtr<ID3D12Resource> m_sceneConstBuff = nullptr;

	//  �V�F�[�_�[���ɓn�����߂̊�{�I�ȍs��f�[�^
	struct SceneData
	{
		XMMATRIX view;        //  �r���[�s��
		XMMATRIX proj;        //  �v���W�F�N�V�����s��
		XMFLOAT3 eye;         //  ���_���W
	};

	//  �V�F�[�_�ɓn���s��f�[�^
	SceneData* m_mappedSceneData;
	ComPtr<ID3D12DescriptorHeap> m_sceneDescHeap = nullptr;        //  �q�[�v

	float _fov = DirectX::XM_PI / 6;//�f�t�H���g30��
	
	//�J�����ʒu
	XMFLOAT3 m_cameraPos = { 0,0,0 };

	//  RenderTarget�̐���
	HRESULT CreateRenderTargets();

	//  DepthStencilView�̐���
	HRESULT CreateDepthStencilView();

	//  SwapChain�̐���
	HRESULT CreateSwapChain(const HWND& _hwnd);

	//  DXGI�܂�菉����
	HRESULT InitializeDXGIDevice();

	//  Command�܂�菉����
	HRESULT InitializeCommand();

	//  �r���[�v���W�F�N�V�����p�r���[�̐���
	HRESULT CreateSceneView();

	//  ���[�h�p�e�[�u��
	using LoadLambda_t = std::function<HRESULT(const std::wstring& _path, TexMetadata*, ScratchImage&)>;
	std::map<std::string, LoadLambda_t> m_loadLambdaTable;
	//  �e�N�X�`���e�[�u��
	std::unordered_map<std::string, ComPtr<ID3D12Resource>> m_textureTable;
	//  TextureLoaderTable�̍쐬
	void CreateTextureLoaderTable();
	//  �e�N�X�`��������e�N�X�`���o�b�t�@�쐬�A���g���R�s�[
	ID3D12Resource* CreateTextureFromFile(const char* _texpath);

	XMFLOAT3 m_nowBackGroundColorCode;
	const XMFLOAT3 END_COLOR = { 0.296f,0.028f,0.332f };
	const XMFLOAT3 START_COLOR = { 0.296f,0.028f,0.332f };
	const XMFLOAT3 CODE_COLOR = { 0.0296f,0.0028f,0.0332f };
	
	int m_backGroundCount=0;

};

