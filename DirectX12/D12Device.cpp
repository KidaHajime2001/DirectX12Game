#include "D12Device.h"

//  �E�B���h�E�萔
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;


LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    //  �E�B���h�E���j�����ꂽ��Ă΂��
    if (msg == WM_DESTROY) {
        //  OS�ɑ΂��āu�������̃A�v���͏I���v�Ɠ`����
        PostQuitMessage(0);
        return 0;
    }
    //  �K��̏������s��
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

SIZE D12Device::GetWindowSize() const
{
    SIZE ret;
    ret.cx = WINDOW_WIDTH;
    ret.cy = WINDOW_HEIGHT;
    return ret;
}


D12Device::D12Device()
{
}

D12Device::~D12Device()
{
}

bool D12Device::Init()
{
    //���̃X���b�h��COM���g�p���邽�߂̏���
    auto result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    CreateGameWindow();

    //  DirectX12���b�p�[������������
    dx12.reset(new DirectXManager(hwnd));


    pmdRenderer.reset(new PMDRenderer(*dx12));

    //font�֘A������
    {
        //  GraphicsMemory�I�u�W�F�N�g�̏�����
        //�@���ڂ̑���͂Ȃ�
        //�@Font�\���̍ۂɕK�v
        gmemory = new GraphicsMemory(dx12->GetDevice().Get());

        //  SpriteBatchMemory�I�u�W�F�N�g�̏�����
        ResourceUploadBatch resUploadBatch(dx12->GetDevice().Get());
        resUploadBatch.Begin();
        RenderTargetState rtState(
            DXGI_FORMAT_R8G8B8A8_UNORM,
            DXGI_FORMAT_D32_FLOAT);
        SpriteBatchPipelineStateDescription pd(rtState);
        spriteBatch = new SpriteBatch(dx12->GetDevice().Get(), resUploadBatch, pd);

        //  SpriteFont�I�u�W�F�N�g�̏�����
        heapForSpriteFont = dx12->CreateDescriptorHeapForSpriteFont();
        spriteFont = new SpriteFont(
            dx12->GetDevice().Get(),
            resUploadBatch,
            L"Data/Font/fonttest.spritefont",
            heapForSpriteFont->GetCPUDescriptorHandleForHeapStart(),
            heapForSpriteFont->GetGPUDescriptorHandleForHeapStart());

        auto future = resUploadBatch.End(dx12->GetCmdQue());        //  �]��


         //  �҂�
        dx12->WaitForCommandQueue();
        future.wait();
        spriteBatch->SetViewport(dx12->GetViewPort());
        
    }
	return true;
}

void D12Device::UpdateCameraPos(const XMFLOAT3& _eye, const XMFLOAT3& _target, const XMFLOAT3& _up)
{
    dx12->UpdateCameraPos(_eye,_target,_up);
}

void D12Device::SetFov(float fov)
{
    dx12->SetFov(fov);
}

void D12Device::Finalize()
{
    //  �����N���X�͎g��Ȃ�����o�^����
    UnregisterClass(m_windowClass.lpszClassName, m_windowClass.hInstance);
}




void D12Device::CreateGameWindow()
{
    HINSTANCE hInst = GetModuleHandle(nullptr);
    //  �E�B���h�E�N���X�������o�^
    m_windowClass.cbSize = sizeof(WNDCLASSEX);
    m_windowClass.lpfnWndProc = (WNDPROC)WindowProcedure;    //  �R�[���o�b�N�֐��̎w��
    m_windowClass.lpszClassName = _T("DirectXTest");         //  �A�v���P�[�V�����N���X��
    m_windowClass.hInstance = GetModuleHandle(0);            //  �n���h���̎擾
    RegisterClassEx(&m_windowClass);    //  �A�v���P�[�V�����N���X(���������̍�邩���낵������OS�ɗ\������)

    RECT wrc = { 0,0, WINDOW_WIDTH, WINDOW_HEIGHT };       //  �E�B���h�E�T�C�Y�����߂�
    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);    //  �E�B���h�E�̃T�C�Y�͂�����Ɩʓ|�Ȃ̂Ŋ֐����g���ĕ␳����
    //  �E�B���h�E�I�u�W�F�N�g�̐���
    hwnd = CreateWindow(m_windowClass.lpszClassName,    //  �N���X���w��
        _T("Game"),    //  �^�C�g���o�[�̕���
        WS_OVERLAPPEDWINDOW,    //  �^�C�g���o�[�Ƌ��E��������E�B���h�E�ł�
        CW_USEDEFAULT,    //  �\��X���W��OS�ɂ��C�����܂�
        CW_USEDEFAULT,    //  �\��Y���W��OS�ɂ��C�����܂�
        wrc.right - wrc.left,    //  �E�B���h�E��
        wrc.bottom - wrc.top,    //  �E�B���h�E��
        nullptr,    //  �e�E�B���h�E�n���h��
        nullptr,    //  ���j���[�n���h��
        m_windowClass.hInstance,    //  �Ăяo���A�v���P�[�V�����n���h��aa
        nullptr);    //  �ǉ��p�����[�^
}
