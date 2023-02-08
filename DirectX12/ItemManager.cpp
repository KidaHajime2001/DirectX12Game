#include"ItemManager.h"

#include"ItemPool.h"
#include"ItemBase.h"
#include"EnumItr.h"
ItemManager::ItemManager()
    :m_itemPool(Singleton<ItemPool>::GetInstance())
{
    m_itemPool.Create();
}

ItemManager::~ItemManager()
{
    m_itemPool.Destroy();

}

void ItemManager::Update()
{
    typedef EnumIterator<ItemTag, ItemTag::Energy, ItemTag::ReinforceAddtoShot> typeItr;

    for (auto itr : typeItr())
    {
        //���ݐ�������Ă���A�C�e���̐�������𒴂��Ă���ꍇ
        if (m_nowAliveItemList[itr].size() > DROP_MAX)
        {
            //����𒴂��Ă����
            int overSize = m_nowAliveItemList[itr].size() - DROP_MAX;

            //�J�E���g�p
            int nowItrNum = 0;

            //�擪���珇�i�o�^���j�ɏ����t���O��ݒ�
            for (auto item : m_nowAliveItemList[itr])
            {
                item->OverAlive();
                nowItrNum++;
                if (overSize == nowItrNum)
                {
                    break;
                }
            }
        }
    }
   
    for (auto itr : typeItr())
    {
        for (auto item : m_nowAliveItemList[itr])
        {
            if (!item->IsAlive())
            {
                m_deleteItemList[itr].emplace_back(item);
            }
        }
        for (auto item : m_deleteItemList[itr])
        {
            m_nowAliveItemList[itr].remove(item);
        }
    }

    m_deleteItemList.clear();
    
}

void ItemManager::Draw()
{
    typedef EnumIterator<ItemTag, ItemTag::Energy, ItemTag::ReinforceAddtoShot> typeItr;
    for (auto itr : typeItr())
    {
        //�������Ă���G�`��
        for (auto item : m_nowAliveItemList[itr])
        {
            item->Draw();
        }
    }
    
}

void ItemManager::CreateDropItem(EnemyType _type, DirectX::XMFLOAT3 _position)
{

    ItemBase* item{};
    if (_type == EnemyType::LesserEnemy)
    {

        item = m_itemPool.GetUnUsedItem(ItemTag::Energy);
    }
    else  if (rand() % DROP_PROBABILITY == 0)
    {
        if (rand()%2==0)
        {
            item = m_itemPool.GetUnUsedItem(ItemTag::ReinforceAddtoShot);
       }
        else
        {
            item = m_itemPool.GetUnUsedItem(ItemTag::ReinforceShotInterval);
        }
        
        
    }
    if (!item)
    {
        return;
    }
    item->Init(_position);
    m_nowAliveItemList[item->GetItemTag()].emplace_back(item);
    
}
