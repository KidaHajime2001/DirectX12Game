#include "EnemyPool.h"
#include"EnemyType.h"
#include"EnumItr.h"
#include"LesserEnemy.h"
#include"StraightShotEnemy.h"
#include"SpreadShotEnemy.h"
#include"CollisionManager.h"
#include"SnakeEnemy.h"
EnemyPool::EnemyPool()
{
}

EnemyPool::~EnemyPool()
{
}

 EnemyBase* EnemyPool::UnUsedEnemyAdvent(const EnemyType _type)
{
    for (auto enemy : m_enemyPool[_type])
    {
        if (!enemy->IsAlive())
        {
            return enemy;
        }
    }
    return nullptr;
}

 void EnemyPool::AddCollision( CollisionManager* _mng)
 {
     typedef EnumIterator<EnemyType, EnemyType::LesserEnemy, EnemyType::AimShotEnemy> typeItr;
     //  タイプごとにエネミー攻撃クラスをプールに登録
     for (auto itr : typeItr())
     {
         for (auto enemyColision : m_enemyPool[itr])
         {
             _mng->AddCollision(enemyColision->GetCollision());
         }
        
     }
    
 }

 void EnemyPool::DeleteCollision(CollisionManager* _mng)
 {
     typedef EnumIterator<EnemyType, EnemyType::LesserEnemy, EnemyType::AimShotEnemy> typeItr;
     //  タイプごとにエネミー攻撃クラスをプールに登録
     for (auto itr : typeItr())
     {
         for (auto enemyColision : m_enemyPool[itr])
         {
             _mng->RemoveCollision(enemyColision->GetCollision());
         }

     }
 }



 void EnemyPool::CreateAll()
 {
     //  列挙型EnemyAttackOrbitTypeのイテレータを作成
     typedef EnumIterator<EnemyType, EnemyType::LesserEnemy, EnemyType::AimShotEnemy> typeItr;
     //  タイプごとにエネミー攻撃クラスをプールに登録
     for (auto itr : typeItr())
     {
         Create(itr);
     }
 }

 void EnemyPool::Create(const EnemyType _type)
{
    switch (_type)
    {
    case EnemyType::LesserEnemy:
        for (int i = 0; i < LESSER_POOL_MAX; i++)
        {
            m_enemyPool[_type].emplace_back(new LesserEnemy(CollisionTag::Enemy, false));
        } 
        break;

    case EnemyType::StraightShotEnemy:
        for (int i = 0; i < ADVENT_MAX; i++)
        {
            m_enemyPool[_type].emplace_back(new StraightShotEnemy(CollisionTag::Enemy, false));
        }
        break;

    case EnemyType::SpreadShotEnemy:
        for (int i = 0; i < ADVENT_MAX; i++)
        {
            m_enemyPool[_type].emplace_back(new SpreadShotEnemy(CollisionTag::Enemy, false));
        }
        break;
    case EnemyType::SnakeEnemy :
        for (int i = 0; i < 1/*ADVENT_MAX*/; i++)
        {
            m_enemyPool[_type].emplace_back(new SnakeEnemy(CollisionTag::Enemy, false));
        }
        break;
    default:
        break;
    }


}

void EnemyPool::DestroyAll()
{
    typedef EnumIterator<EnemyType, EnemyType::LesserEnemy, EnemyType::AimShotEnemy> typeItr;
    //  タイプごとにエネミー攻撃クラスをプールに登録
    for (auto itr : typeItr())
    {
        for (auto enemy : m_enemyPool[itr])
        {
            if (enemy)
            {
                delete enemy;

            }
            
        };
        m_enemyPool[itr].clear();
        m_enemyPool[itr].shrink_to_fit();
    }
}
