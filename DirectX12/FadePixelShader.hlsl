#include"OutPut.hlsli"
Texture2D<float4> tex:register(t0);//0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp:register(s0);//0�ԃX���b�g�ɐݒ肳�ꂽ�T���v��
cbuffer cbuff0 : register(b0) {
    float2 wipeDirection;  //���C�v�̕���
    float wipeSize;        //���C�v�T�C�Y
    float2 Rect;
};

//�s�N�Z���V�F�[�_
float4 BasicPS(BasicType input) : SV_TARGET{
     float4 color = tex.Sample(smp, input.uv);

     ////�s�N�Z�����W�����C�v�����Ɏˉe����

    /* float t = dot(wipeDirection, input.svpos.xy);
     clip(t - wipeSize);*/

     float2 posFromCenter = input.svpos.xy-float2(1920/2, 1080/2);
     clip(length(posFromCenter)-wipeSize);
     return color;
}