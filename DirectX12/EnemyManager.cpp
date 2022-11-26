#include "EnemyManager.h"
#include"EnemyBase.h"
#include"EnemyPool.h"
#include"Time.h"
#include"EnumItr.h"
#include"EnemyType.h"
#include"EnemyAttackPool.h"
#include"ScoreData.h"

EnemyManager::EnemyManager()
    :m_enemyPool(Singleton<EnemyPool>::GetInstance())
    ,m_enemyAttackPool(Singleton<EnemyAttackPool>::GetInstance())
    ,m_timer(new Time())
{
    m_seriousDegree = 1.0f;
    m_enemyPool.CreateAll();
}

EnemyManager::~EnemyManager()
{
    m_enemyPool.DestroyAll();
    delete m_timer;
}






void EnemyManager::Update(const DirectX::XMFLOAT3& _targetPos)
{
    CallEnemy();
    for (auto enemy : m_nowAliveEnemyList)
    {
        enemy->Update(_targetPos);
        if (!enemy->IsAlive())
        {
            if (enemy->GetDefeatFlag())
            {
                AddScore(enemy->GetEnemyType());
            }
            m_deleteList.emplace_back(enemy);
        }
    }
    for (auto enemy : m_deleteList)
    {
        m_nowAliveEnemyList.remove(enemy);
    }
    m_deleteList.clear();

    m_enemyAttackPool.Update(_targetPos);
}

void EnemyManager::Draw()
{
    for (auto enemy : m_nowAliveEnemyList)
    {
        if (enemy->IsAlive())
        {
            enemy->Draw();
            
        }
    }
    m_enemyAttackPool.Draw();
}
//
//const int EnemyManager::GetScore()
//{
//    
//        m_defeatScore+=3;
//        if (m_defeatScore >= m_maxScore)
//        {
//            m_defeatScore = m_maxScore;
//        }
//        return m_defeatScore;
//}

void EnemyManager::Advent90s()
{
    int i=0;
    typedef EnumIterator<EnemyType, EnemyType::LesserEnemy, EnemyType::StraightShotEnemy> typeItr;
    //  タイプごとにエネミー攻撃クラスをプールに登録
    for (auto itr : typeItr())
    {
        i++;
    }
    int random = (rand() % (i - 1))+1;
    //大物の敵を発生
    EnemyType enemytype = (EnemyType)random;
    int positionIndex = rand() % 4;
    XMFLOAT3 position = ADVENT_EVENT_POSITION[positionIndex];
    AddEnemy(enemytype, 1, position);
}

void EnemyManager::Advent60s()
{
    AddEnemy(EnemyType::StraightShotEnemy, 1, XMFLOAT3(100,0,100));
    AddEnemy(EnemyType::StraightShotEnemy, 1, XMFLOAT3(-100, 0, -100));
}

void EnemyManager::Advent30s()
{
    AddEnemy(EnemyType::SpreadShotEnemy, 1, XMFLOAT3(100, 0, -100));
    AddEnemy(EnemyType::SpreadShotEnemy, 1, XMFLOAT3(-100, 0, 100));
}

void EnemyManager::SetGameLevel(int _level)
{
    m_seriousDegree += _level*0.1f;
}


void EnemyManager::AddScore(const EnemyType _enemyType)
{
    

        if (_enemyType==EnemyType::LesserEnemy)
        {
            m_lesserNumScore++;
        }
        else
        {
            m_higherNumScore++;
        }
    
}

void EnemyManager::CallEnemy()
{
    //端数は切り捨て
    float CallTime = DEFAULT_CALL_TIME - (SERIOUS_COEFFICIENT * m_seriousDegree);
    m_timer->SetTimer(CallTime);

    if (m_timer->CheakTime())
    {
        int i=0;
        //  列挙型EnemyAttackOrbitTypeのイテレータを作成
        typedef EnumIterator<EnemyType, EnemyType::LesserEnemy, EnemyType::StraightShotEnemy> typeItr;
        //  タイプごとにエネミー攻撃クラスをプールに登録
        for (auto itr : typeItr())
        {
            i++;
        }


        int random=rand() % i;
        int positionIndex = rand() % 4;
        XMFLOAT3 position = ADVENT_POSITION[positionIndex];
        if(positionIndex==1|| positionIndex == 0)
        {
            position.x = rand() % 200 - 100;
        }
        if (positionIndex == 2 || positionIndex == 3)
        {
            position.z = rand() % 200 - 100;
        }
        
        //大物の敵を発生
        EnemyType enemytype = (EnemyType)random;

        //雑魚敵を難易度分調整して発生させる
        int CreateLesser = 5 + (5 * m_seriousDegree);

        AddEnemy(enemytype,1, position);
        AddEnemy(EnemyType::LesserEnemy, CreateLesser, position);



    }
    
}

void EnemyManager::AddEnemy(const EnemyType& _type, const int& _num,const DirectX::XMFLOAT3& _adventPosition)
{
    
    for (int i = 0; i < _num; i++)
    {
        auto enemy = m_enemyPool.UnUsedEnemyAdvent(_type);
        
        if (enemy)
        {
            m_nowAliveEnemyList.emplace_back(enemy);
            m_nowAliveEnemyList.back()->Init();
            m_nowAliveEnemyList.back()->Advent(_adventPosition);
        }
       
    }
}
