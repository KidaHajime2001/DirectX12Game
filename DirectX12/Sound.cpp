#include "Sound.h"

#include <string>

#include "EnumItr.h"
#include "SoundData.h"
#include "SoundType.h"

#include "Singleton.h"
#include "CheckError.h"

//  ���ʂ̔{���̕ω���
static const float CHANGE_VOLUME_MAGNIFICATION = 0.2;

Sound::Sound()
    :m_error(Singleton<CheckError>::GetInstance())
    , m_bgmVolumeMagnification(0.9f)
    , m_seVolumeMagnification(0.9f)
   , m_volumeMagnification(0.9f)
{
    //  ������
    Init();
}

Sound::~Sound()
{
    //  �������̉��
    for (auto itr : m_soundQue)
    {
        itr.second.clear();
    }
}

//  ������
void Sound::Init()
{
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    //  �f�t�H���g�̃t���O���g�p
    m_audioEngineflags = AudioEngine_Default;

    //  �񋓌^SoundType�̃C�e���[�^���쐬
    typedef EnumIterator<SoundType, SoundType::TitleBGM, SoundType::ShootSE> typeItr;

    //  �S�ẴT�E���h�f�[�^�����[�h
    for (auto itr : typeItr())
    {
        //  ��d���[�h�̖h�~
        for (auto secondItr : typeItr())
        {
            if (itr != secondItr && SoundData::PATH_MAP[itr] == SoundData::PATH_MAP[secondItr])
            {
                std::string str = "�T�E���h : " + std::to_string(static_cast<int>(itr)) + "�̃t�@�C���͓�d�Ƀ��[�h����Ă��܂��B";
                m_error.CreateErrorMessage(str);
            }
        }
        Load(itr);
    }
}

//  ���[�h
void Sound::Load(const SoundType& _type)
{
    //  �I�[�f�B�I�G���W���̐ݒ�
    m_audioEngine[_type] = std::make_unique<AudioEngine>(m_audioEngineflags);

    //  �T�E���h�t�@�C���̓ǂݎ��
    m_soundEffect[_type] = std::make_unique<SoundEffect>(m_audioEngine[_type].get(), SoundData::PATH_MAP[_type]);
    //  �G���[�`�F�b�N
    if (m_soundEffect[_type] == nullptr)
    {
        std::string str = "�T�E���h : " + std::to_string(static_cast<int>(_type)) + " �̓ǂݎ�蒆�ɃG���[���������܂����B";
        m_error.CreateErrorMessage(str);
    }
}

//  �Đ�����
//  NOTE: �Đ������L���[�̔ԍ���Ԃ����߁Aint�^�ɂ��Ă��܂��B 
//        �r���Œ�~���������ꍇ��Stop�֐��̈���_index�ɕԂ�l��n���Ă��������B
int Sound::Play(const SoundType& _type, const bool _isLoop, const bool _isFromBegin)
{
    //  �Y�����J�E���g�p
    int index = 0;

    //  �w�肳�ꂽ�^�C�v�̃T�E���h�L���[������
    for (auto itr : m_soundQue[_type])
    {

        //  ��~���̃L���[������΂��̃L���[���Đ��ɕύX
        if (itr->GetState() == SoundState::STOPPED)
        {
            itr->Play(_isLoop);
            return index;
        }
        index++;
    }
    //  �w�肳�ꂽ�^�C�v�̃T�E���h�L���[���Ȃ��A
    //  �������͑S�čĐ����Ȃ�V�����T�E���h�L���[���쐬���čĐ�����
    PushSoundQue(_type, _isLoop);
    return index;
}

//  ��~����
void Sound::Stop(const SoundType& _type, const int _index, const bool _immediate)
{
    m_soundQue[_type][_index]->Stop(_immediate);
}

void Sound::StopAll()
{
    typedef EnumIterator<SoundType, SoundType::TitleBGM, SoundType::ShootSE> typeItr;
    for (auto itr : typeItr())
    {
        int j = 0;
        for (auto i : m_soundQue[itr])
        {
            m_soundQue[itr][j]->Stop(true);
            j++;
        }
        j = 0;
    }
}

void Sound::SetSoundVolume(const float _allVolume, const float _bgmVolume, const float _seVolume)
{
    m_volumeMagnification = _allVolume * 0.1f;
    m_seVolumeMagnification = _seVolume * 0.1f;
    m_bgmVolumeMagnification = _bgmVolume * 0.1f;

    typedef EnumIterator<SoundType, SoundType::TitleBGM, SoundType::ShootSE> typeItr;
    for (auto itr : typeItr())
    {
        for (auto sinstance :m_soundQue[itr])
        {
            //  �w�肳�ꂽ�^�C�v�̃T�E���h�̃C���X�^���X�𐶐�
            std::shared_ptr<SoundEffectInstance> instance = sinstance;
            float vol = 1.0f;
            switch (SoundData::VOLUME_TYPE[itr])
            {
            case SoundVolumeType::BGM:
                vol = m_bgmVolumeMagnification;
                break;
            case SoundVolumeType::SE:
                vol = m_seVolumeMagnification;
                break;
            }
            //  �{�����[�������݂̃{�����[���ɍ��킹�Đݒ�
            instance->SetVolume(SoundData::FIRST_VOLUME[itr] * m_volumeMagnification * vol);
        }
        
    }

}


//  �T�E���h�L���[���쐬
void Sound::PushSoundQue(const SoundType& _type, const bool _isLoop)
{
    //  �w�肳�ꂽ�^�C�v�̃T�E���h�̃C���X�^���X�𐶐�
    std::shared_ptr<SoundEffectInstance> instance = m_soundEffect[_type]->CreateInstance();
    float vol = 1.0f;
    switch (SoundData::VOLUME_TYPE[_type])
    {
    case SoundVolumeType::BGM:
        vol = m_bgmVolumeMagnification;
        break;
    case SoundVolumeType::SE:
        vol = m_seVolumeMagnification;
        break;
    }
    //  �{�����[�������݂̃{�����[���ɍ��킹�Đݒ�
    instance->SetVolume(SoundData::FIRST_VOLUME[_type] * m_volumeMagnification * vol);
    //  �T�E���h�L���[���ɃC���X�^���X���i�[
    m_soundQue[_type].emplace_back(instance);
    //  �Đ�
    m_soundQue[_type].back()->Play(_isLoop);
}
