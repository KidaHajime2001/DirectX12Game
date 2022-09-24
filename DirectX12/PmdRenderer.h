#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <memory>

#include"DirectXManager.h"
using namespace Microsoft::WRL;

//  PMD�p�̃����_���[�̐ݒ���s���N���X
class PMDRenderer
{
    friend class PMDLoader;
public:
    PMDRenderer(class DirectXManager& _dx12);
    ~PMDRenderer();

    //  �Q�b�^�[
    ID3D12PipelineState* GetPipelineState()const { return m_pipeline.Get(); }            //  �p�C�v���C���X�e�[�g
    ID3D12RootSignature* GetRootSignature()const { return m_rootSignature.Get(); }       //  ���[�g�V�O�l�`��

private:
    DirectXManager& m_dx12;
    template<typename T>
    using ComPtr = ComPtr<T>;

    //  PMD�p�p�C�v���C��
    ComPtr<ID3D12PipelineState> m_pipeline = nullptr;
    //  PMD�p���[�g�V�O�l�`��
    ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;    

    //  PMD�p���ʃe�N�X�`��
    ComPtr<ID3D12Resource> m_whiteTex = nullptr;    //  ��
    ComPtr<ID3D12Resource> m_blackTex = nullptr;    //  ��    
    ComPtr<ID3D12Resource> m_gradTex = nullptr;     //  �O���[�X�P�[���O���f�[�V����

    //  �e�N�X�`���̐���
    ID3D12Resource* CreateDefaultTexture(const size_t _width, const size_t _height);    //  �W��
    ID3D12Resource* CreateWhiteTexture();                //  ��
    ID3D12Resource* CreateBlackTexture();                //  ��
    ID3D12Resource* CreateGrayGradationTexture();        //  �O���[�X�P�[���O���f�[�V����

    //  PMD�p�̃p�C�v���C���̐���
    HRESULT CreateGraphicsPipelineForPMD();
    //  ���[�g�V�O�l�`���̐���
    HRESULT CreateRootSignature();

    //  �V�F�[�_�[�ɓn�������̃`�F�b�N
    bool CheckShaderCompileResult(HRESULT _result, ID3DBlob* _error = nullptr);
};