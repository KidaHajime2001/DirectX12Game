#pragma once
#include"DirectXTex.h"
#define PI 3.141592
namespace XMF3Math
{
	/// <summary>
	/// �x�N�g���̑����Z
	/// </summary>
	/// <param name="a">���������x�N�g��1</param>
	/// <param name="b">���������x�N�g��2</param>
	/// <returns>�v�Z��̃x�N�g�� </returns>
	const DirectX::XMFLOAT3 AddXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b);
	
	/// <summary>
	/// �x�N�g���̈����Z
	/// </summary>
	/// <param name="a">���������x�N�g��1</param>
	/// <param name="b">���������x�N�g��2</param>
	/// <returns>�v�Z��̃x�N�g�� </returns>
	const DirectX::XMFLOAT3 SubXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b);

	/// <summary>
	/// �x�N�g���ւ̊|���Z
	/// </summary>
	/// <param name="a">�|���Z�̂��ƂƂȂ�x�N�g��</param>
	/// <param name="_scalar">�x�N�g���Ɋ|�������W��</param>
	/// <returns>a * _scalar�̃x�N�g��</returns>
	const DirectX::XMFLOAT3 ScalarXMFLOAT3(const DirectX::XMFLOAT3& a,const float& _scalar);
	
	/// <summary>
	/// �x�N�g���ւ̊���Z
	/// </summary>
	/// <param name="a">����Z�̂��ƂƂȂ�</param>
	/// <param name="_division">�x�N�g�������肽���W��</param>
	/// <returns>a * _division�̃x�N�g��</returns>
	const DirectX::XMFLOAT3 DivisionXMFLOAT3(const DirectX::XMFLOAT3& a, const float& _division);
	
	/// <summary>
	/// �O�ς̌v�Z
	/// </summary>
	/// <param name="a">�O�ς��o�������x�N�g��1</param>
	/// <param name="b">�O�ς��o�������x�N�g��2</param>
	/// <returns>�v�Z���ďo�����O��</returns>
	const DirectX::XMFLOAT3 CrossXMFLOAT3(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b );

	/// <summary>
	/// �x�N�g���̒��������v�Z
	/// </summary>
	/// <param name="a">�������悵�����x�N�g��</param>
	/// <returns>�v�Z��̓�悳�ꂽ�x�N�g��</returns>
	const float LengthSquaredXMFLOAT3(const DirectX::XMFLOAT3& a);
	
	/// <summary>
	///�@�x�N�g���̒������v�Z
	/// </summary>
	/// <param name="a">�������o�������x�N�g��</param>
	/// <returns>�����̃x�N�g���̒���</returns>
	const float LengthXMFLOAT3(const DirectX::XMFLOAT3& a);

	/// <summary>
	/// �x�N�g���̐��K��
	/// </summary>
	/// <param name="a">���K���������x�N�g��</param>
	/// <returns>�P�ʃx�N�g��</returns>
	const DirectX::XMFLOAT3 NormalizeXMFLOAT3(const DirectX::XMFLOAT3& a);
	
	/// <summary>
	/// �x�N�g���̑傫����ݒ肷��i���K��������A�|���Z�ő傫����ς���j
	/// </summary>
	/// <param name="a">�傫����ς������x�N�g��</param>
	/// <param name="_mag">�x�N�g���̑傫��</param>
	/// <returns>�傫����ς����x�N�g��</returns>
	const DirectX::XMFLOAT3 SetMagnitude(const DirectX::XMFLOAT3& a ,const float& _mag);
	
	/// <summary>
	/// Y���Ńx�N�g������]������
	/// </summary>
	/// <param name="a">��]������x�N�g��</param>
	/// <param name="_degree">��]������p�x�i���p�xdegree�j</param>
	/// <returns>��]�������x�N�g��</returns>
	const DirectX::XMFLOAT3 RotateVec2_XZ(const DirectX::XMFLOAT3& a,const float& _degree);
	//180->3.14
	const float DegreeForRadian(const float& degree);

	//3.14->180
	const float RadianForDegree(const float& radian);
}