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
    //  初期化
    void Init();

    //  ロード
    void Load(const SoundType& _type);

    //  再生する
    int Play(const SoundType& _type, const bool _isLoop, const bool _isFromBegin);

    //  停止する
    void Stop(const SoundType& _type, const int _index, const bool _immediate = true);
private:
    //  サウンドキューの作成
    void PushSoundQue(const SoundType& _type, const bool _isLoop);
    //  シングルトンクラスへの参照
    class CheckError& m_error;
    //  サウンドのロードに必要な変数
    std::unordered_map<SoundType, std::unique_ptr<AudioEngine>> m_audioEngine;    //  オーディオエンジン
    AUDIO_ENGINE_FLAGS m_audioEngineflags;        //  オーディオエンジンフラグ
    std::unique_ptr<uint8_t[]> m_wavData;              //  wavデータ

    //  サウンドの再生に必要な変数
    std::unordered_map<SoundType, std::unique_ptr<SoundEffect>> m_soundEffect;    //  サウンドエフェクト
    std::unordered_map<SoundType, std::vector<std::shared_ptr<SoundEffectInstance>>> m_soundQue;        //  サウンドキュー
    //  音量の倍率
    float m_volumeMagnification;

};

