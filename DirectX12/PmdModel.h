#pragma once
#include <DirectXMath.h>
#include <unordered_map>
#include <vector>

using namespace DirectX;

enum class PMDModelType;
//  PMD���f���̃��[�h��`����s���N���X
class PMDModel
{
public:
    PMDModel();
    ~PMDModel();

    //  �X�V
    void Update();

    //  �`��
    //  TODO: �����֐����ɂ����A�������ƂɊ֐�����ύX
    void Draw(const XMFLOAT3& _pos, const PMDModelType _type);
    void Draw(const XMFLOAT3& _pos, const float _angle, const PMDModelType _type);

    //  �g�嗦�ƍ��W��ύX���ĕ`��
    void DrawChangePosAndScale(const XMFLOAT3& _pos, const float _scale, const PMDModelType _type);

    //  ���f����`�悷�邽�߂̐ݒ�
    void SetUp(const int _modelNum = 1);
private:
    //  ���[�h
    void Load(const PMDModelType _type);

    //  �`��p�N���X�̔z��̓Y�������w�肷��ԍ�
    int m_drawClassIndexNumber;

    //  �\���̂ւ̃|�C���^
    std::unordered_map<PMDModelType, struct PMDDrawData*> m_drawData;    //  PMD�̕`��ɕK�v�ȃf�[�^

    //  �V���O���g���N���X�ւ̎Q��
    std::unordered_map<PMDModelType, class PMDLoader*> m_loader; //  PMD���f���̃��[�h
    std::vector<class PMDShifter*> m_shifter;       //  PMD���f���̍��W�ϊ�
    std::vector<class PMDDrawer*> m_drawer;         //  PMD���f���̕`��
};