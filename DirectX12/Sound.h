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
    float m_volumeMagnification;

};

