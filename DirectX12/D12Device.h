#pragma once
#include <tchar.h>
#include <DirectXTex.h>
#include <wrl.h>
#include"DirectXManager.h"
#include"PmdRenderer.h"
//  DXTK12
#include <SpriteFont.h>
#include <ResourceUploadBatch.h>

#pragma comment(lib,"DirectXTK12.lib")
#pragma comment(lib,"dxguid.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

class D12Device
{
public:
    D12Device();
    ~D12Device();

    //  ������
    bool Init();

    //  �f�o�C�X
    std::shared_ptr<DirectXManager> dx12;

    class Fade* m_fade;
    //  �����_���[
    std::shared_ptr<PMDRenderer> pmdRenderer;

    //  �E�B���h�E�n���h��
    HWND hwnd;
    
    
    //  �J�����̍��W���X�V
    void UpdateCameraPos(const XMFLOAT3& _eye, const XMFLOAT3& _target, const XMFLOAT3& _up);
    void SetFov(float fov);
    void SetBackGroundColor(const DirectX::XMFLOAT3& _colors);
    //  �t�H���g�p�q�[�v
    ComPtr<ID3D12DescriptorHeap> heapForSpriteFont;

    //  �O���t�B�b�N�X�������I�u�W�F�N�g
    GraphicsMemory* gmemory = nullptr;
    //  �t�H���g�\���p�I�u�W�F�N�g
    SpriteFont* spriteFont = nullptr;
    //  �X�v���C�g�\���p�I�u�W�F�N�g
    SpriteBatch* spriteBatch = nullptr;

    //  �㏈��
    void Finalize();

    //  �E�B���h�E�̃T�C�Y�̃Q�b�^�[
    SIZE GetWindowSize()const;
private:
    //  �E�B���h�E�N���X����
    WNDCLASSEX m_windowClass = {};

    //  �Q�[���p�E�B���h�E�̐���
    void CreateGameWindow();
};

