#pragma once
#include <list>
#include"EnemyType.h"
#include"DirectXHelpers.h"
#include"ItemTag.h"
#include<unordered_map>
class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	void Update();
	void Draw();

	/// <summary>
	/// �A�C�e������
	/// </summary>
	/// <param name="_type">
	/// �@�G�l�~�[�̃^�C�v�@
	/// ���͂��ꂽ�^�C�v����Ńh���b�v�A�C�e�����ς��
	/// </param>
	/// <param name="_position">
	/// ��������ʒu
	/// </param>
	void CreateDropItem(EnemyType _type,DirectX::XMFLOAT3 _position);
private:
	class ItemPool& m_itemPool;

	const int DROP_MAX=100;
	const int DROP_PROBABILITY = 10; // 1/DROP_PROBABILITY = �h���b�v��
	//�������Ă���G�̃��X�g
	std::unordered_map<ItemTag, std::list<class ItemBase*>> m_nowAliveItemList;
	//�����Ă��郊�X�g���珜������G�̃��X�g
	std::unordered_map<ItemTag, std::list<class ItemBase*>> m_deleteItemList;
};