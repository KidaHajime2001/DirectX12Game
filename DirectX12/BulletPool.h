#pragma once
#include<vector>
//弾をいちいち生成しないよう作り置きしたものを再利用する
class BulletPool
{
public:
	//コンストラクタ、デストラクタ
	BulletPool();
	~BulletPool();

	/// <summary>
	/// 指定数オブジェクトを生成
	/// </summary>
	/// <param name="_size">オブジェクトプールの大きさ</param>
	void CreatePool(int _size);
	
	//オブジェクトプールの削除
	void DestroyPool();
	/// <summary>
	/// 未使用の弾を返す
	/// </summary>
	class Bullet* GetUnUsedBullet();
	//更新
	void Update();
	//描画
	void Draw();
private:
	//オブジェクトの数
	int m_poolSize;
	//弾のオブジェクトプール
	std::vector<Bullet*> m_bulletPool;
};
