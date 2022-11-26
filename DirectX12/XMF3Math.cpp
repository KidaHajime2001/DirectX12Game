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

const DirectX::XMFLOAT3 XMF3Math::ScalarXMFLOAT3(const DirectX::XMFLOAT3& a, const float& _scalar)
{
	return DirectX::XMFLOAT3(a.x*_scalar, a.y * _scalar, a.z * _scalar);
}

const DirectX::XMFLOAT3 XMF3Math::DivisionXMFLOAT3(const DirectX::XMFLOAT3& a, const float& _division)
{
	return DirectX::XMFLOAT3(a.x /_division, a.y / _division, a.z / _division);;
}

const DirectX::XMFLOAT3 XMF3Math::CrossXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b)
{
	DirectX::XMFLOAT3 tmp;
	tmp.x = a.y * b.z - a.z * b.y;
	tmp.y = a.z * b.x - a.x * b.z;
	tmp.z = a.x * b.y - a.y * b.x;
	return tmp;
}

const float XMF3Math::LengthSquaredXMFLOAT3(const DirectX::XMFLOAT3& a)
{
	return(a.x * a.x + a.y * a.y + a.z * a.z);

}

const float XMF3Math::LengthXMFLOAT3(const DirectX::XMFLOAT3& a)
{
	return (sqrt(LengthSquaredXMFLOAT3(a)));
}

const DirectX::XMFLOAT3 XMF3Math::NormalizeXMFLOAT3(const DirectX::XMFLOAT3& a)
{
	float length = LengthXMFLOAT3(a);
	DirectX::XMFLOAT3 tmp;
	tmp.x = a.x /length;
	tmp.y = a.y /length;
	tmp.z = a.z /length;

	return tmp;
}

const DirectX::XMFLOAT3 XMF3Math::SetMagnitude(const DirectX::XMFLOAT3& _vec, const float& _mag)
{
	
	auto _normalvec = XMF3Math::NormalizeXMFLOAT3(_vec);
	_normalvec = ScalarXMFLOAT3(_normalvec,_mag);
	return _normalvec;
}

const DirectX::XMFLOAT3 XMF3Math::RotateVec2_XZ(const DirectX::XMFLOAT3& a, const float& _degree)
{
	float radian = DegreeForRadian(_degree);
	DirectX::XMFLOAT3 vec= DirectX::XMFLOAT3(0,0,0);
	vec.x = a.x * cos(radian) - a.z * sin(radian);
	vec.z = a.x * sin(radian) + a.z * cos(radian);
	return vec;
}

const float XMF3Math::DegreeForRadian(const float& degree)
{
	return degree * (PI/180);
}

const float XMF3Math::RadianForDegree(const float& radian)
{
	return radian * (180 / PI);
}
