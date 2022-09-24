#pragma once
#include <Effekseer.h>
#include <EffekseerRendererDX12.h>
#include <DirectXMath.h>
#include <unordered_map>
#include <list>

#pragma comment(lib,"EffekseerRendererDX12.lib")
#pragma comment(lib,"Effekseer.lib")
#pragma comment(lib,"LLGI.lib")

using namespace DirectX;

enum class EffectType;
//  Effekseer�̃��[�h��Đ����s���N���X
//  �V���O���g���ň���
class EffekseerManager
{
public:
    EffekseerManager();
    ~EffekseerManager();

    //  ������
    void Init();

    //  �G�t�F�N�g�̍Đ�
    //  NOTE: �G�t�F�N�g�����[�v�Đ�����ꍇ�A���̊֐��ɂ���ĕԂ����l��
    //        int�^�ϐ��ɕێ����A�G�t�F�N�g�n���h���Ƃ��āA
    //        �X�V���~�ɗ��p����
    int PlayEffect(const EffectType _type, const XMFLOAT3& _pos, bool _isLoop);

    //  �G�t�F�N�g�̒�~
    void StopEffect(int _handle);

    //  �`��
    void Draw();

    //  �G�t�F�N�g�̍X�V
    //  NOTE: ���[�v�Đ�����ꍇ�́A���߂���G�t�F�N�g���Đ����Ȃ����x�Ƀn���h���̒l���ς�邽�߁A
    //        int�^�ϐ���Ԃ��悤�ɂ��āA�G�t�F�N�g�n���h���̒l���X�V�ł���悤�ɂ���
    //  NOTE: ���̊֐����ĂԂ̂́A���[�v�Đ����Ă���G�t�F�N�g������ꍇ�̂�
    int UpdateLoopPlayEffect(const XMFLOAT3& _pos, const int _handle, const XMFLOAT3& _angle = { 0.0f,0.0f,0.0f });

    //  �J������Effekseer�̕\���ꏊ�̓���
    void SyncronizeEffekseerCamera();
private:
    //  �G�t�F�N�g�����ɕK�v�Ȑݒ�
    void SetUpEffect();

    //  DirectX12��p��Renderer�̏�����
    void DX12RendererInit();

    //  �G�t�F�N�g�t�@�C���̓ǂݍ���
    void LoadEffect(const EffectType _type);

    //  �G�t�F�N�g�}�l�[�W���[
    Effekseer::RefPtr<Effekseer::Manager> m_efkMgr;

    //  �G�t�F�N�g�����_���[
    Effekseer::RefPtr<EffekseerRenderer::Renderer> m_efkRenderer;

    //  �������v�[��
    Effekseer::RefPtr<EffekseerRenderer::SingleFrameMemoryPool> m_efkMemoryPool;

    //  �R�}���h���X�g
    Effekseer::RefPtr<EffekseerRenderer::CommandList> m_efkCmdList;

    //  �G�t�F�N�g�{��
    std::unordered_map<EffectType, Effekseer::RefPtr<Effekseer::Effect>> m_effect;

    //  ���[�v�Đ����̃G�t�F�N�g�̃f�[�^
    struct LoopPlayData
    {
        Effekseer::Handle handle;
        EffectType type;
    };
    std::list<LoopPlayData> m_loopPlayData;

    //  �V���O���g���N���X�ւ̎Q��
    class D12Device& m_device;     //  �f�o�C�X�̊Ǘ�
    class CheckError& m_error;
};