#pragma once
#include<DirectXMath.h>
#include "EnemyAttackType.h"
#include<iostream>
#include<list>
//エネミーの攻撃クラス
class EnemyShotDirector
{
public:

	EnemyShotDirector();
	~EnemyShotDirector();
	/// <summary>
	/// エネミークラスの攻撃
	/// </summary>
	/// <param name="_type">攻撃のタイプ</param>
	/// <param name="_pos">攻撃位置</param>
	/// <param name="_targetPos">攻撃の狙い先</param>
	/// <param name="_aimVec">
	/// 初期ベクトル
	/// （指定をすることで攻撃の自由度を上げる目的がある：あえて狙いをはずすなど）
	/// </param>
	void Shot(const EnemyAttackType _type, const DirectX::XMFLOAT3 _pos,const DirectX::XMFLOAT3 _targetPos,DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0,0,0));

private:

	/// <summary>
	/// ホーミング弾を撃つ
	/// </summary>
	/// <param name="_pos">発射位置</param>
	/// <param name="_targetPos">狙う敵</param>
	/// <param name="_aimVec">初期ベクトル</param>
	void HormingShot( const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));
	/// <summary>
	/// まっすぐ弾を撃つ
	/// </summary>
	/// <param name="_pos">発射位置</param>
	/// <param name="_targetPos">狙う敵</param>
	/// <param name="_aimVec">初期ベクトル</param>
	void StraightShot(const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));

	/// <summary>
	/// 複数方向にまっすぐな弾を撃つ
	/// </summary>
	/// <param name="_pos">発射位置</param>
	/// <param name="_targetPos">狙う敵</param>
	/// <param name="_aimVec">初期ベクトル</param>
	void SpreadShot(const DirectX::XMFLOAT3 _pos, const DirectX::XMFLOAT3 _targetPos, DirectX::XMFLOAT3 _aimVec = DirectX::XMFLOAT3(0, 0, 0));

	/// <summary>
	/// 生きている攻撃クラスをまとめるリスト
	/// </summary>
	std::list<class EnemyAttackBase*> m_attackList;

	/// <summary>
	/// 時限などで削除する攻撃クラスをまとめるリスト
	/// </summary>
	std::list<class EnemyAttackBase*> m_deleteList;

	/// <summary>
	/// エネミーの攻撃プール
	/// </summary>
	class EnemyAttackPool& m_enemyAttackPool;

	/// <summary>
	/// 拡散弾の数
	/// </summary>
	const int SPREAD_SHOT_NUM=3;

};

