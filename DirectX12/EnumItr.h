#pragma once
#pragma once
#include <type_traits>

//  �񋓌^T�̃C�e���[�^���쐬����N���X
//  beginVal: �C�e���[�^�̍ŏ��̗v�f
//  endVal: �C�e���[�^�̍Ō�̗v�f
//  NOTE: �e���v���[�g�N���X�̂��߃w�b�_�[�ɒ�`���L�q
template < typename T, T beginVal, T endVal>
class EnumIterator {
public:
    //  �C�e���[�^�̎n�[���w���R���X�g���N�^
    EnumIterator() : m_val(static_cast<m_val_t>(beginVal)) {}
    //  �C�e���[�^�̏I�[���w���R���X�g���N�^
    EnumIterator(const T& _end) : m_val(static_cast<m_val_t>(_end)) {}
    //  �C�e���[�^�����̗v�f���w���悤�ɉ��Z�q++���I�[�o�[���[�h
    EnumIterator operator++()
    {
        m_val++;
        return *this;
    }
    //  �C�e���[�^�����ݎw���Ă���v�f��Ԃ��悤�ɊԐډ��Z�q���I�[�o�[���[�h
    T operator*()const { return static_cast<T>(m_val); }
    //  �n�[�̗v�f
    EnumIterator begin()const { return *this; }
    //  �I�[�̗v�f
    EnumIterator end() {
        static const EnumIterator endIter = ++EnumIterator(endVal);
        return endIter;
    }
    //  �C�e���[�^�̏I�[�����m���邽�߂ɉ��Z�q!=���I�[�o�[���[�h
    bool operator!=(const EnumIterator& _end)const { return m_val != _end.m_val; }
private:
    //  �񋓌^�����S�ɃL���X�g�ł���悤�ɗ񋓌^T�̊��^���擾
    //  NOTE: underlying_type<T>::type�ŗ񋓌^T�̊��^���擾�ł���
    typedef typename std::underlying_type<T>::type m_val_t;
    //  ���ݎw���Ă���v�f�̔ԍ�
    int m_val;
};