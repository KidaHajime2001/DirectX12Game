#include "Fade.h"
#include <d3dx12.h>
#include <d3dcompiler.h>
#include <cassert>
#include <string>
#include <algorithm>
#include"Controller.h"
#include"Singleton.h"
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
Fade::Fade(DirectXManager& _dx12) :m_dx12(_dx12)
, m_nowFadeIn(false)
,m_state(FadeState::neutral)
{

	m_wipeSize = new WipeParam();
	//  ルートシグネチャ生成
	assert(SUCCEEDED(CreateRootSignature()));
	//  グラフィックスパイプライン生成
	assert(SUCCEEDED(CreateGraphicsPipelineForFade()));
	CreateVB();
	CreateIB();
}
void Fade::FadeStart()
{
	if (m_state != FadeState::Fadeing)
	{
		m_nowFadeIn = !m_nowFadeIn;
		m_state = FadeState::Fadeing;
	}

}
void Fade::FadeEnd()
{
	if (m_state == FadeState::Fadeing
		&& !m_once&& m_fadeOut)
	{
		m_nowFadeIn = !m_nowFadeIn;
		m_once = true;
	}
	
}

const Fade::FadeState Fade::GetState()
{
	return m_state;
}

void Fade::Update()
{
	
	
	
	if (m_nowFadeIn)
	{
		m_wipeSize->wipeSize += FADESPEED * WIPECODE_FADEIN;
		if (m_wipeSize->wipeSize < WIPESIZE_MIN)
		{
			m_wipeSize->wipeSize = WIPESIZE_MIN;
			m_fadeOut = true;

			m_isEnd = true;
		}
	}
	else
	{
		m_wipeSize->wipeSize += FADESPEED * WIPECODE_FADEOUT;
		
		if (m_wipeSize->wipeSize > WIPESIZE_MAX)
		{
			m_wipeSize->wipeSize = WIPESIZE_MAX;
			if (m_fadeOut)
			{
				Init();
			}
			
		}
	}




	
}

void Fade::Draw()
{
	
	m_dx12.GetCommandList()->SetGraphicsRootSignature(m_rootSignature.Get());
	m_dx12.GetCommandList()->SetPipelineState(m_pipeline.Get());
	m_dx12.GetCommandList()->IASetVertexBuffers(0,1,&vbView);
	m_dx12.GetCommandList()->IASetIndexBuffer(&ibView);
	m_dx12.GetCommandList()->SetDescriptorHeaps(1, &basicDescHeap);
	m_dx12.GetCommandList()->SetGraphicsRootDescriptorTable(0, basicDescHeap->GetGPUDescriptorHandleForHeapStart());

	m_dx12.GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	
	m_dx12.GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
	
}

void Fade::Load()
{
	
}

HRESULT Fade::CreateGraphicsPipelineForFade()
{
	

	
	//  シェーダーの設定
	 //　バイナリデータ構造体
	ComPtr<ID3DBlob> vsBlob = nullptr;
	ComPtr<ID3DBlob> psBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;

	//  シェーダーをコンパイル
	//　BasicShader.hlslが頂点シェーダー
	auto result = D3DCompileFromFile(L"FadeVertexShader.hlsl",
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"BasicVS", "vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0, &vsBlob, &errorBlob);
	if (!CheckShaderCompileResult(result, errorBlob.Get())) {
		assert(0);
		return result;
	}

	//  シェーダーをコンパイル
   //　BasicShader.hlslがピクセルシェーダー
	result = D3DCompileFromFile(L"FadePixelShader.hlsl",
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
	//  グラフィックスパイプラインステートの設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline = {};
	gpipeline.pRootSignature = m_rootSignature.Get();
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;    //  中身は0xffffffff

	gpipeline.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);

	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;    //  カリングしない
	gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;

	gpipeline.DepthStencilState.DepthEnable = true;    //  深度バッファを使う
	gpipeline.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;    //  全て書き込み
	gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;        //  小さい方を採用
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	gpipeline.DepthStencilState.StencilEnable = false;

	gpipeline.InputLayout.pInputElementDescs = inputLayout;       //  レイアウト先頭アドレス
	gpipeline.InputLayout.NumElements = _countof(inputLayout);    //  レイアウト配列数

	gpipeline.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;     //  ストリップ時のカットなし
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;    //  三角形で構成

	gpipeline.NumRenderTargets = 1;    //  今は１つのみ
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;    //  0～1に正規化されたRGBA

	gpipeline.SampleDesc.Count = 1;        //  サンプリングは1ピクセルにつき１
	gpipeline.SampleDesc.Quality = 0;      //  クオリティは最低

	//  グラフィックスパイプラインステートの生成
	result = m_dx12.GetDevice()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(m_pipeline.ReleaseAndGetAddressOf()));
	if (FAILED(result)) {
		assert(SUCCEEDED(result));
	}
	return result;
}

HRESULT Fade::CreateRootSignature()
{
	//  レンジ
	CD3DX12_DESCRIPTOR_RANGE  descTblRanges[4] = {};    //  テクスチャと定数の２つ
	descTblRanges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);    //  定数[b0](ビュープロジェクション用)
	descTblRanges[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);    //  定数[b1](ワールド、ボーン用)


	D3D12_ROOT_PARAMETER rootparam = {};
	rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootparam.DescriptorTable.pDescriptorRanges = &descTblRanges[0];//デスクリプタレンジのアドレス
	rootparam.DescriptorTable.NumDescriptorRanges = 2;//デスクリプタレンジ数
	rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//全てのシェーダから見える

	D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//横繰り返し
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//縦繰り返し
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//奥行繰り返し
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;//ボーダーの時は黒
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;//補間しない(ニアレストネイバー)
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;//ミップマップ最大値
	samplerDesc.MinLOD = 0.0f;//ミップマップ最小値
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;//オーバーサンプリングの際リサンプリングしない？
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;//ピクセルシェーダからのみ可視amplerDescs[1].Init(1, D3D12_FILTER_ANISOTROPIC, D3D12_TEXTURE_ADDRESS_MODE_CLAMP, D3D12_TEXTURE_ADDRESS_MODE_CLAMP);

	//  ルートシグネチャの設定
	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	rootSignatureDesc.Init(1, &rootparam, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	//  ルートシグネチャの生成
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

void Fade::CreateVB()
{
	struct Vertex {
		XMFLOAT3 pos;//XYZ座標
		XMFLOAT2 uv;//UV座標
	};

	Vertex vertices[] = {
		{{-1.f,-1.f,0.0f},{0.0f,1.0f} },//左下
		{{-1.f,1.f,0.0f} ,{0.0f,0.0f}},//左上
		{{1.f,-1.f,0.0f} ,{1.0f,1.0f}},//右下
		{{1.f,1.f,0.0f} ,{1.0f,0.0f}},//右上
	};
	//UPLOAD(確保は可能)
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto resDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices));
	auto result = m_dx12.GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));

	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);

	std::copy(std::begin(vertices), std::end(vertices), vertMap);

	vertBuff->Unmap(0, nullptr);

	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();//バッファの仮想アドレス
	vbView.SizeInBytes = sizeof(vertices);//全バイト数
	vbView.StrideInBytes = sizeof(vertices[0]);//1頂点あたりのバイト数

	//WICテクスチャのロード
	TexMetadata metadata = {};
	ScratchImage scratchImg = {};
	 result = LoadFromWICFile(L"Data/Img/GameScene/BackBlack.png", WIC_FLAGS_NONE, &metadata, scratchImg);
	auto img = scratchImg.GetImage(0, 0, 0);//生データ抽出

	//WriteToSubresourceで転送する用のヒープ設定
	D3D12_HEAP_PROPERTIES texHeapProp = {};
	texHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;//特殊な設定なのでdefaultでもuploadでもなく
	texHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;//ライトバックで
	texHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;//転送がL0つまりCPU側から直で
	texHeapProp.CreationNodeMask = 0;//単一アダプタのため0
	texHeapProp.VisibleNodeMask = 0;//単一アダプタのため0

	resDesc = {};
	resDesc.Format = metadata.format;//DXGI_FORMAT_R8G8B8A8_UNORM;//RGBAフォーマット
	resDesc.Width = static_cast<UINT>(metadata.width);//幅
	resDesc.Height = static_cast<UINT>(metadata.height);//高さ
	resDesc.DepthOrArraySize = static_cast<UINT16>(metadata.arraySize);//2Dで配列でもないので１
	resDesc.SampleDesc.Count = 1;//通常テクスチャなのでアンチェリしない
	resDesc.SampleDesc.Quality = 0;//
	resDesc.MipLevels = static_cast<UINT16>(metadata.mipLevels);//ミップマップしないのでミップ数は１つ
	resDesc.Dimension = static_cast<D3D12_RESOURCE_DIMENSION>(metadata.dimension);//2Dテクスチャ用
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;//レイアウトについては決定しない
	resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;//とくにフラグなし

	ID3D12Resource* texbuff = nullptr;
	result = m_dx12.GetDevice()->CreateCommittedResource(
		&texHeapProp,
		D3D12_HEAP_FLAG_NONE,//特に指定なし
		&resDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,//テクスチャ用(ピクセルシェーダから見る用)
		nullptr,
		IID_PPV_ARGS(&texbuff)
	);
	result = texbuff->WriteToSubresource(0,
		nullptr,//全領域へコピー
		img->pixels,//元データアドレス
		static_cast<UINT>(img->rowPitch),//1ラインサイズ
		static_cast<UINT>(img->slicePitch)//全サイズ
	);

	ID3D12Resource* constBuff = nullptr;
	heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	resDesc = CD3DX12_RESOURCE_DESC::Buffer((sizeof(XMFLOAT2) + 0xff) & ~0xff);
	result =m_dx12.GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff)
	);


	/*ID3D12DescriptorHeap* basicDescHeap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};*/
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	descHeapDesc.NodeMask = 0;//マスクは0
	descHeapDesc.NumDescriptors = 2;//SRV1つとCBV1つ
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//デスクリプタヒープ種別
	result =m_dx12.GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&basicDescHeap));//生成

	//通常テクスチャビュー作成
	/*D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};*/
	srvDesc.Format = metadata.format;//DXGI_FORMAT_R8G8B8A8_UNORM;//RGBA(0.0f～1.0fに正規化)
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;//後述
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;//ミップマップは使用しないので1

	//デスクリプタの先頭ハンドルを取得しておく
	auto basicHeapHandle = basicDescHeap->GetCPUDescriptorHandleForHeapStart();
	//シェーダリソースビューの作成
	m_dx12.GetDevice()->CreateShaderResourceView(texbuff, //ビューと関連付けるバッファ
		&srvDesc, //先ほど設定したテクスチャ設定情報
		basicHeapHandle
	);
	basicHeapHandle.ptr +=
		m_dx12.GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	
	
	result = constBuff->Map(0, nullptr, (void**)&m_wipeSize);//マップ
	m_wipeSize->wipeDir = WIPEDIR_FADE_OUT;
	m_wipeSize->wipeSize = 3500.0f;
	m_wipeSize->rectSize.y = WINDOW_WIDTH / 2;
	m_wipeSize->rectSize.x = WINDOW_HEIGHT / 2;
	/*D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};*/
	cbvDesc.BufferLocation = constBuff->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = static_cast<UINT>(constBuff->GetDesc().Width);
	//定数バッファビューの作成
	m_dx12.GetDevice()->CreateConstantBufferView(&cbvDesc, basicHeapHandle);


}

void Fade::CreateIB()
{
	unsigned short indices[] = { 0,1,2, 2,1,3 };

	//設定は、バッファのサイズ以外頂点バッファの設定を使いまわして
	//OKだと思います。
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto resDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(indices));
	auto result = m_dx12.GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&idxBuff));

	//作ったバッファにインデックスデータをコピー
	unsigned short* mappedIdx = nullptr;
	idxBuff->Map(0, nullptr, (void**)&mappedIdx);
	std::copy(std::begin(indices), std::end(indices), mappedIdx);
	idxBuff->Unmap(0, nullptr);

	//インデックスバッファビューを作成
	ibView.BufferLocation = idxBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeof(indices);

}

bool Fade::CheckShaderCompileResult(HRESULT _result, ID3DBlob* _error)
{
	if (FAILED(_result)) {
		if (_result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) {
			::OutputDebugStringA("ファイルが見当たりません");
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

void Fade::Init()
{
	m_nowFadeIn=false;
	m_isEnd = false;
	m_once = false;
	m_fadeOut = false;
	m_state = FadeState::neutral;
}
