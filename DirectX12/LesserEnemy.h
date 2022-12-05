#pragma once
#include "EnemyBase.h"

//射撃を行わない雑魚敵クラス
class LesserEnemy :
    public EnemyBase
{
public:
    //コンストラクタ
    LesserEnemy(CollisionTag _tag, bool m_alive);
    //デストラクタ
    ~LesserEnemy();
    //初期化
    void Init();
    //更新
    void Update(const DirectX::XMFLOAT3 _targetPos);

   
private:
    /// <summary>
    /// 簡易AIの待機行動
    /// </summary>
    /// <param name="_targetPos">
    /// ターゲット（プレイヤー）の位置
    /// </param>
    void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);
    /// <summary>
    /// 簡易AIの移動行動
    /// </summary>
    /// <param name="_targetPos">
    /// ターゲット（プレイヤー）の位置
    /// </param>
	void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);
   
    /// <summary>
   /// 固有の動き、
   /// </summary>
   /// <param name="otherCollision">
   ///　接触した他当たり判定情報
   /// </param>
    void CollisionOriginal(class Collision* otherCollision);

    //時間を図るクラス
    class Time* m_timer;
};