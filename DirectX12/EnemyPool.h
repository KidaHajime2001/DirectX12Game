#pragma once

#include<vector>
#include<unordered_map>
enum class EnemyType;
class EnemyPool
{
public:
	EnemyPool();
	~EnemyPool();
	/// <summary>
	///　プールから未使用のエネミークラスをゲットする
	/// </summary>
	class EnemyBase* UnUsedEnemyAdvent(const EnemyType _type);

	/// <summary>
	/// コリジョンマネージャーにエネミープールの当たり判定を登録する
	/// </summary>
	/// <param name="_mng">
	/// コリジョンマネージャー
	/// </param>
	void AddCollision( class CollisionManager* _mng);

	/// <summary>
	/// コリジョンマネージャーのエネミープールの当たり判定を削除する
	/// </summary>
	/// <param name="_mng">
	/// コリジョンマネージャー
	/// </param>
	void DeleteCollision(class CollisionManager* _mng);

	/// <summary>
	/// プール作成
	/// </summary>
	void CreateAll();

	/// <summary>
	/// プールを削除
	/// </summary>
	void DestroyAll();
private:
	/// <summary>
	/// 指定のエネミークラスを作成
	/// </summary>
	/// <param name="_type">
	/// 指定するタイプ
	/// </param>
	void Create(const EnemyType _type);

	/// <summary>
	/// プール本体
	/// </summary>
	std::unordered_map<EnemyType, std::vector<EnemyBase*>> m_enemyPool;

	/// <summary>
	///　上級ボスタイプごとの最大数
	/// </summary>
	const int HIGHER_ENEMY_MAX = 10;
	
	/// <summary>
	/// 下位エネミーの最大数
	/// </summary>
	const int LESSER_ENEMY_MAX = 300;
};
