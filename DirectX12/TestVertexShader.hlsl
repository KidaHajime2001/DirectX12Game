#include"TestHeader.hlsli"
//���_�V�F�[�_�[

Output BasicVS( float4 pos : POSITION,float2 uv:TEXCOORD )
{
	Output output;
	output.svpos = pos;
	output.uv = uv;
	return output;
}