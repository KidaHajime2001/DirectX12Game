#include"OutPut.hlsli"
Texture2D<float4> tex:register(t0);//0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp:register(s0);//0�ԃX���b�g�ɐݒ肳�ꂽ�T���v��
//�ϊ����܂Ƃ߂��\����
cbuffer cbuff0 : register(b0) {
	float2 wipeDirection;  //���C�v�̕���
	float wipeSize;        //���C�v�T�C�Y
};

//���_�V�F�[�_
BasicType BasicVS(float4 pos : POSITION, float2 uv : TEXCOORD) {
	BasicType output;//�s�N�Z���V�F�[�_�֓n���l
	output.svpos = pos;
	output.uv = uv;
	return output;
}
