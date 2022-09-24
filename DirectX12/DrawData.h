#pragma once
#include <d3d12.h>
#include <vector>
#include <wrl/client.h>

using namespace Microsoft::WRL;

//  PMD�̕`��̍ۂɕK�v�ȃf�[�^
struct PMDDrawData
{
    //  ���_�o�b�t�@�[�r���[
    D3D12_VERTEX_BUFFER_VIEW vbView;
    D3D12_INDEX_BUFFER_VIEW ibView;
    //  �}�e���A��
    std::vector<struct Material> materials;
    //  �}�e���A���q�[�v
    ComPtr<ID3D12DescriptorHeap> materialHeap;
};