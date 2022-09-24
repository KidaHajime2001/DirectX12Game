#pragma once
#include"DirectXTex.h"
#define PI 3.141592
namespace XMF3Math
{

	const DirectX::XMFLOAT3 AddXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b);
	
	const DirectX::XMFLOAT3 SubXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b);

	const DirectX::XMFLOAT3 ScalarXMFLOAT3(const DirectX::XMFLOAT3& a,const float scalar);
	
	const DirectX::XMFLOAT3 CrossXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b );

	const float LengthSquaredXMFLOAT3(const DirectX::XMFLOAT3 a);
	
	const float LengthXMFLOAT3(const DirectX::XMFLOAT3 a);

	const DirectX::XMFLOAT3 NormalizeXMFLOAT3(const DirectX::XMFLOAT3 a);
	
	//180->3.14
	const float DegreeForRadian(const float& degree);

	//3.14->180
	const float RadianForDegree(const float& radian);
}