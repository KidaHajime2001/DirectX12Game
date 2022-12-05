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
    typedef EnumIterator<EnemyAttackType, EnemyAttackType::StraightShot, EnemyAttackType::HormingShot> typeItr;
    for (auto itr : typeItr())
    {
        UpdateEnemyAttack(itr,_targetPos);
    }
}

void EnemyAttackPool::Draw()
{
    //  列挙型EnemyAttackOrbitTypeのイテレータを作成
    typedef EnumIterator<EnemyAttackType, EnemyAttackType::StraightShot, EnemyAttackType::HormingShot> typeItr;
    for (auto itr : typeItr())
    {
        DrawEnemyAttack(itr);
    }
}

EnemyAttackBase* EnemyAttackPool::GetUnUsedEnemyAttack(const EnemyAttackType _type)
{
    //敵攻撃タイプの中で使っていないものを返す
    //そうでなければNULLPOINTERを返す
    for (auto shot:m_poolMap[_type])
    {
        if (!shot->IsAlive())
        {
            return shot;
        }
    }
    return nullptr;
}

void EnemyAttackPool::UpdateEnemyAttack(const EnemyAttackType _type, const DirectX::XMFLOAT3 _targetPos)
{
    //敵攻撃タイプごとの更新
    for (auto shot : m_poolMap[_type])
    {
        if (shot->IsAlive())
        {
            shot->Update(_targetPos);
        }
    }
    return;
}

void EnemyAttackPool::DrawEnemyAttack(const EnemyAttackType _type)
{
    //敵攻撃タイプごとの描画
    for (auto shot : m_poolMap[_type])
    {
        if (shot->IsAlive())
        {
            shot->Draw();
        }
    }
    return;
}

void EnemyAttackPool::CreateAll()
{
    //のちにJsonfileでデータを受け取るべき値
    int STRIGHT_ATTACK_CREATE_NUM = 100;
    int AIM_ATTACK_CREATE_NUM = 50;
    for (int i = 0; i < STRIGHT_ATTACK_CREATE_NUM; i++)
    {
        m_StraightPool.emplace_back(new StraightAttack(EnemyAttackType::StraightShot, CollisionTag::EnemyBullet));
    }
    for (int i = 0; i < AIM_ATTACK_CREATE_NUM; i++)
    {
        m_HormingPool.emplace_back(new HormingAimAttack(EnemyAttackType::HormingShot, CollisionTag::EnemyBullet));
    }
    //マップで紐づけしてイテレーターで使用できるように
    m_poolMap[EnemyAttackType::StraightShot] = m_StraightPool;
    m_poolMap[EnemyAttackType::HormingShot] = m_HormingPool;
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

