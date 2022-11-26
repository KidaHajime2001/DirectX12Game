#pragma once
#include <Audio.h>
#include <unordered_map>
#include <vector>

enum class SoundType;
using namespace DirectX;
class Sound
{
public:
    Sound();
    ~Sound();
    //  ������
    void Init();

    //  ���[�h
    void Load(const SoundType& _type);

    //  �Đ�����
    int Play(const SoundType& _type, const bool _isLoop, const bool _isFromBegin);

    //  ��~����
    void Stop(const SoundType& _type, const int _index, const bool _immediate = true);
    void StopAll();
    void SetSoundVolume(const float _allVolume, const float _bgmVolume, const float _seVolume);
    const DirectX::XMFLOAT3 GetSonudVolume() { return DirectX::XMFLOAT3(m_volumeMagnification*10.0f, m_bgmVolumeMagnification * 10.0f, m_seVolumeMagnification * 10.0f); };
private:
    //  �T�E���h�L���[�̍쐬
    void PushSoundQue(const SoundType& _type, const bool _isLoop);
    //  �V���O���g���N���X�ւ̎Q��
    class CheckError& m_error;
    //  �T�E���h�̃��[�h�ɕK�v�ȕϐ�
    std::unordered_map<SoundType, std::unique_ptr<AudioEngine>> m_audioEngine;    //  �I�[�f�B�I�G���W��
    AUDIO_ENGINE_FLAGS m_audioEngineflags;        //  �I�[�f�B�I�G���W���t���O
    std::unique_ptr<uint8_t[]> m_wavData;              //  wav�f�[�^

    //  �T�E���h�̍Đ��ɕK�v�ȕϐ�
    std::unordered_map<SoundType, std::unique_ptr<SoundEffect>> m_soundEffect;    //  �T�E���h�G�t�F�N�g
    std::unordered_map<SoundType, std::vector<std::shared_ptr<SoundEffectInstance>>> m_soundQue;        //  �T�E���h�L���[
    //  ���ʂ̔{��
    float m_bgmVolumeMagnification;
    float m_seVolumeMagnification;
    float m_volumeMagnification;

};

