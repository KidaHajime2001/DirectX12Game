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
    //��Փx������
    m_seriousDegree = 1.0f;
    //�G�l�~�[�v�[���̒��g���쐬
    m_enemyPool.CreateAll();
}

EnemyManager::~EnemyManager()
{
    //�G�l�~�[�v�[���̒��g���폜
    m_enemyPool.DestroyAll();
    delete m_itemManager;
    delete m_timer;
}

void EnemyManager::Update(const DirectX::XMFLOAT3& _targetPos)
{
    //�G���Ăяo��
    CallEnemy();

    //���ݐ����Ă��郊�X�g�ɓ����Ă���G�̍X�V
    for (auto enemy : m_nowAliveEnemyList)
    {
        enemy->Update(_targetPos);
        //�����t���O��OFF�ɂȂ�����
        if (!enemy->IsAlive())
        {
            m_itemManager->CreateDropItem(enemy->GetEnemyType(),enemy->GetPosition());
            //�X�R�A�p�̐��l���Z
            AddScore(enemy->GetEnemyType());

            //���ݓ����Ă��郊�X�g����폜���邽�߂̃��X�g��
            m_deleteList.emplace_back(enemy);
        }

    }
    m_itemManager->Update();

    //���݂̃��X�g�������
    for (auto enemy : m_deleteList)
    {
        m_nowAliveEnemyList.remove(enemy);
    }
    m_deleteList.clear();
    //�e�̍X�V
    m_enemyAttackPool.Update(_targetPos);
}

void EnemyManager::Draw()
{
    m_itemManager->Draw();
}

void EnemyManager::LineDraw()
{
    //�������Ă���G�`��
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
    ////�^�C�v�̐����J�E���g
    //for (auto itr : typeItr())
    //{
    //    i++;
    //}
    ////�G�l�~�[�̃^�C�v�����肵����
    ////�G�������O���Čv�Z
    //int random = (rand() % (i - 1))+1;
    //EnemyType enemytype = (EnemyType)random;
    ////�����_���|�W�V�������쐬
    //int positionIndex = rand() % 4;
    //XMFLOAT3 position = ADVENT_EVENT_POSITION[positionIndex];
    ////�Ăяo��
    //AddEnemy(enemytype, 1, position);


   /* AddEnemy(EnemyType::SnakeEnemy, 1, XMFLOAT3(100, 0, -100));*/
}

void EnemyManager::Advent60s()
{
    AddEnemy(EnemyType::LesserEnemy, 50, XMFLOAT3(100, 0, -100));

    AddEnemy(EnemyType::LesserEnemy, 50, XMFLOAT3(-100, 0, 100));
    ////�񂩏��������̓G���o��
    //AddEnemy(EnemyType::StraightShotEnemy, 1, XMFLOAT3(100,0,100));
    //AddEnemy(EnemyType::StraightShotEnemy, 1, XMFLOAT3(-100, 0, -100));
}

void EnemyManager::Advent30s()
{
    //�񂩏��������̓G���o��
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
    //�[���͐؂�̂�
    float CallTime = DEFAULT_CALL_TIME - (SERIOUS_COEFFICIENT * m_seriousDegree);
    m_timer->SetTimer(CallTime);

    if (m_timer->CheakTime())
    {
        int i=0;
        //  �񋓌^EnemyAttackOrbitType�̃C�e���[�^���쐬
        typedef EnumIterator<EnemyType, EnemyType::LesserEnemy, EnemyType::StraightShotEnemy> typeItr;
        //�^�C�v���J�E���g
        for (auto itr : typeItr())
        {
            i++;
        }

        //�^�C�v�������_���ɑI��
        int random=rand() % i;
        //�����_���Ƀ|�W�V������I��
        int positionIndex = rand() % 4;
        XMFLOAT3 position = ADVENT_POSITION[positionIndex];

        //�o���|�C���g���U�炷
        if(positionIndex==1|| positionIndex == 0)
        {
            position.x = rand() % 200 - 100;
        }
        if (positionIndex == 2 || positionIndex == 3)
        {
            position.z = rand() % 200 - 100;
        }
        
        //�G�𔭐�
        EnemyType enemytype = (EnemyType)random;

        //�G���G���Փx���������Ĕ���������
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
        //�G�l�~�[�v�[������擾�ł��Ă���ꍇ
        if (enemy)
        {
            //�o���ɓ������Ă̏�����
            m_nowAliveEnemyList.emplace_back(enemy);
            m_nowAliveEnemyList.back()->Init();
            m_nowAliveEnemyList.back()->Advent(_adventPosition);
        }
       
    }
}
