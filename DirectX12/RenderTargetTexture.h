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
	/// 描画前準備
	/// </summary>
	void BeginDraw();
	void AfterDraw();
	/// <summary>
	/// レンダリングターゲットの作成。
	/// </summary>
	/// <param name="w">レンダリングターゲットの幅</param>
	/// <param name="h">レンダリングターゲットの高さ</param>
	/// <param name="mipLevel">ミップマップレベル。0を指定した場合はミップマップがサポートされているGPUでは1*1ピクセルまでのミップマップが作成される。</param>
	/// <param name="arraySize">テクスチャ配列のサイズ</param>
	/// <param name="colorFormat">カラーバッファのフォーマット。</param>
	/// <param name="depthStencilFormat">深度ステンシルバッファのフォーマット。</param>
	/// <returns>trueが返ってきたら作成成功</returns>
	bool Create(
		int w,
		int h,
		int mipLevel,
		int arraySize,
		DXGI_FORMAT colorFormat,
		DXGI_FORMAT depthStencilFormat
	);
	/// <summary>
	/// レンダリングターゲットとなるテクスチャを作成。
	/// </summary>
	/// <param name="ge">グラフィックエンジン</param>
	/// <param name="d3dDevice">D3Dデバイス</param>
	/// <param name="w">テクスチャの幅</param>
	/// <param name="h">テクスチャの高さ</param>
	/// <param name="mipLevel">ミップマップレベル</param>
	/// <param name="arraySize">テクスチャ配列のサイズ</param>
	/// <param name="format">テクスチャのフォーマット</param>
	/// <returns>trueが返ってきたら成功。</returns>
	bool CreateRenderTargetTexture(
		ComPtr<ID3D12Device> d3dDevice,
		int w,
		int h,
		int mipLevel,
		int arraySize,
		DXGI_FORMAT format
	);
	/// <summary>
	/// 深度ステンシルバッファとなるテクスチャを作成。
	/// </summary>
	/// <param name="ge">グラフィックエンジン</param>
	/// <param name="d3dDevice">D3Dデバイス</param>
	/// <param name="w">テクスチャの幅</param>
	/// <param name="h">テクスチャの高さ</param>
	/// <param name="format">テクスチャのフォーマット</param>
	/// <returns>trueが返ってきたら成功</returns>
	bool CreateDepthStencilTexture(
		ComPtr<ID3D12Device> d3dDevice,
		int w,
		int h,
		DXGI_FORMAT format);
	/// <summary>
	/// ディスクリプタの作成。
	/// </summary>
	/// <param name="d3dDevice">D3Dデバイス</param>
	/// <returns>trueが返ってｋチアら成功。</returns>
	void CreateDescriptor(ComPtr<ID3D12Device> d3dDevice);

	/// <summary>
	/// ディスクリプタヒープを作成。
	/// </summary>
	/// <param name="ge">グラフィックエンジン</param>
	/// <param name="d3dDevice">D3Dデバイス</param>
	/// <returns></returns>
	bool CreateDescriptorHeap(ComPtr<ID3D12Device> d3dDevice);

	bool CreateSRV(ComPtr<ID3D12Device> d3dDevice);

	ComPtr<ID3D12DescriptorHeap> GetSRV() { return m_srvHeap; };


private:
	template<typename T>
	using ComPtr = ComPtr<T>;

	DirectXManager& m_dx12;
	ComPtr<ID3D12DescriptorHeap> m_srvHeap;


	ComPtr<ID3D12Resource> m_renderTargetTexture;//レンダリングターゲットとなるテクスチャ。peraResource

	ComPtr<ID3D12Resource> m_depthStencilTexture;//深度ステンシルバッファとなるテクスチャ。
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;		//RTV用のディスクリプタヒープ。
	ComPtr<ID3D12DescriptorHeap> m_dsvHeap;		//深度ステンシルバッファビューのディスクリプタヒープ。
	UINT m_rtvDescriptorSize = 0;
	UINT m_dsvDescriptorSize = 0;
	int m_width = 0;
	int m_height= 0;
	float m_dsvClearValue = 1.0f;
	
};
