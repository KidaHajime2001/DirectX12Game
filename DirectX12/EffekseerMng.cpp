#include "EffekseerMng.h"

#include <string>

#include "EnumItr.h"
#include "EffectData.h"
#include "EffectType.h"
#include "DirectXManager.h"

#include "Singleton.h"
#include "CheckError.h"
#include "D12Device.h"

//  ��ʏ�Ɉ�x�ɕ\������ő�G�t�F�N�g��
static const int DISPLAY_EFFECT_NUM_MAX = 2000;

//  ��ʏ�Ɉ�x�ɕ\������ő�p�[�e�B�N����
static const int DESPLAY_PARTICLE_NUM_MAX = 10000;

EffekseerManager::EffekseerManager()
    :m_efkRenderer(nullptr)
    , m_efkMgr(nullptr)
    , m_efkMemoryPool(nullptr)
    , m_efkCmdList(nullptr)
    , m_device(Singleton<D12Device>::GetInstance())
    , m_error(Singleton<CheckError>::GetInstance())
{
    //  �����Ȃ�
}

EffekseerManager::~EffekseerManager()
{
    //  �����Ȃ�
}

//  ������
void EffekseerManager::Init()
{
    //  Effekseer�����_���[�̏�����
    DXGI_FORMAT bbFormats[] = { DXGI_FORMAT_R8G8B8A8_UNORM,DXGI_FORMAT_R8G8B8A8_UNORM };
    m_efkRenderer = EffekseerRendererDX12::Create(
        m_device.dx12->GetDevice().Get(),    //  DirectX12�̃f�o�C�X
        m_device.dx12->GetCmdQue(),          //  DirectX12�̃R�}���h�L���[
        2,                                   //  �o�b�N�o�b�t�@�[�̐�
        bbFormats,                           //  �����_�[�^�[�Q�b�g�t�H�[�}�b�g
        1,                                   //  �����_�[�^�[�Q�b�g��
        DXGI_FORMAT_D32_FLOAT,                 //  �f�v�X�͂Ȃ�
        false,                               //  ���΃f�v�X�͂Ȃ�
        DESPLAY_PARTICLE_NUM_MAX);                              //  �ő�p�[�e�B�N���̐�

    //  Effekseer�}�l�[�W���[�̏�����
    m_efkMgr = Effekseer::Manager::Create(DISPLAY_EFFECT_NUM_MAX);

    //  �G�t�F�N�g�̐ݒ�
    SetUpEffect();
    //  DirectX12�p�̏�����
    DX12RendererInit();

    //  �񋓌^EffectType�̃C�e���[�^���쐬
    typedef EnumIterator<EffectType, EffectType::AppearancePlayer, EffectType::DebugPos> typeItr;

    //  �G�t�F�N�g�̎�ނ̍��v���������[�h������B
    for (auto itr : typeItr())
    {
        //  ��d���[�h�̖h�~
        for (auto secondItr : typeItr())
        {
            if (itr != secondItr && EffectData::PATH_MAP[itr] == EffectData::PATH_MAP[secondItr])
            {
                std::string str = "�G�t�F�N�g : " + std::to_string(static_cast<int>(itr)) + "�̃t�@�C���͓�d�Ƀ��[�h����Ă��܂��B";
                m_error.CreateErrorMessage(str);
            }
        }
        LoadEffect(itr);
    }
}

//  �G�t�F�N�g�̐ݒ�
void EffekseerManager::SetUpEffect()
{
    //  ���W�n������n�ɂ���(�N���C�A���g���̌n�ɍ��킹��)
    m_efkMgr->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

    //  �`��p�C���X�^���X����`��@�\��ݒ�
    m_efkMgr->SetSpriteRenderer(m_efkRenderer->CreateSpriteRenderer());
    m_efkMgr->SetRibbonRenderer(m_efkRenderer->CreateRibbonRenderer());
    m_efkMgr->SetRingRenderer(m_efkRenderer->CreateRingRenderer());
    m_efkMgr->SetTrackRenderer(m_efkRenderer->CreateTrackRenderer());
    m_efkMgr->SetModelRenderer(m_efkRenderer->CreateModelRenderer());


    //  �`��p�C���X�^���X����e�N�X�`���̓ǂݍ��݋@�\��ݒ�
    //  �Ǝ��g�����\
    m_efkMgr->SetTextureLoader(m_efkRenderer->CreateTextureLoader());
    m_efkMgr->SetModelLoader(m_efkRenderer->CreateModelLoader());
    m_efkMgr->SetMaterialLoader(m_efkRenderer->CreateMaterialLoader());
}

//  DirectX12�̃����_���[�p�̏�����
void EffekseerManager::DX12RendererInit()
{
    //  �������v�[���̐ݒ�
    m_efkMemoryPool = EffekseerRenderer::CreateSingleFrameMemoryPool(m_efkRenderer->GetGraphicsDevice());
    //  �R�}���h���X�g��Effekseer�����_���[�̏����ǉ�
    m_efkCmdList = EffekseerRenderer::CreateCommandList(m_efkRenderer->GetGraphicsDevice(), m_efkMemoryPool);
    m_efkRenderer->SetCommandList(m_efkCmdList);
}

//  ���[�h
void EffekseerManager::LoadEffect(const EffectType _type)
{
    //  �t�@�C������G�t�F�N�g����ǂݎ��
    m_effect[_type] = Effekseer::Effect::Create(
        m_efkMgr,
        (const EFK_CHAR*)EffectData::PATH_MAP[_type],
        EffectData::MAGNIFICATION_MAP[_type],
        (const EFK_CHAR*)EffectData::FILE_MAP[_type]);
    //  �G���[�`�F�b�N
    if (m_effect[_type] == nullptr)
    {
        std::string str = "�G�t�F�N�g : " + std::to_string(static_cast<int>(_type)) + " �̓ǂݎ�蒆�ɃG���[���������܂����B";
        m_error.CreateErrorMessage(str);
    }
}

//  �Đ�
//  NOTE: �G�t�F�N�g�����[�v�Đ�����ꍇ�A���̊֐��ɂ���ĕԂ����l��
//        int�^�ϐ��ɕێ����A�G�t�F�N�g�n���h���Ƃ��āA
//        �X�V���~�ɗ��p����
int EffekseerManager::PlayEffect(const EffectType _type, const XMFLOAT3& _pos, bool _isLoop)
{
    //  �w�肳�ꂽ���W�Ɏw�肳�ꂽ�^�C�v�̃G�t�F�N�g���Đ�
    //  ���[�v�Đ�����Ȃ�z��Ƀf�[�^���i�[���ĕێ�����
    if (_isLoop)
    {
        LoopPlayData data;
        data.type = _type;
        data.handle = m_efkMgr->Play(m_effect[_type], _pos.x, _pos.y, _pos.z);
        m_loopPlayData.emplace_back(data);

        return data.handle;
    }
    else
    {
        return m_efkMgr->Play(m_effect[_type], _pos.x, _pos.y, _pos.z);
    }
}

//  ��~
void EffekseerManager::StopEffect(int _handle)
{
    //  �w�肳�ꂽ�G�t�F�N�g���~
    m_efkMgr->StopEffect(_handle);
    //  ���[�v�Đ����̃G�t�F�N�g�f�[�^����폜
    for (auto itr = m_loopPlayData.begin(); itr != m_loopPlayData.end(); itr++)
    {
        if (itr->handle == _handle)
        {
            m_loopPlayData.erase(itr);
            return;
        }
    }
}

//  �X�V
void EffekseerManager::Draw()
{
    //  �G�t�F�N�g�`��
    m_efkMgr->Update();                //  �}�l�[�W���[�̍X�V(���ԍX�V)
    m_efkMemoryPool->NewFrame();       //  �`�悷�ׂ������_�[�^�[�Q�b�g��I��

    //  �`�揈���̊J�n
    EffekseerRendererDX12::BeginCommandList(m_efkCmdList, m_device.dx12->GetCommandList().Get());

    //  �`��O����
    m_efkRenderer->BeginRendering();
    //  �G�t�F�N�g�`��
    m_efkMgr->Draw();
    //  �`��㏈��
    m_efkRenderer->EndRendering();

    //  �`�揈���I��
    EffekseerRendererDX12::EndCommandList(m_efkCmdList);
}

//  �G�t�F�N�g�̍X�V
//  NOTE: ���[�v�Đ�����ꍇ�́A���߂���G�t�F�N�g���Đ����Ȃ����x�Ƀn���h���̒l���ς�邽�߁A
//        int�^�ϐ���Ԃ��悤�ɂ��āA�G�t�F�N�g�n���h���̒l���X�V�ł���悤�ɂ���
int EffekseerManager::UpdateLoopPlayEffect(const XMFLOAT3& _pos, const int _handle, const XMFLOAT3& _angle)
{
    //  �n���h���ɂ���Ďw�肳�ꂽ�G�t�F�N�g�����[�v�Đ���������
    for (auto itr = m_loopPlayData.begin(); itr != m_loopPlayData.end(); itr++)
    {
        //  ���[�v�Đ����̏ꍇ
        if (itr->handle == _handle)
        {
            //  �G�t�F�N�g�̍Đ����I����Ă�����A�ŏ�����Đ����Ȃ����B
            if (!m_efkMgr->Exists(_handle))
            {
                //  �Đ�
                itr->handle = m_efkMgr->Play(m_effect[itr->type], _pos.x, _pos.y, _pos.z);
                //  �p�x�̕ύX
                m_efkMgr->SetRotation(itr->handle, _angle.x, _angle.y, _angle.z);

                return itr->handle;
            }
            //  �Đ����Ȃ�ʒu�Ɗp�x�̂ݕύX
            else
            {
                //  �Đ�
                m_efkMgr->SetLocation(_handle, _pos.x, _pos.y, _pos.z);
                //  �p�x�̕ύX
                m_efkMgr->SetRotation(itr->handle, _angle.x, _angle.y, _angle.z);

                return _handle;
            }
        }
    }
    return _handle;
}

//  �J�����ɃG�t�F�N�g�̈ʒu�𓯊�
void EffekseerManager::SyncronizeEffekseerCamera()
{
    //  Effekseer�p�r���[�s��
    Effekseer::Matrix44 fkViewMat;
    //  Effekseer�p�v���W�F�N�V�����s��
    Effekseer::Matrix44 fkProjMat;

    //  �f�o�C�X�̃r���[�s��ƃv���W�F�N�V�����s����R�s�[
    auto view = m_device.dx12->GetViewMatrix();
    auto proj = m_device.dx12->GetProjMatrix();

    //  Effekseer�p�ƃf�o�C�X��̂��ꂼ��̍s��𓯊�
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            fkViewMat.Values[i][j] = view.r[i].m128_f32[j];
            fkProjMat.Values[i][j] = proj.r[i].m128_f32[j];
        }
    }

    //  ���ꂼ��̍s��ɏ]���ăJ������ݒ�
    m_efkRenderer->SetCameraMatrix(fkViewMat);
    m_efkRenderer->SetProjectionMatrix(fkProjMat);
}
