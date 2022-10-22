#pragma once
#include"DirectXTex.h"
#define PI 3.141592
namespace XMF3Math
{
	/// <summary>
	/// ベクトルの足し算
	/// </summary>
	/// <param name="a">足したいベクトル1</param>
	/// <param name="b">足したいベクトル2</param>
	/// <returns>計算後のベクトル </returns>
	const DirectX::XMFLOAT3 AddXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b);
	
	/// <summary>
	/// ベクトルの引き算
	/// </summary>
	/// <param name="a">引きたいベクトル1</param>
	/// <param name="b">引きたいベクトル2</param>
	/// <returns>計算後のベクトル </returns>
	const DirectX::XMFLOAT3 SubXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b);

	/// <summary>
	/// ベクトルへの掛け算
	/// </summary>
	/// <param name="a">掛け算のもととなるベクトル</param>
	/// <param name="_scalar">ベクトルに掛けたい係数</param>
	/// <returns>a * _scalarのベクトル</returns>
	const DirectX::XMFLOAT3 ScalarXMFLOAT3(const DirectX::XMFLOAT3& a,const float& _scalar);
	
	/// <summary>
	/// ベクトルへの割り算
	/// </summary>
	/// <param name="a">割り算のもととなる</param>
	/// <param name="_division">ベクトルを割りたい係数</param>
	/// <returns>a * _divisionのベクトル</returns>
	const DirectX::XMFLOAT3 DivisionXMFLOAT3(const DirectX::XMFLOAT3& a, const float& _division);
	
	/// <summary>
	/// 外積の計算
	/// </summary>
	/// <param name="a">外積を出したいベクトル1</param>
	/// <param name="b">外積を出したいベクトル2</param>
	/// <returns>計算して出した外積</returns>
	const DirectX::XMFLOAT3 CrossXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b );

	/// <summary>
	/// ベクトルの長さ二乗を計算
	/// </summary>
	/// <param name="a">長さを二乗したいベクトル</param>
	/// <returns>計算後の二乗されたベクトル</returns>
	const float LengthSquaredXMFLOAT3(const DirectX::XMFLOAT3& a);
	
	/// <summary>
	///　ベクトルの長さを計算
	/// </summary>
	/// <param name="a">長さを出したいベクトル</param>
	/// <returns>引数のベクトルの長さ</returns>
	const float LengthXMFLOAT3(const DirectX::XMFLOAT3& a);

	/// <summary>
	/// ベクトルの正規化
	/// </summary>
	/// <param name="a">正規化したいベクトル</param>
	/// <returns>単位ベクトル</returns>
	const DirectX::XMFLOAT3 NormalizeXMFLOAT3(const DirectX::XMFLOAT3& a);
	
	/// <summary>
	/// ベクトルの大きさを設定する（正規化した後、掛け算で大きさを変える）
	/// </summary>
	/// <param name="a">大きさを変えたいベクトル</param>
	/// <param name="_mag">ベクトルの大きさ</param>
	/// <returns>大きさを変えたベクトル</returns>
	const DirectX::XMFLOAT3 SetMagnitude(const DirectX::XMFLOAT3& a ,const float& _mag);
	
	/// <summary>
	/// Y軸でベクトルを回転させる
	/// </summary>
	/// <param name="a">回転させるベクトル</param>
	/// <param name="_degree">回転させる角度（実角度degree）</param>
	/// <returns>回転させたベクトル</returns>
	const DirectX::XMFLOAT3 RotateVec2_XZ(const DirectX::XMFLOAT3& a,const float& _degree);
	//180->3.14
	const float DegreeForRadian(const float& degree);

	//3.14->180
	const float RadianForDegree(const float& radian);
}