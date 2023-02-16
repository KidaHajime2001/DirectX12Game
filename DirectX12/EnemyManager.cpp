#include "EnemyManager.h"
#include"EnemyBase.h"
#include"EnemyPool.h"
#include"Time.h"
#include"EnumItr.h"
#include"EnemyType.h"
#include"EnemyAttackPool.h"
#include"ScoreData.h"
#include"ItemManager.h"
EnemyManager::EnemyManager()
    :m_enemyPool(Singleton<EnemyPool>::GetInstance())
    , m_enemyAttackPool(Singleton<EnemyAttackPool>::GetInstance())
    , m_itemManager(new ItemManager())
    ,m_timer(new Time())
{
    //難易度初期化
    m_seriousDegree = 1.0f;
    //エネミープールの中身を作成
    m_enemyPool.CreateAll();
}

EnemyManager::~EnemyManager()
{
    //エネミープールの中身を削除
    m_enemyPool.DestroyAll();
    delete m_itemManager;
    delete m_timer;
}

void EnemyManager::Update(const DirectX::XMFLOAT3& _targetPos)
{
    //敵を呼び出す
    CallEnemy();

    //現在生きているリストに入っている敵の更新
    for (auto enemy : m_nowAliveEnemyList)
    {
        enemy->Update(_targetPos);
        //生存フラグがOFFになったら
        if (!enemy->IsAlive())
        {
            m_itemManager->CreateDropItem(enemy->GetEnemyType(),enemy->GetPosition());
            //スコア用の数値加算
            AddScore(enemy->GetEnemyType());

            //現在動いているリストから削除するためのリストへ
            m_deleteList.emplace_back(enemy);
        }

    }
    m_itemManager->Update();

    //現在のリストから消去
    for (auto enemy : m_deleteList)
    {
        m_nowAliveEnemyList.remove(enemy);
    }
    m_deleteList.clear();
    //弾の更新
    m_enemyAttackPool.Update(_targetPos);
}

void EnemyManager::Draw()
{
    m_itemManager->Draw();
}

void EnemyManager::LineDraw()
{
    //生存している敵描画
    for (auto enemy : m_nowAliveEnemyList)
    {
        enemy->Draw();
    }
    
    m_enemyAttackPool.Draw();
}

void EnemyManager::Advent90s()
{
    //int i=0;
    //typedef EnumIterator<EnemyType, EnemyType::LesserEnemy, EnemyType::StraightShotEnemy> typeItr;
    ////タイプの数をカウント
    //for (auto itr : typeItr())
    //{
    //    i++;
    //}
    ////エネミーのタイプを決定したい
    ////雑魚を除外して計算
    //int random = (rand() % (i - 1))+1;
    //EnemyType enemytype = (EnemyType)random;
    ////ランダムポジションを作成
    //int positionIndex = rand() % 4;
    //XMFLOAT3 position = ADVENT_EVENT_POSITION[positionIndex];
    ////呼び出し
    //AddEnemy(enemytype, 1, position);


   /* AddEnemy(EnemyType::SnakeEnemy, 1, XMFLOAT3(100, 0, -100));*/
}

void EnemyManager::Advent60s()
{
    AddEnemy(EnemyType::LesserEnemy, 50, XMFLOAT3(100, 0, -100));

    AddEnemy(EnemyType::LesserEnemy, 50, XMFLOAT3(-100, 0, 100));
    ////二か所から特定の敵を出現
    //AddEnemy(EnemyType::StraightShotEnemy, 1, XMFLOAT3(100,0,100));
    //AddEnemy(EnemyType::StraightShotEnemy, 1, XMFLOAT3(-100, 0, -100));
}

void EnemyManager::Advent30s()
{
    //二か所から特定の敵を出現
    AddEnemy(EnemyType::LesserEnemy, 75, XMFLOAT3(-100, 0, -100));

    AddEnemy(EnemyType::LesserEnemy, 75, XMFLOAT3(100, 0, 100));
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
        //タイプをカウント
        for (auto itr : typeItr())
        {
            i++;
        }

        //タイプをランダムに選ぶ
        int random=rand() % i;
        //ランダムにポジションを選ぶ
        int positionIndex = rand() % 4;
        XMFLOAT3 position = ADVENT_POSITION[positionIndex];

        //出現ポイントを散らす
        if(positionIndex==1|| positionIndex == 0)
        {
            position.x = rand() % 200 - 100;
        }
        if (positionIndex == 2 || positionIndex == 3)
        {
            position.z = rand() % 200 - 100;
        }
        
        //敵を発生
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
        //エネミープールから取得できている場合
        if (enemy)
        {
            //出現に当たっての初期化
            m_nowAliveEnemyList.emplace_back(enemy);
            m_nowAliveEnemyList.back()->Init();
            m_nowAliveEnemyList.back()->Advent(_adventPosition);
        }
       
    }
}
