#pragma once
#include <d3d12.h>
#include <vector>
#include <wrl/client.h>

#include "Material.h"

using namespace Microsoft::WRL;

//  PMD���f���̃��[�h���s���N���X
class PMDLoader
{
    friend class PMDRenderer;
public:
    PMDLoader();
    ~PMDLoader();

    //  ���f���̃��[�h
    void LoadModel(const char* _filepath);

    //  �`��ɕK�v�ȃf�[�^�̃Q�b�^�[
    D3D12_VERTEX_BUFFER_VIEW GetVbView()const { return m_vbView; }
    D3D12_INDEX_BUFFER_VIEW GetIbView()const { return m_ibView; }
    std::vector<struct Material> GetMaterials()const;
    ComPtr<ID3D12DescriptorHeap> GetMaterialHeap()const { return m_materialHeap; };
private:
    //  �ǂݍ��񂾃}�e���A�������ƂɃ}�e���A���o�b�t�@���쐬
    HRESULT CreateMaterialData();

    //  �}�e���A�����e�N�X�`���̃r���[�𐶐�
    HRESULT CreateMaterialAndTextureView();

    //  PMD�t�@�C���̃��[�h
    HRESULT LoadPMDFile(const char* _path);

    //  ���_�֘A
    ComPtr<ID3D12Resource> m_vb;
    ComPtr<ID3D12Resource> m_ib;
    D3D12_VERTEX_BUFFER_VIEW m_vbView;
    D3D12_INDEX_BUFFER_VIEW m_ibView;

    // �}�e���A���֘A
    std::vector<struct Material> m_materials;                 //  �}�e���A��
    ComPtr<ID3D12Resource> m_materialBuff;                    //  �o�b�t�@�[
    std::vector<ComPtr<ID3D12Resource>> m_textureResources;   //  �e�N�X�`��
    std::vector<ComPtr<ID3D12Resource>> m_sphResources;       //  sph
    std::vector<ComPtr<ID3D12Resource>> m_spaResources;       //  spa
    std::vector<ComPtr<ID3D12Resource>> m_toonResources;      //  toon
    ComPtr<ID3D12DescriptorHeap> m_materialHeap;              //  �q�[�v

    //  �V���O���g���N���X�ւ̎Q��
    class D12Device& m_device; //  �f�o�C�X�̊Ǘ�
};