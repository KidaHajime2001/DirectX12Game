#include "PMDLoader.h"

#include <d3dx12.h>

#include "DirectXManager.h"
#include "PMDRenderer.h"

#include "Singleton.h"
#include "D12Device.h"
#pragma warning(disable : 4996) 
namespace
{
    ///  �e�N�X�`���̃p�X���Z�p���[�^�����ŕ�������
    ///  @param path �Ώۂ̃p�X������
    ///  @param splitter ��؂蕶��
    ///  @return �����O��̕�����y�A
    std::pair<std::string, std::string>
        SplitFileName(const std::string& _path, const char _splitter = '*') {
        int idx = _path.find(_splitter);
        std::pair<std::string, std::string> ret;
        ret.first = _path.substr(0, idx);
        ret.second = _path.substr(idx + 1, _path.length() - idx - 1);
        return ret;
    }
    ///  �t�@�C��������g���q���擾����
    ///  @param path �Ώۂ̃p�X������
    ///  @return �g���q
    std::string
        GetExtension(const std::string& _path) {
        int idx = _path.rfind('.');
        return _path.substr(idx + 1, _path.length() - idx - 1);
    }
    ///  ���f���̃p�X�ƃe�N�X�`���̃p�X���獇���p�X�𓾂�
    ///  @param modelPath �A�v���P�[�V�������猩��pmd���f���̃p�X
    ///  @param texPath PMD���f�����猩���e�N�X�`���̃p�X
    ///  @return �A�v���P�[�V�������猩���e�N�X�`���̃p�X
    std::string GetTexturePathFromModelAndTexPath(const std::string& _modelPath, const char* _texPath) {
        //  �t�@�C���̃t�H���_��؂��\��/�̓��ނ��g�p�����\��������
        //  �Ƃ�����������\��/�𓾂���΂����̂ŁA�o����rfind���Ƃ��r����
        //  int�^�ɑ�����Ă���̂͌�����Ȃ������ꍇ��rfind��epos(-1��0xffffffff)��Ԃ�����
        int pathIndex1 = _modelPath.rfind('/');
        int pathIndex2 = _modelPath.rfind('\\');
        auto pathIndex = max(pathIndex1, pathIndex2);
        auto folderPath = _modelPath.substr(0, pathIndex + 1);
        return folderPath + _texPath;
    }
}

PMDLoader::PMDLoader()
    :m_device(Singleton<D12Device>::GetInstance())
    , m_vb(nullptr)
    , m_ib(nullptr)
    , m_vbView({})
    , m_ibView({})
    , m_materialBuff(nullptr)
    , m_materialHeap(nullptr)
{
    //  �����Ȃ�
}

PMDLoader::~PMDLoader()
{
    //  �����Ȃ�
}

//  ���f���̃��[�h
void PMDLoader::LoadModel(const char* _filepath)
{
    //  PMD�����[�h
    LoadPMDFile(_filepath);
    //  �}�e���A���̏����쐬
    CreateMaterialData();
    //  �}�e���A���ƃe�N�X�`���̃r���[���쐬
    CreateMaterialAndTextureView();
}

//  �}�e���A���\���̂̃Q�b�^�[
std::vector<Material> PMDLoader::GetMaterials()const
{
    return m_materials;
}

//  �ǂݍ��񂾃}�e���A�������ƂɃ}�e���A���o�b�t�@���쐬
HRESULT PMDLoader::CreateMaterialData()
{
    //  �}�e���A���o�b�t�@���쐬
    auto materialBuffSize = sizeof(MaterialForHlsl);
    materialBuffSize = (materialBuffSize + 0xff) & ~0xff;
    auto temp1 = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    auto temp2 = CD3DX12_RESOURCE_DESC::Buffer(materialBuffSize * m_materials.size());
    auto result = m_device.dx12->GetDevice()->CreateCommittedResource(
        &temp1,
        D3D12_HEAP_FLAG_NONE,
        &temp2,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(m_materialBuff.ReleaseAndGetAddressOf())
    );
    if (FAILED(result)) {
        assert(SUCCEEDED(result));
        return result;
    }

    //  �}�b�v�}�e���A���ɃR�s�[
    char* mapMaterial = nullptr;
    result = m_materialBuff->Map(0, nullptr, (void**)&mapMaterial);
    if (FAILED(result)) {
        assert(SUCCEEDED(result));
        return result;
    }
    for (auto& m : m_materials) {
        *((MaterialForHlsl*)mapMaterial) = m.material;    //  �f�[�^�R�s�[
        mapMaterial += materialBuffSize;    //  ���̃A���C�����g�ʒu�܂Ői�߂�
    }
    m_materialBuff->Unmap(0, nullptr);

    return S_OK;
}

//  �}�e���A�����e�N�X�`���̃r���[�𐶐�
HRESULT PMDLoader::CreateMaterialAndTextureView()
{
    //  �}�e���A���̃f�B�X�N���v�^�q�[�v�쐬
    D3D12_DESCRIPTOR_HEAP_DESC materialDescHeapDesc = {};
    materialDescHeapDesc.NumDescriptors = m_materials.size() * 5;    //  �}�e���A�����Ԃ�(�萔1�A�e�N�X�`��3��)
    materialDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    materialDescHeapDesc.NodeMask = 0;
    materialDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;    //  �f�X�N���v�^�q�[�v���
    auto result = m_device.dx12->GetDevice()->CreateDescriptorHeap(&materialDescHeapDesc, IID_PPV_ARGS(m_materialHeap.ReleaseAndGetAddressOf()));   //  ����
    if (FAILED(result))
    {
        assert(SUCCEEDED(result));
        return result;
    }

    //  �}�e���A���̃o�b�t�@�[�r���[�쐬
    auto materialBuffSize = sizeof(MaterialForHlsl);
    materialBuffSize = (materialBuffSize + 0xff) & ~0xff;
    D3D12_CONSTANT_BUFFER_VIEW_DESC matCBVDesc = {};
    matCBVDesc.BufferLocation = m_materialBuff->GetGPUVirtualAddress();
    matCBVDesc.SizeInBytes = materialBuffSize;

    //  �ʏ�e�N�X�`���r���[�쐬
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;    //  2D�e�N�X�`��
    srvDesc.Texture2D.MipLevels = 1;    //  �~�b�v�}�b�v�͎g�p���Ȃ��̂�1

    //  �}�e���A���̃f�B�X�N���v�^�q�[�v�ւ̃|�C���^���擾
    CD3DX12_CPU_DESCRIPTOR_HANDLE matDescHeapH(m_materialHeap->GetCPUDescriptorHandleForHeapStart());
    auto incSize = m_device.dx12->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    //  �}�e���A���̐������������s��
    auto materialsSize = m_materials.size();
    for (int i = 0; i < materialsSize; ++i)
    {
        //  �}�e���A���Œ�o�b�t�@�r���[
        m_device.dx12->GetDevice()->CreateConstantBufferView(&matCBVDesc, matDescHeapH);
        //  �}�e���A���̃f�B�X�N���v�^�q�[�v�̎w�������̏���
        matDescHeapH.ptr += incSize;
        matCBVDesc.BufferLocation += materialBuffSize;

        //  �}�e���A�����̏�񂲂ƂɃV�F�[�_�[���\�[�r���[���쐬
        if (m_textureResources[i] == nullptr) {
            srvDesc.Format = m_device.pmdRenderer->m_whiteTex->GetDesc().Format;
            m_device.dx12->GetDevice()->CreateShaderResourceView(m_device.pmdRenderer->m_whiteTex.Get(), &srvDesc, matDescHeapH);
        }
        else {
            srvDesc.Format = m_textureResources[i]->GetDesc().Format;
            m_device.dx12->GetDevice()->CreateShaderResourceView(m_textureResources[i].Get(), &srvDesc, matDescHeapH);
        }
        matDescHeapH.Offset(incSize);

        if (m_sphResources[i] == nullptr) {
            srvDesc.Format = m_device.pmdRenderer->m_whiteTex->GetDesc().Format;
            m_device.dx12->GetDevice()->CreateShaderResourceView(m_device.pmdRenderer->m_whiteTex.Get(), &srvDesc, matDescHeapH);
        }
        else {
            srvDesc.Format = m_sphResources[i]->GetDesc().Format;
            m_device.dx12->GetDevice()->CreateShaderResourceView(m_sphResources[i].Get(), &srvDesc, matDescHeapH);
        }
        matDescHeapH.ptr += incSize;

        if (m_spaResources[i] == nullptr) {
            srvDesc.Format = m_device.pmdRenderer->m_blackTex->GetDesc().Format;
            m_device.dx12->GetDevice()->CreateShaderResourceView(m_device.pmdRenderer->m_blackTex.Get(), &srvDesc, matDescHeapH);
        }
        else {
            srvDesc.Format = m_spaResources[i]->GetDesc().Format;
            m_device.dx12->GetDevice()->CreateShaderResourceView(m_spaResources[i].Get(), &srvDesc, matDescHeapH);
        }
        matDescHeapH.ptr += incSize;


        if (m_toonResources[i] == nullptr) {
            srvDesc.Format = m_device.pmdRenderer->m_gradTex->GetDesc().Format;
            m_device.dx12->GetDevice()->CreateShaderResourceView(m_device.pmdRenderer->m_gradTex.Get(), &srvDesc, matDescHeapH);
        }
        else {
            srvDesc.Format = m_toonResources[i]->GetDesc().Format;
            m_device.dx12->GetDevice()->CreateShaderResourceView(m_toonResources[i].Get(), &srvDesc, matDescHeapH);
        }
        matDescHeapH.ptr += incSize;
    }
}

//  PMD�t�@�C���̃��[�h
HRESULT PMDLoader::LoadPMDFile(const char* _path)
{
    //  PMD�w�b�_�\����
    struct PMDHeader {
        float version;    //  ��F00 00 80 3F == 1.00
        char model_name[20];    //  ���f����
        char comment[256];        //  ���f���R�����g
    };
    //  PMD�t�@�C���̐擪�ɂ���"Pmd"�Ƃ���3�o�C�g�̕�����
    char signature[3];
    //  PMD�w�b�_�\���̂�ϐ��Ƃ��Đ錾
    PMDHeader pmdheader = {};

    //  ���f���̃t�@�C����
    std::string strModelPath = _path;

    //  �t�@�C�����ǂݎ��
    auto fp = fopen(strModelPath.c_str(), "rb");
    if (fp == nullptr) {
        //  �G���[����
        assert(0);
        return ERROR_FILE_NOT_FOUND;
    }
    //  "Pmd"�ǂݎ��
    fread(signature, sizeof(signature), 1, fp);
    //  PMD�w�b�_�\���̓ǂݎ��
    fread(&pmdheader, sizeof(pmdheader), 1, fp);

    //  ���_��
    unsigned int vertNum;
    //  ���_���ǂݎ��
    fread(&vertNum, sizeof(vertNum), 1, fp);

#pragma pack(1)    //  ��������1�o�C�g�p�b�L���O�c�A���C�����g�͔������Ȃ�
    //  PMD�}�e���A���\����
    struct PMDMaterial {
        XMFLOAT3 diffuse;     //  �f�B�t���[�Y�F
        float alpha;          //  �f�B�t���[�Y��
        float specularity;    //  �X�y�L�����̋���(��Z�l)
        XMFLOAT3 specular;    //  �X�y�L�����F
        XMFLOAT3 ambient;     //  �A���r�G���g�F
        unsigned char toonIdx;    //  �g�D�[���ԍ�
        unsigned char edgeFlg;    //  �}�e���A�����̗֊s���t���O
        //  2�o�C�g�̃p�f�B���O�������I�I
        unsigned int indicesNum;    //  ���̃}�e���A�������蓖����C���f�b�N�X��
        char texFilePath[20];       //  �e�N�X�`���t�@�C����
    };//  70�o�C�g�̂͂��c�ł��p�f�B���O���������邽��72�o�C�g
#pragma pack()    //  1�o�C�g�p�b�L���O����

    //  ���_�������̃T�C�Y
    constexpr unsigned int pmdvertex_size = 38;
    //  ���_���
    std::vector<unsigned char> vertices(vertNum * pmdvertex_size);
    //  ���_���̓ǂݎ��
    fread(vertices.data(), vertices.size(), 1, fp);

    //  ���_�C���f�b�N�X��
    unsigned int indicesNum;
    //  ���_�C���f�b�N�X���ǂݎ��
    fread(&indicesNum, sizeof(indicesNum), 1, fp);

    //  ���_�o�b�t�@�̍쐬�Ə��̓]��
    auto temp1 = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    auto temp2 = CD3DX12_RESOURCE_DESC::Buffer(vertices.size());
    auto result = m_device.dx12->GetDevice()->CreateCommittedResource(
        &temp1,
        D3D12_HEAP_FLAG_NONE,
        &temp2,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(m_vb.ReleaseAndGetAddressOf()));

    //  �쐬�����o�b�t�@�ɒ��_�����}�b�v���ăR�s�[
    unsigned char* vertMap = nullptr;
    result = m_vb->Map(0, nullptr, (void**)&vertMap);
    copy(vertices.begin(), vertices.end(), vertMap);
    m_vb->Unmap(0, nullptr);
    m_vbView.BufferLocation = m_vb->GetGPUVirtualAddress();    //  �o�b�t�@�̉��z�A�h���X
    m_vbView.SizeInBytes = vertices.size();     //  �S�o�C�g��
    m_vbView.StrideInBytes = pmdvertex_size;    //  1���_������̃o�C�g��

    //  ���_�C���f�b�N�X���
    std::vector<unsigned short> indices(indicesNum);
    //  ���_�C���f�b�N�X���̓ǂݎ��
    fread(indices.data(), indices.size() * sizeof(indices[0]), 1, fp);

    //  ���_�C���f�b�N�X�o�b�t�@�̐ݒ�Ə��̓]��
    auto temp3 = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    auto temp4 = CD3DX12_RESOURCE_DESC::Buffer(indices.size() * sizeof(indices[0]));
    result = m_device.dx12->GetDevice()->CreateCommittedResource(
        &temp3,
        D3D12_HEAP_FLAG_NONE,
        &temp4,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(m_ib.ReleaseAndGetAddressOf()));

    //  �쐬�����o�b�t�@�ɒ��_�C���f�b�N�X�����}�b�v���ăR�s�[
    unsigned short* mappedIdx = nullptr;
    m_ib->Map(0, nullptr, (void**)&mappedIdx);
    copy(indices.begin(), indices.end(), mappedIdx);
    m_ib->Unmap(0, nullptr);

    //  �C���f�b�N�X�o�b�t�@�r���[���쐬
    m_ibView.BufferLocation = m_ib->GetGPUVirtualAddress();
    m_ibView.Format = DXGI_FORMAT_R16_UINT;
    m_ibView.SizeInBytes = indices.size() * sizeof(indices[0]);

    //  �}�e���A����
    unsigned int materialNum;
    //  �}�e���A�����̓ǂݎ��
    fread(&materialNum, sizeof(materialNum), 1, fp);
    //  �}�e���A�����ɍ��킹�Ċe�f�[�^�̃T�C�Y��ύX
    m_materials.resize(materialNum);
    m_textureResources.resize(materialNum);
    m_sphResources.resize(materialNum);
    m_spaResources.resize(materialNum);
    m_toonResources.resize(materialNum);

    //  �}�e���A�����
    std::vector<PMDMaterial> pmdMaterials(materialNum);
    auto pmdMaterialsSize = pmdMaterials.size();
    //  �}�e���A�����̓ǂݎ��
    fread(pmdMaterials.data(), pmdMaterialsSize * sizeof(PMDMaterial), 1, fp);
    //  �ǂݎ���������R�s�[
    for (int i = 0; i < pmdMaterialsSize; ++i) {
        m_materials[i].indicesNum = pmdMaterials[i].indicesNum;
        m_materials[i].material.diffuse = pmdMaterials[i].diffuse;
        m_materials[i].material.alpha = pmdMaterials[i].alpha;
        m_materials[i].material.specular = pmdMaterials[i].specular;
        m_materials[i].material.specularity = pmdMaterials[i].specularity;
        m_materials[i].material.ambient = pmdMaterials[i].ambient;
        m_materials[i].additional.toonIdx = pmdMaterials[i].toonIdx;
    }

    //  �}�e���A���̃T�C�Y�����[�v����
    for (int i = 0; i < pmdMaterialsSize; ++i) {
        //  �g�D�[�����\�[�X�̓ǂݍ���
        char toonFilePath[32];
        sprintf(toonFilePath, "Data/Toon/toon%02d.bmp", pmdMaterials[i].toonIdx + 1);
        m_toonResources[i] = m_device.dx12->GetTextureByPath(toonFilePath);

        //  �e�N�X�`���̏�񂪂Ȃ��ꍇ�͏������΂�
        if (strlen(pmdMaterials[i].texFilePath) == 0) {
            m_textureResources[i] = nullptr;
            continue;
        }

        //  �e�N�X�`���A��Z�X�t�B�A�}�b�v�A���Z�X�t�B�A�}�b�v�̓ǂݍ���
        std::string texFileName = pmdMaterials[i].texFilePath;
        std::string sphFileName = "";
        std::string spaFileName = "";
        if (count(texFileName.begin(), texFileName.end(), '*') > 0) {    //  �X�v���b�^������
            auto namepair = SplitFileName(texFileName);
            if (GetExtension(namepair.first) == "sph") {
                texFileName = namepair.second;
                sphFileName = namepair.first;
            }
            else if (GetExtension(namepair.first) == "spa") {
                texFileName = namepair.second;
                spaFileName = namepair.first;
            }
            else {
                texFileName = namepair.first;
                if (GetExtension(namepair.second) == "sph") {
                    sphFileName = namepair.second;
                }
                else if (GetExtension(namepair.second) == "spa") {
                    spaFileName = namepair.second;
                }
            }
        }
        else {
            if (GetExtension(pmdMaterials[i].texFilePath) == "sph") {
                sphFileName = pmdMaterials[i].texFilePath;
                texFileName = "";
            }
            else if (GetExtension(pmdMaterials[i].texFilePath) == "spa") {
                spaFileName = pmdMaterials[i].texFilePath;
                texFileName = "";
            }
            else {
                texFileName = pmdMaterials[i].texFilePath;
            }
        }
        //  ���f���ƃe�N�X�`���p�X����A�v���P�[�V��������̃e�N�X�`���p�X�𓾂�
        if (texFileName != "") {
            auto texFilePath = GetTexturePathFromModelAndTexPath(strModelPath, texFileName.c_str());
            m_textureResources[i] = m_device.dx12->GetTextureByPath(texFilePath.c_str());
        }
        if (sphFileName != "") {
            auto sphFilePath = GetTexturePathFromModelAndTexPath(strModelPath, sphFileName.c_str());
            m_sphResources[i] = m_device.dx12->GetTextureByPath(sphFilePath.c_str());
        }
        if (spaFileName != "") {
            auto spaFilePath = GetTexturePathFromModelAndTexPath(strModelPath, spaFileName.c_str());
            m_spaResources[i] = m_device.dx12->GetTextureByPath(spaFilePath.c_str());
        }
    }
    fclose(fp);
}
