#include "DirectXManager.h"

#include <cassert>
#include <d3dx12.h>

#include "Singleton.h"
#include "D12Device.h"

#pragma comment(lib,"DirectXTex.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
namespace {
    //  ���f���̃p�X�ƃe�N�X�`���̃p�X���獇���p�X�𓾂�
    //  @param modelPath �A�v���P�[�V�������猩��pmd���f���̃p�X
    //  @param texPath PMD ���f�����猩���e�N�X�`���̃p�X
    //  @return �A�v���P�[�V�������猩���e�N�X�`���̃p�X
    std::string GetTexturePathFromModelAndTexPath(
        const std::string& _modelPath,
        const char* _texPath)
    {
        //  �t�@�C���̃t�H���_�[��؂��\��/��2��ނ��g�p�����\��������
        //  �Ƃ�����������\��/�𓾂���΂����̂ŁA�o����rfind������r����
        //  �iint�^�ɑ�����Ă���̂́A������Ȃ������ꍇ��rfind��epos(-1 �� 0xffffffff)��Ԃ�����
        int pathIndex1 = _modelPath.rfind('/');
        int pathIndex2 = _modelPath.rfind('\\');

        auto pathIndex = max(pathIndex1, pathIndex2);
        auto folderPath = _modelPath.substr(0, pathIndex + 1);

        return folderPath + _texPath;
    }

    //  �t�@�C��������g���q���擾����
    //  @param path �Ώۂ̃p�X������
    //  @return �g���q
    std::string GetExtension(const std::string& _path)
    {
        int idx = _path.rfind('.');
        return _path.substr(idx + 1, _path.length() - idx - 1);
    }

    ///  <summary>
    ///  �e�N�X�`���̃p�X���Z�p���[�^�����ŕ�������
    ///  </summary>
    ///  @param path ��܂̃p�X������
    ///  @param splitter ��؂蕶��
    ///  @return �����O��̕�����y�A
    std::wstring GetExtension(const std::wstring& _path)
    {
        int idx = _path.rfind(L'.');
        return _path.substr(idx + 1, _path.length() - idx - 1);
    }

    //  �e�N�X�`���̃p�X���Z�p���[�^�[�����ŕ�������
    //  @param path �Ώۂ̃p�X������
    //  @param splitter ��؂蕶��
    //  @return �����O��̕�����y�A
    std::pair<std::string, std::string> SplitFileName(const std::string& _path, const char _splitter = '*')
    {
        int idx = _path.find(_splitter);
        std::pair<std::string, std::string> ret;
        ret.first = _path.substr(0, idx);
        ret.second = _path.substr(idx + 1, _path.length() - idx - 1);
        return ret;
    }

    //  std::string�i�}���`�o�C�g������j����std::wstring�i���C�h������j�𓾂�
    //  @param str �}���`�o�C�g������
    //  @return �ϊ����ꂽ���C�h������
    std::wstring GetWideStringFromString(const std::string& _str)
    {
        //  �Ăяo��1��ځi�����񐔂𓾂�j
        auto num1 = MultiByteToWideChar(
            CP_ACP,
            MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
            _str.c_str(),
            -1,
            nullptr,
            0);

        std::wstring wstr;         //  string��wchar_t��
        wstr.resize(num1);    //  ����ꂽ�����񐔂Ń��T�C�Y

        //  �Ăяo��2��ځi�m�ۍς݂�wstr�ɕϊ���������R�s�[�j
        auto num2 = MultiByteToWideChar(
            CP_ACP,
            MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
            _str.c_str(),
            -1,
            &wstr[0],
            num1);

        assert(num1 == num2);    //  �ꉞ�`�F�b�N
        return wstr;
    }

    //  �f�o�b�O���C���[��L���ɂ���
    void EnableDebugLayer()
    {
        ComPtr<ID3D12Debug> debugLayer = nullptr;
        auto result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));

        debugLayer->EnableDebugLayer();
    }
}
DirectXManager::DirectXManager(HWND _hwnd)
    :m_nowBackGroundColorCode(XMFLOAT3(0,0,0))
{
#ifdef _DEBUG
    //  �f�o�b�O���C���[���I����
    EnableDebugLayer();
#endif
    D12Device& device = Singleton<D12Device>::GetInstance();
    m_winSize = device.GetWindowSize();

    //  DirectX12�֘A������
    if (FAILED(InitializeDXGIDevice())) {
        assert(0);
        return;
    }
    if (FAILED(InitializeCommand())) {
        assert(0);
        return;
    }
    if (FAILED(CreateSwapChain(_hwnd))) {
        assert(0);
        return;
    }
    if (FAILED(CreateRenderTargets())) {
        assert(0);
        return;
    }

    if (FAILED(CreateSceneView())) {
        assert(0);
        return;
    }

    //  TextureLoader�֘A������
    CreateTextureLoaderTable();

    //  DepthStencilView�쐬
    if (FAILED(CreateDepthStencilView()))
    {
        assert(0);
        return;
    }
    //  Fence�̍쐬
    if (FAILED(m_dev->CreateFence(m_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_fence.ReleaseAndGetAddressOf())))) {
        assert(0);
        return;
    }

}


DirectXManager::~DirectXManager()
{
}


HRESULT DirectXManager::InitializeDXGIDevice()
{
    //�f�o�b�O�L
    UINT flagsDXGI = 0;
    flagsDXGI |= DXGI_CREATE_FACTORY_DEBUG;

    //Dx12�f�o�C�X�ƃX���b�v�`�F�[�����̂ɕK�v
    auto result = CreateDXGIFactory2(flagsDXGI, IID_PPV_ARGS(m_dxgiFactory.ReleaseAndGetAddressOf()));

    //  DirectX12�܂�菉����
    //  FeatureLevel�񋓁iver�݂����Ȃ���
    D3D_FEATURE_LEVEL levels[] = {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };
    if (FAILED(result)) {
        return result;
    }

    //���p�\�ȃA�_�v�^�[�̗�
    std::vector <IDXGIAdapter*> adapters;
    IDXGIAdapter* tmpAdapter = nullptr;
    for (int i = 0; m_dxgiFactory->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
        adapters.push_back(tmpAdapter);
    }
    for (auto adpt : adapters) {
        DXGI_ADAPTER_DESC adesc = {};
        adpt->GetDesc(&adesc);
        std::wstring strDesc = adesc.Description;
        //NVIDIA�Ɩ��̕t�����̂�T��
        if (strDesc.find(L"NVIDIA") != std::string::npos) {
            tmpAdapter = adpt;
            break;
        }
    }
    result = S_FALSE;
    //  Direct3D�f�o�C�X�̏�����
    D3D_FEATURE_LEVEL featureLevel;

    //�쐬�\�ȃ��x���ō��
    for (auto l : levels) {
        if (SUCCEEDED(D3D12CreateDevice(tmpAdapter, l, IID_PPV_ARGS(m_dev.ReleaseAndGetAddressOf())))) {
            featureLevel = l;
            result = S_OK;
            break;
        }
    }
    return result;
}


HRESULT DirectXManager::InitializeCommand()
{
    //�R�}���h�A���P�[�^�[���
    auto result = m_dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_cmdAllocator.ReleaseAndGetAddressOf()));
    if (FAILED(result)) {
        assert(0);
        return result;
    }
    //�R�}���h���X�g���
    result = m_dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_cmdAllocator.Get(), nullptr, IID_PPV_ARGS(m_cmdList.ReleaseAndGetAddressOf()));
    if (FAILED(result)) {
        assert(0);
        return result;
    }

    //�R�}���h�L���[���
    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
    cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE; //  �^�C���A�E�g�Ȃ�
    cmdQueueDesc.NodeMask = 0;
    cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;    //  Priority���Ɏw��Ȃ�
    cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT; //  ������CommandList�ƍ��킹�Ă�������
    result = m_dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(m_cmdQueue.ReleaseAndGetAddressOf()));   //  CommandQueue����
    assert(SUCCEEDED(result));
    return result;
}

ComPtr<ID3D12Resource> DirectXManager::GetTextureByPath(const char* _texpath)
{
    auto it = m_textureTable.find(_texpath);
    if (it != m_textureTable.end()) {
        //  �e�[�u���ɓ��ɂ������烍�[�h����̂ł͂Ȃ��}�b�v����
        //  ���\�[�X��Ԃ�
        return m_textureTable[_texpath];
    }
    else {
        return ComPtr<ID3D12Resource>(CreateTextureFromFile(_texpath));
    }
}

D3D12_VIEWPORT DirectXManager::GetViewPort() const
{
    D12Device& device = Singleton<D12Device>::GetInstance();
    auto wsize = device.GetWindowSize();
    D3D12_VIEWPORT vp;
    vp.TopLeftX = vp.TopLeftY = 0;
    vp.Width = wsize.cx;
    vp.Height = wsize.cy;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    return vp;
}

ComPtr<ID3D12DescriptorHeap> DirectXManager::CreateDescriptorHeapForSpriteFont()
{
    ComPtr<ID3D12DescriptorHeap> ret;
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    desc.NodeMask = 0;
    desc.NumDescriptors = 1;
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    m_dev->CreateDescriptorHeap(&desc, IID_PPV_ARGS(ret.ReleaseAndGetAddressOf()));
    return ret;
}

void DirectXManager::WaitForCommandQueue()
{
    //���ɏ���Ƃ���_fenceValue��0�������Ƃ��܂�
    m_cmdQueue->Signal(m_fence.Get(), ++m_fenceVal);
    //���̖��ߒ���ł�_fenceValue��1�ŁA
    //GetCompletedValue�͂܂�0�ł��B
    if (m_fence->GetCompletedValue() < m_fenceVal) {
        //�����܂��I����ĂȂ��Ȃ�A�C�x���g�҂����s��
        //�����̂��߂̃C�x���g�H���Ƃ��̂��߂�_fenceValue
        auto event = CreateEvent(nullptr, false, false, nullptr);
        //�t�F���X�ɑ΂��āACompletedValue��_fenceValue��
        //�Ȃ�����w��̃C�x���g�𔭐�������Ƃ������߁�
        m_fence->SetEventOnCompletion(m_fenceVal, event);
        //���܂��C�x���g�������Ȃ�
        //���C�x���g����������܂ő҂�
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }
}

void DirectXManager::SetScene()
{
    //  ���݂̃V�[��(�r���[�v���W�F�N�V����)���Z�b�g
    ID3D12DescriptorHeap* sceneheaps[] = { m_sceneDescHeap.Get() };
    m_cmdList->SetDescriptorHeaps(1, sceneheaps);
    m_cmdList->SetGraphicsRootDescriptorTable(0, m_sceneDescHeap->GetGPUDescriptorHandleForHeapStart());
}

void DirectXManager::UpdateCameraPos(const XMFLOAT3& _eye, const XMFLOAT3& _target, const XMFLOAT3& _up)
{
    //  �w��ʒu�ɃJ�������ړ�
    m_mappedSceneData->view = XMMatrixLookAtLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_target), XMLoadFloat3(&_up));
}
void DirectXManager::SetFov(float fov)
{
    //  SwapChain�̐ݒ�
    DXGI_SWAP_CHAIN_DESC1 desc = {};
    auto result = m_swapchain->GetDesc1(&desc);
    float TrueFOV = fov*(DirectX::XM_PI/180);
    m_mappedSceneData->proj = XMMatrixPerspectiveFovLH(_fov,    //  ��p��45��
        static_cast<float>(desc.Width) / static_cast<float>(desc.Height),    //  �A�X��
        0.1f,    //  �߂���
        1000.0f    //  ������
    );
}
void DirectXManager::SetBackGroundColor(const DirectX::XMFLOAT3& _colors)
{
    m_nowBackGroundColorCode = _colors;
}
HRESULT DirectXManager::CreateRenderTargets()
{
    DXGI_SWAP_CHAIN_DESC1 desc = {};
    auto result = m_swapchain->GetDesc1(&desc);

    //  RenderTarget�p��DescriptorHeap�̍쐬
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;    //  RenderTargetView�Ȃ̂œ��RRTV
    heapDesc.NodeMask = 0;
    heapDesc.NumDescriptors = 2;    //  �\���̂Q��
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;    //  ���Ɏw��Ȃ�
    result = m_dev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(m_rtvHeaps.ReleaseAndGetAddressOf()));
    if (FAILED(result)) {
        SUCCEEDED(result);
        return result;
    }
    //  SwapChain�̐ݒ�
    DXGI_SWAP_CHAIN_DESC swcDesc = {};
    result = m_swapchain->GetDesc(&swcDesc);

    m_backBuffers.resize(swcDesc.BufferCount);

    //  DescriptorHeap�̃n���h��
    D3D12_CPU_DESCRIPTOR_HANDLE handle = m_rtvHeaps->GetCPUDescriptorHandleForHeapStart();

    //  SRGBRenderTargetView�ݒ�
    D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
    rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

    //  RenderTargetView�̐���
    //�X���b�v�`�F�C������A�t���b�v�Ώۂ̃��\�[�X���擾
    for (int i = 0; i < swcDesc.BufferCount; i++) {
        //GetBuffer�̓X���b�v�`�F�C���������Ă�i�Ԗڂ�
        //���\�[�X��������ɓ���Ă����
        result = m_swapchain->GetBuffer(i, IID_PPV_ARGS(&m_backBuffers[i]));
        assert(SUCCEEDED(result));

        rtvDesc.Format = m_backBuffers[i]->GetDesc().Format;
        //Format���킹��RTV�쐬
        m_dev->CreateRenderTargetView(m_backBuffers[i], &rtvDesc, handle);

        //�X���b�v�`�F�[���̖����A�擪�n���h������RTV���ړ�
        handle.ptr += m_dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }
    m_viewport.reset(new CD3DX12_VIEWPORT(m_backBuffers[0]));
    m_scissorrect.reset(new CD3DX12_RECT(0, 0, desc.Width, desc.Height));
    return result;
}

HRESULT DirectXManager::CreateDepthStencilView()
{
    DXGI_SWAP_CHAIN_DESC1 desc = {};
    auto result = m_swapchain->GetDesc1(&desc);

    //  �[�x�o�b�t�@�̐ݒ�
    D3D12_RESOURCE_DESC resdesc = {};
    resdesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    resdesc.DepthOrArraySize = 1;
    resdesc.Width = desc.Width;
    resdesc.Height = desc.Height;
    resdesc.Format = DXGI_FORMAT_D32_FLOAT;
    resdesc.SampleDesc.Count = 1;
    resdesc.SampleDesc.Quality = 0;
    resdesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
    resdesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    resdesc.MipLevels = 1;
    resdesc.Alignment = 0;

    //  �[�x�pHeapProperty
    auto depthHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

    //  �[�x�o�b�t�@�̍쐬
    CD3DX12_CLEAR_VALUE depthClearValue(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);
    result = m_dev->CreateCommittedResource(
        &depthHeapProp,
        D3D12_HEAP_FLAG_NONE,
        &resdesc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE,    //  �[�x�������݂Ɏg�p
        &depthClearValue,
        IID_PPV_ARGS(m_depthBuffer.ReleaseAndGetAddressOf()));
    if (FAILED(result)) {
        //  �G���[����
        return result;
    }

    //  �[�x�̂��߂�DescriptorHeap�쐬
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
    dsvHeapDesc.NumDescriptors = 1;    //  DepthStencilView1�̂�
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;    //  DepthStencilView�Ƃ��Ďg��
    dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;


    result = m_dev->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(m_dsvHeap.ReleaseAndGetAddressOf()));

    //  DepthStencilView�쐬
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;    //  �[�x�l��32bit�g�p
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;    //  2D�e�N�X�`��
    dsvDesc.Flags = D3D12_DSV_FLAG_NONE;    //  �t���O�͓��ɂȂ�
    m_dev->CreateDepthStencilView(m_depthBuffer.Get(), &dsvDesc, m_dsvHeap->GetCPUDescriptorHandleForHeapStart());
}

HRESULT DirectXManager::CreateSwapChain(const HWND& _hwnd)
{
    //��ʋ�`���
    RECT rc = {};
    ::GetWindowRect(_hwnd, &rc);

    //  SwapChain�̐ݒ�
    DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
    swapchainDesc.Width = m_winSize.cx;
    swapchainDesc.Height = m_winSize.cy;
    swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapchainDesc.Stereo = false;
    swapchainDesc.SampleDesc.Count = 1;
    swapchainDesc.SampleDesc.Quality = 0;
    swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapchainDesc.BufferCount = 2;
    swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
    swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    //  SwapChain�̍쐬
    auto result = m_dxgiFactory->CreateSwapChainForHwnd(m_cmdQueue.Get(),
        _hwnd,
        &swapchainDesc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)m_swapchain.ReleaseAndGetAddressOf());
    assert(SUCCEEDED(result));
    return result;
}



HRESULT DirectXManager::CreateSceneView()
{
    //  SwapChain�̐ݒ�
    DXGI_SWAP_CHAIN_DESC1 desc = {};
    auto result = m_swapchain->GetDesc1(&desc);

    //  �萔�o�b�t�@�쐬
    auto temp1 = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    auto temp2 = CD3DX12_RESOURCE_DESC::Buffer((sizeof(SceneData) + 0xff) & ~0xff);
    result = m_dev->CreateCommittedResource(
        &temp1,
        D3D12_HEAP_FLAG_NONE,
        &temp2,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(m_sceneConstBuff.ReleaseAndGetAddressOf()));

    if (FAILED(result))
    {
        assert(SUCCEEDED(result));
        return result;
    }

    //  �}�b�v��������|�C���^
    m_mappedSceneData = nullptr;
    //  �}�b�v
    result = m_sceneConstBuff->Map(0, nullptr, (void**)&m_mappedSceneData);

    //  �J�����̐ݒ�
    XMFLOAT3 eye(0, 10, -100);
    XMFLOAT3 target(0, 0, 0);
    XMFLOAT3 up(0, 1, 0);
    m_mappedSceneData->view = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
    m_mappedSceneData->proj = XMMatrixPerspectiveFovLH(XM_PIDIV4,    //  ��p��45��
        static_cast<float>(desc.Width) / static_cast<float>(desc.Height),    //  �A�X��
        0.1f,    //  �߂���
        1000.0f    //  ������
    );
    m_mappedSceneData->eye = eye;

    //  DescriptorHeap�̐ݒ�
    D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
    descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;    //  �V�F�[�_���猩����悤��
    descHeapDesc.NodeMask = 0;    //  �}�X�N��0
    descHeapDesc.NumDescriptors = 1;//
    descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;    //  �f�X�N���v�^�q�[�v���
    result = m_dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(m_sceneDescHeap.ReleaseAndGetAddressOf()));//����

    //  Descriptor�̐擪�n���h�����擾���Ă���
    auto heapHandle = m_sceneDescHeap->GetCPUDescriptorHandleForHeapStart();

    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    cbvDesc.BufferLocation = m_sceneConstBuff->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes = m_sceneConstBuff->GetDesc().Width;
    //  �萔�o�b�t�@�r���[�̍쐬
    m_dev->CreateConstantBufferView(&cbvDesc, heapHandle);
    return result;
}

void DirectXManager::CreateTextureLoaderTable()
{
    m_loadLambdaTable["sph"] = m_loadLambdaTable["spa"] = m_loadLambdaTable["bmp"] = m_loadLambdaTable["png"] = m_loadLambdaTable["jpg"] = [](const std::wstring& _path, TexMetadata* _meta, ScratchImage& _img)->HRESULT {
        return LoadFromWICFile(_path.c_str(), WIC_FLAGS_NONE, _meta, _img);
    };

    m_loadLambdaTable["tga"] = [](const std::wstring& _path, TexMetadata* _meta, ScratchImage& _img)->HRESULT {
        return LoadFromTGAFile(_path.c_str(), _meta, _img);
    };

    m_loadLambdaTable["dds"] = [](const std::wstring& _path, TexMetadata* _meta, ScratchImage& _img)->HRESULT {
        return LoadFromDDSFile(_path.c_str(), DDS_FLAGS_NONE, _meta, _img);
    };
}

ID3D12Resource* DirectXManager::CreateTextureFromFile(const char* _texpath)
{
    std::string texPath = _texpath;
    //  �e�N�X�`���̃��[�h
    TexMetadata metadata = {};
    ScratchImage scratchImg = {};
    auto wtexpath = GetWideStringFromString(texPath);    //  �e�N�X�`���̃t�@�C���p�X
    auto ext = GetExtension(texPath);    //  �g���q���擾
    auto result = m_loadLambdaTable[ext](wtexpath,
        &metadata,
        scratchImg);
    if (FAILED(result)) {
        return nullptr;
    }
    auto img = scratchImg.GetImage(0, 0, 0);    //  ���f�[�^���o

    //  WriteToSubresource�œ]������p�̃q�[�v�ݒ�
    auto texHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
    auto resDesc = CD3DX12_RESOURCE_DESC::Tex2D(metadata.format, metadata.width, metadata.height, metadata.arraySize, metadata.mipLevels);

    //  �e�N�X�`���p�o�b�t�@�̍쐬
    ID3D12Resource* texbuff = nullptr;
    result = m_dev->CreateCommittedResource(
        &texHeapProp,
        D3D12_HEAP_FLAG_NONE,    //  ���Ɏw��Ȃ�
        &resDesc,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
        nullptr,
        IID_PPV_ARGS(&texbuff)
    );

    if (FAILED(result)) {
        return nullptr;
    }
    result = texbuff->WriteToSubresource(0,
        nullptr,        //  �S�̈�փR�s�[
        img->pixels,    //  ���f�[�^�A�h���X
        img->rowPitch,    //  1���C���T�C�Y
        img->slicePitch    //  �S�T�C�Y
    );
    if (FAILED(result)) {
        return nullptr;
    }

    return texbuff;

}



void DirectXManager::BeginDraw()
{
    //  DirectX����
    //  BackBufferIndex���擾
    auto bbIdx = m_swapchain->GetCurrentBackBufferIndex();
    auto temp = CD3DX12_RESOURCE_BARRIER::Transition(m_backBuffers[bbIdx], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    m_cmdList->ResourceBarrier(1, &temp);


    //  RenderTarget���w��
    auto rtvH = m_rtvHeaps->GetCPUDescriptorHandleForHeapStart();
    rtvH.ptr += bbIdx * m_dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    //  �[�x���w��
    auto dsvH = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
    m_cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);
    m_cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);


    //  ��ʃN���A


    float clearColor[] = {m_nowBackGroundColorCode.x/255,m_nowBackGroundColorCode.y / 255,m_nowBackGroundColorCode.z / 255,1.0f };    //  ���F
    m_cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);

    //  Viewport�AScissorRect�̃Z�b�g
    m_cmdList->RSSetViewports(1, m_viewport.get());
    m_cmdList->RSSetScissorRects(1, m_scissorrect.get());
}

void DirectXManager::EndDraw()
{
    auto bbIdx = m_swapchain->GetCurrentBackBufferIndex();
    auto temp = CD3DX12_RESOURCE_BARRIER::Transition(m_backBuffers[bbIdx], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    m_cmdList->ResourceBarrier(1, &temp);

    //  ���߂̃N���[�Y
    m_cmdList->Close();

    //  CommandList�̎��s
    ID3D12CommandList* cmdlists[] = { m_cmdList.Get() };
    m_cmdQueue->ExecuteCommandLists(1, cmdlists);
    //  �҂�
    m_cmdQueue->Signal(m_fence.Get(), ++m_fenceVal);

    //  GPU�̏��������m�F
    if (m_fence->GetCompletedValue() < m_fenceVal) {
        auto event = CreateEvent(nullptr, false, false, nullptr);
        m_fence->SetEventOnCompletion(m_fenceVal, event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }
    //  CommandQue���N���A
    m_cmdAllocator->Reset();
    //  �Ă�CommandList�����߂鏀��
    m_cmdList->Reset(m_cmdAllocator.Get(), nullptr);
}
