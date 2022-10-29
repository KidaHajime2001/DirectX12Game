#include "CollisionManager.h"
#include"EnumItr.h"
#include"CollisionTag.h"
using namespace std;
CollisionManager::CollisionManager()
{
	collidePairs onepair = { CollisionTag::Player,CollisionTag::Enemy };
	pairsVec.push_back(onepair);
	 onepair = { CollisionTag::PlayerBullet,CollisionTag::Enemy };
	pairsVec.push_back(onepair);
	onepair = { CollisionTag::Enemy,CollisionTag::Enemy };
	pairsVec.push_back(onepair);
	onepair = { CollisionTag::Player,CollisionTag::EnemyBullet };
	pairsVec.push_back(onepair);
}

CollisionManager::~CollisionManager()
{
	pairsVec.clear();
	mColliders.clear();
}

void CollisionManager::AddCollision(Collision* collision)
{
	CollisionTag tag = collision->GetTag();
	mColliders[tag].emplace_back(collision);
}

void CollisionManager::RemoveCollision(Collision* collision)
{
	CollisionTag tag = collision->GetTag();
	vector<Collision*>::iterator iter = find(mColliders[tag].begin(), mColliders[tag].end(), collision);
	if (iter != mColliders[tag].end())
	{
		mColliders[tag].erase(iter);
		return;
	}

}

void CollisionManager::Update()
{
	//  列挙型EnemyAttackOrbitTypeのイテレータを作成
	typedef EnumIterator<CollisionTag, CollisionTag::Player, CollisionTag::End> typeItr;
	for (auto itr : typeItr())
	{
		for (auto collision : mColliders[itr])
		{
			collision->Update();
		}
	}
	CollisionUpdate();
}

void CollisionManager::CollisionUpdate()
{
	
	bool isHit = false;

	for (auto onePair : pairsVec)
	{
		for (auto obj : mColliders[onePair.pair1])
		{
			for (auto reactionObj : mColliders[onePair.pair2])
			{
				
				if (obj->Cheak(reactionObj)&& obj!= reactionObj)
				{
					CollisionTag u = obj->GetTag();
					CollisionTag o = obj->GetTag();
					reactionObj->Hit(obj);
					obj->Hit(reactionObj);
					isHit = true;
				}
			}
		}

	}
	
}

void CollisionManager::DestroyAll()
{
	//  列挙型EnemyAttackOrbitTypeのイテレータを作成
	typedef EnumIterator<CollisionTag, CollisionTag::Player, CollisionTag::EnemyBullet> typeItr;
	for (auto itr : typeItr())
	{
		for (auto collision :mColliders[itr])
		{
			if (collision)
			{
				delete collision;
			}
		}
		mColliders[itr].clear();
		mColliders[itr].shrink_to_fit();
	}

	
}
