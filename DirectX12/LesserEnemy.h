#pragma once
#include "EnemyBase.h"
class LesserEnemy :
    public EnemyBase
{
public:
    LesserEnemy(CollisionTag _tag, bool m_alive);
    ~LesserEnemy();
    //初期化
    void Init();
    void Update(const DirectX::XMFLOAT3 _targetPos);
    /// <summary>
    /// 固有の動き、
    /// </summary>
    /// <param name="otherCollision"></param>
    void CollisionOriginal(class Collision* otherCollision);
private:
    void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);
	void AttackUpdate(const DirectX::XMFLOAT3 _targetPos);
	void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);

    ////弾を打つクラス
    //class EnemyShotDirector* m_enemyShotDirector;

    //時間を図るクラス
    class Time* m_timer;
};