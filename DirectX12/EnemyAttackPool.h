#pragma once
#include <iostream>
#include <vector>
#include <DirectXMath.h>
#include<unordered_map>
enum class EnemyAttackType;
//シングルトンクラス
class EnemyAttackPool
{
public:
	EnemyAttackPool();
	~EnemyAttackPool();
	//弾の更新
	void Update(const DirectX::XMFLOAT3 _targetPos);
	//弾の描画
	void Draw();
	/// <summary>
	/// 未使用の敵攻撃クラスを返す
	/// </summary>
	class EnemyAttackBase* GetUnUsedEnemyAttack(const EnemyAttackType _type);

	//弾のオブジェクトプール作成
	void CreateAll();
	//オブジェクトプール削除
	void DestroyAll();
private:
	//タイプ別更新
	void UpdateEnemyAttack(const EnemyAttackType _type,const DirectX::XMFLOAT3 _targetPos);
	//タイプ別描画
	void DrawEnemyAttack(const EnemyAttackType _type);

	//オブジェクトプール
	std::vector<class EnemyAttackBase*> m_StraightPool;
	//オブジェクトプール
	std::vector<class EnemyAttackBase*> m_HormingPool;
	//タイプとオブジェクトプールを紐づけたマップ
	std::unordered_map<EnemyAttackType, std::vector<class EnemyAttackBase*>> m_poolMap;
};

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    