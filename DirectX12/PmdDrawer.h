#pragma once
#include <d3d12.h>
#include <vector>
#include <wrl/client.h>

using namespace Microsoft::WRL;

//  PMD���f���̕`����s���N���X
class PMDDrawer
{
public:
    PMDDrawer();
    ~PMDDrawer();

    //  �`��
    void Draw(const struct PMDDrawData& _data, const ComPtr<ID3D12DescriptorHeap> _transformHeap);
private:
    //  �V���O���g���N���X�ւ̎Q��
    class D12Device& m_device; //  �f�o�C�X�̊Ǘ�
};