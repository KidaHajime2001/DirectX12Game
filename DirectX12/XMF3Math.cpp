#include "XMF3Math.h"
#include<math.h>
using namespace XMF3Math;
const DirectX::XMFLOAT3 XMF3Math::AddXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b)
{
	return DirectX::XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
}


const DirectX::XMFLOAT3 XMF3Math::SubXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b)
{
	return DirectX::XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
}

const DirectX::XMFLOAT3 XMF3Math::ScalarXMFLOAT3(const DirectX::XMFLOAT3& a, const float scalar)
{
	return DirectX::XMFLOAT3(a.x*scalar, a.y * scalar, a.z * scalar);
}

const DirectX::XMFLOAT3 XMF3Math::CrossXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b)
{
	DirectX::XMFLOAT3 tmp;
	tmp.x = a.y * b.z - a.z * b.y;
	tmp.y = a.z * b.x - a.x * b.z;
	tmp.z = a.x * b.y - a.y * b.x;
	return tmp;
}

const float XMF3Math::LengthSquaredXMFLOAT3(const DirectX::XMFLOAT3 a)
{
	return(a.x * a.x + a.y * a.y + a.z * a.z);

}

const float XMF3Math::LengthXMFLOAT3(const DirectX::XMFLOAT3 a)
{
	return (sqrt(LengthSquaredXMFLOAT3(a)));
}

const DirectX::XMFLOAT3 XMF3Math::NormalizeXMFLOAT3(const DirectX::XMFLOAT3 a)
{
	float length = LengthXMFLOAT3(a);
	DirectX::XMFLOAT3 tmp;
	tmp.x = a.x /length;
	tmp.y = a.y /length;
	tmp.z = a.z /length;

	return tmp;
}

const float XMF3Math::DegreeForRadian(const float& degree)
{
	return degree * (PI/180);
}

const float XMF3Math::RadianForDegree(const float& radian)
{
	return radian * (180 / PI);
}
