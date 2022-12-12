#include"OutPut.hlsli"
Texture2D<float4> tex:register(t0);//0番スロットに設定されたテクスチャ
SamplerState smp:register(s0);//0番スロットに設定されたサンプラ
//変換をまとめた構造体
cbuffer cbuff0 : register(b0) {
	float2 wipeDirection;  //ワイプの方向
	float wipeSize;        //ワイプサイズ
};

//頂点シェーダ
BasicType BasicVS(float4 pos : POSITION, float2 uv : TEXCOORD) {
	BasicType output;//ピクセルシェーダへ渡す値
	output.svpos = pos;
	output.uv = uv;
	return output;
}
