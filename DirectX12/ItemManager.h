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
	/// アイテム生成
	/// </summary>
	/// <param name="_type">
	/// 　エネミーのタイプ　
	/// 入力されたタイプ次第でドロップアイテムが変わる
	/// </param>
	/// <param name="_position">
	/// 生成する位置
	/// </param>
	void CreateDropItem(EnemyType _type,DirectX::XMFLOAT3 _position);
private:
	class ItemPool& m_itemPool;

	const int DROP_MAX=100;
	const int DROP_PROBABILITY = 10; // 1/DROP_PROBABILITY = ドロップ率
	//今動いている敵のリスト
	std::unordered_map<ItemTag, std::list<class ItemBase*>> m_nowAliveItemList;
	//動いているリストから除去する敵のリスト
	std::unordered_map<ItemTag, std::list<class ItemBase*>> m_deleteItemList;
};