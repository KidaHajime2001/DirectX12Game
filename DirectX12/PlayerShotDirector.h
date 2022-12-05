#pragma once
#include<DirectXMath.h>
//プレイヤーの弾を撃つクラス
class PlayerShotDirector
{
public:
	//コンストラクタ、デストラクタ
	PlayerShotDirector();
	~PlayerShotDirector();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="_isShot">プレイヤーの弾を撃つフラグがたっているか</param>
	/// <param name="_pos">弾発射のためのポジション</param>
	/// <param name="_direction">弾を撃つ向き</param>
	/// <param name="_speed">弾の速度</param>
	void Update(const bool& _isShot,const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT3& _direction,const float& _speed);

	//描画
	void Draw();
private:
	//オブジェクトプール
	class BulletPool* m_bulletPool;
	const float FIRE_POSITION = 5.0f;
};
