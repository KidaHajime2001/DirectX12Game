#include "PMDShifter.h"

#include <d3dx12.h>

#include "DirectXManager.h"

#include "Singleton.h"
#include "D12Device.h"

PMDShifter::PMDShifter()
    :m_device(Singleton<D12Device>::GetInstance())
    , m_transformMat(nullptr)
    , m_transformHeap(nullptr)
    , m_mappedTransform(nullptr)
    , m_transformBuff(nullptr)
{
    //  ���W�ϊ��p�|�C���^�̏�����
    m_transform.world = XMMatrixIdentity();
    //  ���W�ϊ��p�r���[�̐���
    CreateTransformView();
}

PMDShifter::~PMDShifter()
{
    //  �����Ȃ�
}

//  �����Ɏ����Ă�XMMATRIX�����o��16�o�C�g�A���C�����g�ł��邽��
//  Transform��new����ۂɂ�16�o�C�g���E�Ɋm�ۂ���
void* PMDShifter::Transform::operator new(size_t _size)
{
    return _aligned_malloc(_size, 16);
}

//  ���W�ϊ��p�r���[�̐���
HRESULT PMDShifter::CreateTransformView()
{
    //  ���W�ϊ��p�o�b�t�@�̍쐬�Ə��̓]��
    auto buffSize = sizeof(Transform);
    buffSize = (buffSize + 0xff) & ~0xff;
    auto temp1 = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    auto temp2 = CD3DX12_RESOURCE_DESC::Buffer(buffSize);
    auto result = m_device.dx12->GetDevice()->CreateCommittedResource(
        &temp1,
        D3D12_HEAP_FLAG_NONE,
        &temp2,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(m_transformBuff.ReleaseAndGetAddressOf())
    );
    if (FAILED(result))
    {
        assert(SUCCEEDED(result));
        return result;
    }

    //  �쐬���������R�s�[
    result = m_transformBuff->Map(0, nullptr, (void**)&m_mappedTransform);
    if (FAILED(result)) {
        assert(SUCCEEDED(result));
        return result;
    }
    *m_mappedTransform = m_transform;

    //  ���W�ϊ��p�r���[�̍쐬
    D3D12_DESCRIPTOR_HEAP_DESC transformDescHeapDesc = {};
    transformDescHeapDesc.NumDescriptors = 1;    //  ���[���h�ЂƂ�
    transformDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    transformDescHeapDesc.NodeMask = 0;
    transformDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;    //  �f�X�N���v�^�q�[�v���
    result = m_device.dx12->GetDevice()->CreateDescriptorHeap(&transformDescHeapDesc, IID_PPV_ARGS(m_transformHeap.ReleaseAndGetAddressOf()));    //  ����
    if (FAILED(result)) {
        assert(SUCCEEDED(result));
        return result;
    }

    //  �萔�o�b�t�@�r���[�̍쐬
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    cbvDesc.BufferLocation = m_transformBuff->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes = buffSize;
    m_device.dx12->GetDevice()->CreateConstantBufferView(&cbvDesc, m_transformHeap->GetCPUDescriptorHandleForHeapStart());

    return S_OK;
}
