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

//DirextX12の設定を行うクラス。
class DirectXManager
{
public:
	//コンストラクタ
	DirectXManager(HWND _hwnd);
	//デストラクタ
	~DirectXManager();

	/// <summary>
	/// 描画の開始の処理
	/// </summary>
	void BeginDraw();

	/// <summary>
	/// 描画終了の処理
	/// </summary>
	void EndDraw();

	/// <summary>
	/// テクスチャパスから必要なテクスチャバッファを返す。
	/// すでにロード済みのものはそちらのリソースを返す。
	/// </summary>
	/// <param name="_texpath">テクスチャのパス名</param>
	/// <returns>テクスチャのリソース</returns>
	ComPtr<ID3D12Resource> GetTextureByPath(const char* _texpath);

	//  ゲッター
	ComPtr<ID3D12Device> GetDevice()const { return m_dev; }    //  デバイス
	ComPtr<ID3D12GraphicsCommandList> GetCommandList()const { return m_cmdList; }    //  CommandList
	ComPtr<IDXGISwapChain4> GetSwapchain()const { return m_swapchain; }        //  Swapchain
	ID3D12CommandQueue* GetCmdQue()const { return m_cmdQueue.Get(); }          //  CommandQue

	 //  ViewPortを返す
	D3D12_VIEWPORT GetViewPort()const;

	//  SpriteFont用のDescriptorHeapを返す
	ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeapForSpriteFont();

	//  CommandQueueの処理待ち
	void WaitForCommandQueue();

	//  シーン(ビュープロジェクション)をセット
	void SetScene();

	//  カメラの座標を更新
	void UpdateCameraPos(const XMFLOAT3& _eye, const XMFLOAT3& _target, const XMFLOAT3& _up);

	//カメラのFOV変更
	void SetFov(float fov);

	void SetBackGroundColor(const DirectX::XMFLOAT3& _colors);
	//  ゲッター
	XMMATRIX GetViewMatrix()const { return m_mappedSceneData->view; }    //  ビュー行列
	XMMATRIX GetProjMatrix()const { return m_mappedSceneData->proj; }    //  プロジェクション行列



private:
	//windowSize
	SIZE m_winSize;

	template<typename T>
	using ComPtr = ComPtr<T>;

	 //  DirectX12設定の部分
	ComPtr<ID3D12Device> m_dev = nullptr;        //  デバイス
	ComPtr<ID3D12CommandAllocator> m_cmdAllocator = nullptr;    //  コマンドアロケータ
	ComPtr<ID3D12GraphicsCommandList> m_cmdList = nullptr;      //  コマンドリスト
	ComPtr<ID3D12CommandQueue> m_cmdQueue = nullptr;            //  コマンドキュー

	//  DXGIまわり
	ComPtr<IDXGIFactory4> m_dxgiFactory = nullptr;    //  DXGIインターフェイス
	ComPtr<IDXGISwapChain4> m_swapchain = nullptr;    //  スワップチェイン

	//  表示に関わる部分
	ComPtr<ID3D12Resource> m_depthBuffer = nullptr;    //  深度バッファ
	std::vector<ID3D12Resource*> m_backBuffers;    //  バックバッファ
	ComPtr<ID3D12DescriptorHeap> m_rtvHeaps = nullptr;    //  レンダーターゲット用ディスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> m_dsvHeap = nullptr;     //  深度バッファビュー用ディスクリプタヒープ
	std::unique_ptr<D3D12_VIEWPORT> m_viewport;    //  ビューポート
	std::unique_ptr<D3D12_RECT> m_scissorrect;     //  シザー矩形

	//  Fence
	ComPtr<ID3D12Fence> m_fence = nullptr;
	UINT64 m_fenceVal = 0;

	 //  シーンを構成するバッファまわり
	ComPtr<ID3D12Resource> m_sceneConstBuff = nullptr;

	//  シェーダー側に渡すための基本的な行列データ
	struct SceneData
	{
		XMMATRIX view;        //  ビュー行列
		XMMATRIX proj;        //  プロジェクション行列
		XMFLOAT3 eye;         //  視点座標
	};

	//  シェーダに渡す行列データ
	SceneData* m_mappedSceneData;
	ComPtr<ID3D12DescriptorHeap> m_sceneDescHeap = nullptr;        //  ヒープ

	float _fov = DirectX::XM_PI / 6;//デフォルト30°
	
	//カメラ位置
	XMFLOAT3 m_cameraPos = { 0,0,0 };

	//  RenderTargetの生成
	HRESULT CreateRenderTargets();

	//  DepthStencilViewの生成
	HRESULT CreateDepthStencilView();

	//  SwapChainの生成
	HRESULT CreateSwapChain(const HWND& _hwnd);

	//  DXGIまわり初期化
	HRESULT InitializeDXGIDevice();

	//  Commandまわり初期化
	HRESULT InitializeCommand();

	//  ビュープロジェクション用ビューの生成
	HRESULT CreateSceneView();

	//  ロード用テーブル
	using LoadLambda_t = std::function<HRESULT(const std::wstring& _path, TexMetadata*, ScratchImage&)>;
	std::map<std::string, LoadLambda_t> m_loadLambdaTable;
	//  テクスチャテーブル
	std::unordered_map<std::string, ComPtr<ID3D12Resource>> m_textureTable;
	//  TextureLoaderTableの作成
	void CreateTextureLoaderTable();
	//  テクスチャ名からテクスチャバッファ作成、中身をコピー
	ID3D12Resource* CreateTextureFromFile(const char* _texpath);

	XMFLOAT3 m_nowBackGroundColorCode;
	const XMFLOAT3 END_COLOR = { 0.296f,0.028f,0.332f };
	const XMFLOAT3 START_COLOR = { 0.296f,0.028f,0.332f };
	const XMFLOAT3 CODE_COLOR = { 0.0296f,0.0028f,0.0332f };
	
	int m_backGroundCount=0;

};

