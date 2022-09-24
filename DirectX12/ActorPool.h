#pragma once
#include"Actor.h"
#include<vector>
#include"ActorTag.h"
#include <unordered_map>
class Pool
{
public:
	//�R���X�g���N�^
	Pool();
	//�f�X�g���N�^
	~Pool();
	//_size���@����
	void Create(int _size, ActorTag _actorTag);
	//
	void AddCollisionManager(class CollisionManager* _mng);
	//�폜
	void Destroy();
	//�S�G�l�~�[�X�V
	void Update();
	//�S�G�l�~�[�`��
	void Draw();
	//�g���Ă��Ȃ��G�l�~�[��Ԃ�
	Actor* GetUnUsedActor();
	//���g���Ă���G�l�~�[�J�E���g
	int NowAliveCount();
private:
	//�G�l�~�[��
	int m_PoolSize;
	struct PoolState
	{
		int poolSize = 0;
		std::vector<Actor*> pool;
	};

	//Vector���܂Ƃ߂���
	std::vector<PoolState> m_poolVec;
	//�G�l�~�[�v�[��
	PoolState m_enemypool;
};

