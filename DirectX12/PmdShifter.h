#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
#include <wrl/client.h>

using namespace Microsoft::WRL;
using namespace DirectX;

class PMDShifter
{
public:
    PMDShifter();
    ~PMDShifter();

    //  ���W�X�V
    //  TODO: �����֐����ɂ����A�������ƂɊ֐�����ύX
    void Update(const XMFLOAT3& _pos) { m_mappedTransform->world = XMMatrixTranslation(_pos.x, _pos.y, _pos.z); }
    void Update(const XMFLOAT3& _pos, const float _angle) { m_mappedTransform->world = XMMatrixRotationY(_angle) * XMMatrixTranslation(_pos.x, _pos.y, _pos.z); }

    //  ���W�Ɗg�嗦�̍X�V
    void UpdatePosAndScale(const XMFLOAT3& _pos, const float _scale) { m_mappedTransform->world = XMMatrixScaling(_scale, _scale, _scale) * XMMatrixTranslation(_pos.x, _pos.y, _pos.z); }

    //  �`��ɕK�v�ȃf�[�^�̃Q�b�^�[
    ComPtr<ID3D12DescriptorHeap> GetTransformHeap()const { return m_transformHeap; };
private:
    //  ���W�ϊ��p�r���[�̐���
    HRESULT CreateTransformView();
    //  ���[���h���W�ϊ��s��
    struct Transform
    {
        //  �����Ɏ����Ă�XMMATRIX�����o��16�o�C�g�A���C�����g�ł��邽��
        //  Transform��new����ۂɂ�16�o�C�g���E�Ɋm�ۂ���
        void* operator new(size_t _size);
        XMMATRIX world;
    };

    //  ���W�ϊ��֘A
    ComPtr<ID3D12Resource> m_transformMat;          //  �s��
    ComPtr<ID3D12DescriptorHeap> m_transformHeap;   //  �q�[�v
    Transform m_transform;                          //  ���[���h���W�ϊ��s��
    Transform* m_mappedTransform;                   //  ���[���h���W�ϊ��s��̃|�C���^
    ComPtr<ID3D12Resource> m_transformBuff;         //  �o�b�t�@�[

    //  �V���O���g���N���X�ւ̎Q��
    class D12Device& m_device;     //  �f�o�C�X�̊Ǘ�
};