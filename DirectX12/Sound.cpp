#include "Sound.h"

#include <string>

#include "EnumItr.h"
#include "SoundData.h"
#include "SoundType.h"

#include "Singleton.h"
#include "CheckError.h"

//  音量の倍率の変化量
static const float CHANGE_VOLUME_MAGNIFICATION = 0.2;

Sound::Sound()
    :m_error(Singleton<CheckError>::GetInstance())
    , m_bgmVolumeMagnification(0.9f)
    , m_seVolumeMagnification(0.9f)
   , m_volumeMagnification(0.9f)
{
    //  初期化
    Init();
}

Sound::~Sound()
{
    //  メモリの解放
    for (auto itr : m_soundQue)
    {
        itr.second.clear();
    }
}

//  初期化
void Sound::Init()
{
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    //  デフォルトのフラグを使用
    m_audioEngineflags = AudioEngine_Default;

    //  列挙型SoundTypeのイテレータを作成
    typedef EnumIterator<SoundType, SoundType::TitleBGM, SoundType::ShootSE> typeItr;

    //  全てのサウンドデータをロード
    for (auto itr : typeItr())
    {
        //  二重ロードの防止
        for (auto secondItr : typeItr())
        {
            if (itr != secondItr && SoundData::PATH_MAP[itr] == SoundData::PATH_MAP[secondItr])
            {
                std::string str = "サウンド : " + std::to_string(static_cast<int>(itr)) + "のファイルは二重にロードされています。";
                m_error.CreateErrorMessage(str);
            }
        }
        Load(itr);
    }
}

//  ロード
void Sound::Load(const SoundType& _type)
{
    //  オーディオエンジンの設定
    m_audioEngine[_type] = std::make_unique<AudioEngine>(m_audioEngineflags);

    //  サウンドファイルの読み取り
    m_soundEffect[_type] = std::make_unique<SoundEffect>(m_audioEngine[_type].get(), SoundData::PATH_MAP[_type]);
    //  エラーチェック
    if (m_soundEffect[_type] == nullptr)
    {
        std::string str = "サウンド : " + std::to_string(static_cast<int>(_type)) + " の読み取り中にエラーが発生しました。";
        m_error.CreateErrorMessage(str);
    }
}

//  再生する
//  NOTE: 再生したキューの番号を返すため、int型にしています。 
//        途中で停止させたい場合はStop関数の引数_indexに返り値を渡してください。
int Sound::Play(const SoundType& _type, const bool _isLoop, const bool _isFromBegin)
{
    //  添え字カウント用
    int index = 0;

    //  指定されたタイプのサウンドキューを検索
    for (auto itr : m_soundQue[_type])
    {

        //  停止中のキューがあればそのキューを再生に変更
        if (itr->GetState() == SoundState::STOPPED)
        {
            itr->Play(_isLoop);
            return index;
        }
        index++;
    }
    //  指定されたタイプのサウンドキューがない、
    //  もしくは全て再生中なら新しくサウンドキューを作成して再生する
    PushSoundQue(_type, _isLoop);
    return index;
}

//  停止する
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
            //  指定されたタイプのサウンドのインスタンスを生成
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
            //  ボリュームを現在のボリュームに合わせて設定
            instance->SetVolume(SoundData::FIRST_VOLUME[itr] * m_volumeMagnification * vol);
        }
        
    }

}


//  サウンドキューを作成
void Sound::PushSoundQue(const SoundType& _type, const bool _isLoop)
{
    //  指定されたタイプのサウンドのインスタンスを生成
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
    //  ボリュームを現在のボリュームに合わせて設定
    instance->SetVolume(SoundData::FIRST_VOLUME[_type] * m_volumeMagnification * vol);
    //  サウンドキュー内にインスタンスを格納
    m_soundQue[_type].emplace_back(instance);
    //  再生
    m_soundQue[_type].back()->Play(_isLoop);
}
