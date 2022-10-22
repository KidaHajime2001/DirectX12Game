#include "EnemyAttackPool.h"
#include"EnemyAttackType.h"
#include"EnumItr.h"
#include"EnemyAttackBase.h"
#include"StraightAttack.h"
#include"HormingAimAttack.h"
EnemyAttackPool::EnemyAttackPool()
{
}

EnemyAttackPool::~EnemyAttackPool()
{
}

void EnemyAttackPool::Update(const DirectX::XMFLOAT3 _targetPos)
{
    //  列挙型EnemyAttackOrbitTypeのイテレータを作成
    typedef EnumIterator<EnemyAttackType, EnemyAttackType::StraightShot, EnemyAttackType::AimShot> typeItr;
    //  タイプごとにエネミー攻撃クラスをプールに登録
    for (auto itr : typeItr())
    {
        UpdateEnemyAttack(itr,_targetPos);
    }
}

void EnemyAttackPool::Draw()
{
    //  列挙型EnemyAttackOrbitTypeのイテレータを作成
    typedef EnumIterator<EnemyAttackType, EnemyAttackType::StraightShot, EnemyAttackType::AimShot> typeItr;
    //  タイプごとにエネミー攻撃クラスをプールに登録
    for (auto itr : typeItr())
    {
        DrawEnemyAttack(itr);
    }
}

void EnemyAttackPool::CreateAttackObj(const EnemyAttackType _type)
{
    //のちにJsonfileでデータを受け取るべき値
    int STRIGHT_ATTACK_CREATE_NUM = 100;
    int AIM_ATTACK_CREATE_NUM = 50;

    switch (_type)
    {
    case EnemyAttackType::StraightShot:
        for (int i = 0; i < STRIGHT_ATTACK_CREATE_NUM; i++)
        {
            m_StraightPool.emplace_back(new StraightAttack(_type, CollisionTag::EnemyBullet));
        }
        break;
    case EnemyAttackType::AimShot:
        for (int i = 0; i < AIM_ATTACK_CREATE_NUM; i++)
        {
            m_HormingPool.emplace_back(new HormingAimAttack(_type,CollisionTag::EnemyBullet));
        }
    default:
        break;
    }
}

EnemyAttackBase* EnemyAttackPool::GetUnUsedEnemyAttack(const EnemyAttackType _type)
{
    switch (_type)
    {
    case EnemyAttackType::StraightShot:
        for (auto shot : m_StraightPool)
        {
            if (!shot->IsAlive())
            {

                return shot;
            }
        }
        break;
    case EnemyAttackType::AimShot:
        for (auto shot:m_HormingPool)
        {
            if (!shot->IsAlive())
            {

                return shot;
            }
        }
        break;
    default:
        return nullptr;
        break;
    }
    return nullptr;
}

void EnemyAttackPool::UpdateEnemyAttack(const EnemyAttackType _type, const DirectX::XMFLOAT3 _targetPos)
{
    switch (_type)
    {
    case EnemyAttackType::StraightShot:
        for (auto shot : m_StraightPool)
        {
            if (shot->IsAlive())
            {
                shot->Update(_targetPos);
            }
        }
        break;
    case EnemyAttackType::AimShot:
        for (auto shot : m_HormingPool)
        {
            if (shot->IsAlive())
            {
                shot->Update(_targetPos);
            }
        }
        break;
    default:
        break;
    }
    return;
}

void EnemyAttackPool::DrawEnemyAttack(const EnemyAttackType _type)
{
    switch (_type)
    {
    case EnemyAttackType::StraightShot:
        for (auto shot : m_StraightPool)
        {
            if (shot->IsAlive())
            {
                shot->Draw();
            }
        }
        break;
    case EnemyAttackType::AimShot:
        for (auto shot : m_HormingPool)
        {
            if (shot->IsAlive())
            {
                shot->Draw();
            }
        }
        break;
    default:
        break;
    }
    return;
}

void EnemyAttackPool::CreateAll()
{
    //  列挙型EnemyAttackOrbitTypeのイテレータを作成
    typedef EnumIterator<EnemyAttackType, EnemyAttackType::StraightShot, EnemyAttackType::AimShot> typeItr;
    //  タイプごとにエネミー攻撃クラスをプールに登録
    for (auto itr : typeItr())
    {
        CreateAttackObj(itr);
    }
}

void EnemyAttackPool::DestroyAll()
{
    for (auto itr : m_StraightPool)
    {
        delete itr;
    }
    m_StraightPool.clear();
    m_StraightPool.shrink_to_fit();

    for (auto itr : m_HormingPool)
    {
        delete itr;
    }
    m_HormingPool.clear();
    m_HormingPool.shrink_to_fit();
}

