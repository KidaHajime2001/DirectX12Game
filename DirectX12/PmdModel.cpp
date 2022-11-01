#include "PmdModel.h"

#include <vector>

#include "EnumItr.h"

#include "DrawData.h"
#include "ModelTypeData.h"
#include "ModelData.h"

#include "PMDDrawer.h"
#include "PMDLoader.h"
#include "PMDShifter.h"

PMDModel::PMDModel()
    :m_drawClassIndexNumber(0)
{
    //  �񋓌^PMDModelType�̃C�e���[�^���쐬
    typedef EnumIterator<PMDModelType, PMDModelType::Player, PMDModelType::BackGround> typeItr;

    //  ���f����S�ă��[�h
    for (auto itr : typeItr())
    {
        Load(itr);
    }
}

PMDModel::~PMDModel()
{
    //  �������̉��
    m_drawData.clear();
    m_loader.clear();
    m_shifter.clear();
    m_shifter.shrink_to_fit();
    m_drawer.clear();
    m_drawer.shrink_to_fit();
}

//  �X�V
void PMDModel::Update()
{
    //  ���̃��[�v�p�ɏ�����
    //  NOTE: ���W�ϊ��ƕ`����s���N���X��z�񉻂��Ă���A
    //        ���[�v���Ƃɔz��̐擪�ɂ���N���X����`�揈�����s�����߂ɁA
    //        �z��̓Y�����Ɏw�肷�邱�̕ϐ��𖈃��[�v0�ŏ��������Ă��܂��B
    m_drawClassIndexNumber = 0;
}

//  �`��
void PMDModel::Draw(const XMFLOAT3& _pos, const PMDModelType _type)
{
    //  ���W�ϊ��p�̏����쐬
    PMDShifter* temp = m_shifter[m_drawClassIndexNumber];
    temp->Update(_pos);
    //  �`��p�̏����쐬
    m_drawer[m_drawClassIndexNumber]->Draw(*m_drawData[_type], temp->GetTransformHeap());
    //  ���̕`��p�ɔԍ������Z
    m_drawClassIndexNumber++;
}
void PMDModel::Draw(const XMFLOAT3& _pos, const float _angle, const PMDModelType _type)
{
    //  ���W�ϊ��p�̏����쐬
    PMDShifter* temp = m_shifter[m_drawClassIndexNumber];
    temp->Update(_pos, _angle);
    //  �`��p�̏����쐬
    m_drawer[m_drawClassIndexNumber]->Draw(*m_drawData[_type], temp->GetTransformHeap());
    //  ���̕`��p�ɔԍ������Z
    m_drawClassIndexNumber++;
}
void PMDModel::Draw(const XMFLOAT3& _pos, const XMFLOAT3 _angle, const PMDModelType _type)
{ //  ���W�ϊ��p�̏����쐬
    PMDShifter* temp = m_shifter[m_drawClassIndexNumber];
    temp->Update(_pos, _angle);
    //  �`��p�̏����쐬
    m_drawer[m_drawClassIndexNumber]->Draw(*m_drawData[_type], temp->GetTransformHeap());
    //  ���̕`��p�ɔԍ������Z
    m_drawClassIndexNumber++;
}
//  �g�嗦�ƍ��W��ύX���ĕ`��
void PMDModel::DrawChangePosAndScale(const XMFLOAT3& _pos, const float _scale, const PMDModelType _type)
{
    //  ���W�ϊ��p�̏����쐬
    PMDShifter* temp = m_shifter[m_drawClassIndexNumber];
    temp->UpdatePosAndScale(_pos, _scale);
    //  �`��p�̏����쐬
    m_drawer[m_drawClassIndexNumber]->Draw(*m_drawData[_type], temp->GetTransformHeap());
    //  ���̕`��p�ɔԍ������Z
    m_drawClassIndexNumber++;
}

//  ���f����`�悷�邽�߂̐ݒ�
void PMDModel::SetUp(const int _modelNum)
{
    //  �w�萔�N���X�̃C���X�^���X�𐶐�
    for (int i = 0; i < _modelNum; i++)
    {
        m_shifter.emplace_back(new PMDShifter());
        m_drawer.emplace_back(new PMDDrawer());
    }
}

const PMDModelType PMDModel::GetModelType(const std::string _typename)
{

    if (_typename == "BlueEnemy")
    {
        return PMDModelType::BlueEnemy;
    }
    if (_typename == "YellowEnemy")
    {
        return PMDModelType::YellowEnemy;
    }

    return PMDModelType::AimingBullet;
}

//  ���[�h
void PMDModel::Load(const PMDModelType _type)
{
    PMDDrawData* tempData = new PMDDrawData();
    PMDLoader* tempLoader = new PMDLoader();
    //  ���f���̃t�@�C������������[�h
    tempLoader->LoadModel(PMDModelData::FILE_PATH[_type].c_str());
    //  �ǂݍ��񂾏����\���̂ɃR�s�[���ĕۑ�
    tempData->vbView = tempLoader->GetVbView();
    tempData->ibView = tempLoader->GetIbView();
    tempData->materials = tempLoader->GetMaterials();
    tempData->materialHeap = tempLoader->GetMaterialHeap();
    m_drawData[_type] = tempData;
    m_loader[_type] = tempLoader;
}
