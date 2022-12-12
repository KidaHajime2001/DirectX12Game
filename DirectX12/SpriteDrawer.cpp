#include "SpriteDrawer.h"

#include <CommonStates.h>
#include <WICTextureLoader.h>

#include "EnumItr.h"
#include "SpriteData.h"
#include"DirectXManager.h"

#include "Singleton.h"
#include "CheckError.h"
#include "D12Device.h"

SpriteDrawer::SpriteDrawer()
    :m_device(Singleton<D12Device>::GetInstance())
    , m_error(Singleton<CheckError>::GetInstance())
{
    //  DescriptorHeap�̏�����
    m_resourceDescriptors = std::make_unique<DescriptorHeap>(m_device.dx12->GetDevice().Get(), SpriteType::EndDescriptors);
    D3D12_DESCRIPTOR_HEAP_DESC transformDescHeapDesc = {};
    //  ���[�h���̎w��
    m_texture.resize(static_cast<int>(SpriteType::EndDescriptors));
    //  ���[�h����
    Load();
}

SpriteDrawer::~SpriteDrawer()
{
    //  �������̉��
    m_texture.clear();
    m_texture.shrink_to_fit();
    m_resourceDescriptors.reset();
    m_spriteBatch.reset();
}

//  �`��
void SpriteDrawer::Draw(const SpriteType _handle, const XMFLOAT2& _pos, const float _magnification, const XMVECTOR& _color)
{
    //  DescriptorHeap�̐ݒ�
    ID3D12DescriptorHeap* heaps[] = { m_resourceDescriptors->Heap() };
    m_device.dx12->GetCommandList()->SetDescriptorHeaps(static_cast<UINT>(std::size(heaps)), heaps);

    //  �T�C�Y�𒲐�
    XMUINT2 size = { static_cast<UINT>(GetTextureSize(m_texture[static_cast<int>(_handle)].Get()).x * _magnification),static_cast<UINT>(GetTextureSize(m_texture[static_cast<int>(_handle)].Get()).y * _magnification) };

    //  �`�悷��
    m_spriteBatch->Begin(m_device.dx12->GetCommandList().Get());
    m_spriteBatch->Draw(m_resourceDescriptors->GetGpuHandle(static_cast<size_t>(_handle)), size, _pos, _color);
    m_spriteBatch->End();
}

//  �`��(�摜�̕`��͈͂��w�肷��ꍇ)
void SpriteDrawer::Draw(const SpriteType _handle, const XMFLOAT2& _pos
    , const float _topMagnification, const float _leftMagnification, const float _bottomMagnification, const float _rightMagnification
    , const float _magnification, const XMVECTOR& _color)
{
    //  DescriptorHeap�̐ݒ�
    ID3D12DescriptorHeap* heaps[] = { m_resourceDescriptors->Heap() };
    m_device.dx12->GetCommandList()->SetDescriptorHeaps(static_cast<UINT>(std::size(heaps)), heaps);

    //  �T�C�Y�𒲐�
    XMUINT2 size = { static_cast<UINT>(GetTextureSize(m_texture[static_cast<int>(_handle)].Get()).x * _magnification),static_cast<UINT>(GetTextureSize(m_texture[static_cast<int>(_handle)].Get()).y * _magnification) };

    //  �`��͈͎w��
    //  NOTE: �摜�̉�����\�����邩���㉺���E�l��������w��
    RECT rect;
    rect.top = static_cast<LONG>(size.y - _topMagnification * size.y);
    rect.left = static_cast<LONG>(size.x - _leftMagnification * size.x);
    rect.bottom = static_cast<LONG>(_bottomMagnification * size.y);
    rect.right = static_cast<LONG>(_rightMagnification * size.x);

    //  �`�悷��
    m_spriteBatch->Begin(m_device.dx12->GetCommandList().Get());
    m_spriteBatch->Draw(m_resourceDescriptors->GetGpuHandle(static_cast<size_t>(_handle)), size, _pos, &rect, _color);
    m_spriteBatch->End();
}

//  ���[�h
int SpriteDrawer::Load()
{
    //  SpriteBatch�I�u�W�F�N�g�̏�����
    ResourceUploadBatch resourceUpload(m_device.dx12->GetDevice().Get());
    resourceUpload.Begin();
    RenderTargetState rtState(DXGI_FORMAT_R8G8B8A8_UNORM,
        DXGI_FORMAT_D32_FLOAT);
    SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
    m_spriteBatch = std::make_unique<SpriteBatch>(m_device.dx12->GetDevice().Get(), resourceUpload, pd);

    //  �񋓌^SpriteType�̃C�e���[�^���쐬
    typedef EnumIterator<SpriteType, SpriteType::TitleBack, SpriteType::ResultLine> typeItr;

    for (auto itr : typeItr())
    {
        //  ��d���[�h�̖h�~
        for (auto secondItr : typeItr())
        {
            if (itr != secondItr && SpriteData::FILE_PATH[itr] == SpriteData::FILE_PATH[secondItr])
            {
                std::string str = "�摜 : " + std::to_string(static_cast<int>(itr)) + "�̃t�@�C���͓�d�Ƀ��[�h����Ă��܂��B";
                m_error.CreateErrorMessage(str);
            }
        }
        //  �e�N�X�`���t�@�C���ǂݍ���
        if (FAILED(CreateWICTextureFromFile(m_device.dx12->GetDevice().Get(),
            resourceUpload,
            SpriteData::FILE_PATH[itr],
            m_texture[static_cast<int>(itr)].ReleaseAndGetAddressOf())))
        {
            assert(0);
            return -1;
        }
        //  �V�F�[�_�[���\�[�X�r���[�̍쐬
        CreateShaderResourceView(m_device.dx12->GetDevice().Get(), m_texture[static_cast<int>(itr)].Get(), m_resourceDescriptors->GetCpuHandle(static_cast<size_t>(itr)));
    }

    //  SpriteBatch�I�u�W�F�N�g�̌㏈��
    auto uploadResourcesFinished = resourceUpload.End(m_device.dx12->GetCmdQue());
    uploadResourcesFinished.wait();

    //  SpriteBatch�Ƀr���[�|�[�g���Z�b�g
    m_spriteBatch->SetViewport(m_device.dx12->GetViewPort());
}

//  �F���w�肷�鎞�ɌĂяo���֐�
//  ColorType�ƃA���t�@�l���w��
XMVECTORF32 SpriteDrawer::GetColorWithalpha(const float _alpha)
{
    return { Colors::White.f[0],Colors::White.f[1],Colors::White.f[2],_alpha };
}