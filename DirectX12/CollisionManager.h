#pragma once
#include"CollisionTag.h"
#include"Collision.h"
#include<vector>
#include<unordered_map>
class CollisionManager
{
public:
	struct collidePairs
	{
		CollisionTag pair1;
		CollisionTag pair2;
	};
	CollisionManager();
	~CollisionManager();
	void AddCollision(Collision* collider);
	void RemoveCollision(Collision* collider);
	void Update();
	void CollisionUpdate();
	void DestroyAll();
	std::vector<collidePairs> pairsVec;//�����蔻�肪��������Actor�̃y�A�@�^�O�Œ�`
	std::unordered_map<CollisionTag, std::vector<class Collision*>> mColliders;
private:

};

