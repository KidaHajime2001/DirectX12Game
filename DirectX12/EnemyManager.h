#pragma once
#include <DirectXMath.h>
#include <list>
enum class EnemyType;
class EnemyManager
{
public:
	//コンストラクタ
	EnemyManager();

	//デストラクタ
	~EnemyManager();

	//更新
	void Update(const DirectX::XMFLOAT3& _targetPos);
	
	//描画
	void Draw();

	//90秒時点からの出現イベント
	void Advent90s();
	//60秒時点からの出現イベント
	void Advent60s();
	//30秒時点からの出現イベント
	void Advent30s();

	//Enemyの撃破数をXMFLOAT2にまとめる（LESSER,HIGHER）
	const DirectX::XMFLOAT2 GetEnemyDefeatScore() { return DirectX::XMFLOAT2(m_lesserNumScore, m_higherNumScore); };

	//ゲームレベルを受け取る
	void SetGameLevel(int _level);
private:
	//敵撃破情報を加算
	void AddScore(const EnemyType _enemyType);
	//エネミーを出す
	void CallEnemy();

	/// <summary>
	/// 敵を追加する
	/// CallEnemy内などで呼ばれ引数で指定された場所に敵を出現させる
	/// </summary>
	/// <param name="_type">呼び出す敵のタイプ</param>
	/// <param name="_num">呼び出す数</param>
	/// <param name="_adventPosition">呼び出すポジション</param>
	void AddEnemy(const EnemyType& _type, const int& _num,const DirectX::XMFLOAT3& _adventPosition);
	
	//敵プール
	class EnemyPool& m_enemyPool;

	//敵の攻撃プール
	class EnemyAttackPool& m_enemyAttackPool;

	//今動いている敵のリスト
	std::list<class EnemyBase*> m_nowAliveEnemyList;
	//動いているリストから除去する敵のリスト
	std::list<class EnemyBase*> m_deleteList;

	//時間を図るクラス
	class Time* m_timer;
	
	//難易度
	float m_seriousDegree = 1.0f;
	//難易度を考慮しない敵出現の時間
	const float DEFAULT_CALL_TIME = 10.0f;
	//難易度で敵出現を調整する際の係数
	const float SERIOUS_COEFFICIENT = 4.0f;

	//出現するポイント
	DirectX::XMFLOAT3 ADVENT_POSITION[4]=
	{
		DirectX::XMFLOAT3(  0,  0,-120),
		DirectX::XMFLOAT3(  0,  0, 120),
		DirectX::XMFLOAT3(-120,  0,  0),
		DirectX::XMFLOAT3( 120,  0,  0),
	};
	//イベントで出現するポイント
	DirectX::XMFLOAT3 ADVENT_EVENT_POSITION[4] =
	{
		DirectX::XMFLOAT3(100,  0,100),
		DirectX::XMFLOAT3(100,  0, -100),
		DirectX::XMFLOAT3(-100,  0, 100),
		DirectX::XMFLOAT3(-100,  0,  -100),
	};
	
	//雑魚の撃破数
	int m_lesserNumScore=0;
	//雑魚以外の撃破数
	int m_higherNumScore=0;


};

