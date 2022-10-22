#pragma once
#include "EnemyBase.h"
class LesserEnemy :
    public EnemyBase
{
public:
    LesserEnemy(CollisionTag _tag, bool m_alive);
    ~LesserEnemy();
    //������
    void Init();
    void Update(const DirectX::XMFLOAT3 _targetPos);
    /// <summary>
    /// �ŗL�̓����A
    /// </summary>
    /// <param name="otherCollision"></param>
    void CollisionOriginal(class Collision* otherCollision);
private:
    void WaitUpdate(const DirectX::XMFLOAT3 _targetPos);
	void AttackUpdate(const DirectX::XMFLOAT3 _targetPos);
	void MoveUpdate(const DirectX::XMFLOAT3 _targetPos);

    ////�e��łN���X
    //class EnemyShotDirector* m_enemyShotDirector;

    //���Ԃ�}��N���X
    class Time* m_timer;
};