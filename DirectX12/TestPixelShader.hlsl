#include"TestHeader.hlsli"
//ピクセルシェーダー

float4 BasicPS(Output input) : SV_TARGET
{
    float4 color = tex.Sample(smp, input.uv);

    // step-7 ピクセルカラーをモノクロ化する
    float Y = 0.299f * color.r + 0.587f * color.b + 0.114f * color.b;
    color.r = Y;
    color.g = Y;
    color.b = Y;

    return color;
}