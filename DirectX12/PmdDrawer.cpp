#include "PMDDrawer.h"

#include "Material.h"
#include "DrawData.h"
#include "DirectXManager.h"

#include "Singleton.h"

#include "D12Device.h"

PMDDrawer::PMDDrawer()
    :m_device(Singleton<D12Device>::GetInstance())
{
    //  �����Ȃ�
}

PMDDrawer::~PMDDrawer()
{
    //  �����Ȃ�
}

//  �`��
void PMDDrawer::Draw(const PMDDrawData& _data, const ComPtr<ID3D12DescriptorHeap> _transformHeap)
{
    //  ���_�o�b�t�@�[�r���[�Ⓒ�_����ݒ�
    m_device.dx12->GetCommandList()->IASetVertexBuffers(0, 1, &_data.vbView);
    m_device.dx12->GetCommandList()->IASetIndexBuffer(&_data.ibView);

    //  ���W�ϊ��p�̏���ݒ�
    ID3D12DescriptorHeap* transheaps[] = { _transformHeap.Get() };
    m_device.dx12->GetCommandList()->SetDescriptorHeaps(1, transheaps);
    m_device.dx12->GetCommandList()->SetGraphicsRootDescriptorTable(1, _transformHeap->GetGPUDescriptorHandleForHeapStart());

    //  �}�e���A���̏���ݒ�
    ID3D12DescriptorHeap* mdh[] = { _data.materialHeap.Get() };
    m_device.dx12->GetCommandList()->SetDescriptorHeaps(1, mdh);
    auto materialH = _data.materialHeap->GetGPUDescriptorHandleForHeapStart();
    unsigned int idxOffset = 0;

    //  �f�B�X�N���v�^�q�[�v�̃T�C�Y�̒ǉ���
    auto cbvsrvIncSize = m_device.dx12->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * 5;

    //  �}�e���A���̐������J��Ԃ�
    for (auto& itr : _data.materials) {
        //  �f�B�X�N���v�^�q�[�v�ƃ��[�g�p�����[�^���֘A�t����
        m_device.dx12->GetCommandList()->SetGraphicsRootDescriptorTable(2, materialH);
        //  ���_�������ƂɃ��f����`��
        m_device.dx12->GetCommandList()->DrawIndexedInstanced(itr.indicesNum, 1, idxOffset, 0, 0);
        //  �}�e���A���q�[�v�̎w�����f�B�X�N���v�^�q�[�v�̃T�C�Y�������炷
        materialH.ptr += cbvsrvIncSize;
        //  �`�悵�����_���������_�`��p�̃I�t�Z�b�g�����Z
        idxOffset += itr.indicesNum;
    }
}