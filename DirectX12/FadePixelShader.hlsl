#include"OutPut.hlsli"
Texture2D<float4> tex:register(t0);//0番スロットに設定されたテクスチャ
SamplerState smp:register(s0);//0番スロットに設定されたサンプラ
cbuffer cbuff0 : register(b0) {
    float2 wipeDirection;  //ワイプの方向
    float wipeSize;        //ワイプサイズ
    float2 Rect;
};

//ピクセルシェーダ
float4 BasicPS(BasicType input) : SV_TARGET{
     float4 color = tex.Sample(smp, input.uv);

     ////ピクセル座標をワイプ方向に射影する

    /* float t = dot(wipeDirection, input.svpos.xy);
     clip(t - wipeSize);*/

     float2 posFromCenter = input.svpos.xy-float2(1920/2, 1080/2);
     clip(length(posFromCenter)-wipeSize);
     return color;
}