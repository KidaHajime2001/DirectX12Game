#include "EnemyManager.h"
#include"EnemyBase.h"
#include"EnemyPool.h"
#include"Time.h"
#include"EnumItr.h"
#include"EnemyType.h"
#include"EnemyAttackPool.h"
EnemyManager::EnemyManager()
    :m_enemyPool(Singleton<EnemyPool>::GetInstance())
    ,m_enemyAttackPool(Singleton<EnemyAttackPool>::GetInstance())
    ,m_timer(new Time())
{
    m_seriousDegree = 1.1f;
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

void EnemyManager::CallEnemy()
{
    //�[���͐؂�̂�
    float CallTime = DEFAULT_CALL_TIME - (SERIOUS_COEFFICIENT * m_seriousDegree);
    m_timer->SetTimer(CallTime);

    if (m_timer->CheakTime())
    {
        int i=0;
        //  �񋓌^EnemyAttackOrbitType�̃C�e���[�^���쐬
        typedef EnumIterator<EnemyType, EnemyType::LesserEnemy, EnemyType::StraightShotEnemy> typeItr;
        //  �^�C�v���ƂɃG�l�~�[�U���N���X���v�[���ɓo�^
        for (auto itr : typeItr())
        {
            i++;
        }


        int random=rand() % i;
        XMFLOAT3 position = RandomPositionSelect();
        //�啨�̓G�𔭐�
        EnemyType enemytype = (EnemyType)random;
        AddEnemy(enemytype,1, position);
        
        //�G���G���Փx���������Ĕ���������
        int CreateLesser = 10 + (10 * m_seriousDegree);

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

const DirectX::XMFLOAT3 EnemyManager::RandomPositionSelect()
{
    int positionIndex = rand() % 4;
    return ADVENT_POSITION[positionIndex];
    
    


}
