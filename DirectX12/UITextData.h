#pragma once
#include <DirectXMath.h>
#include"SpriteFont.h"
//UI�̃f�[�^���܂Ƃ߂��w�b�_�[

//�t�H���g��Default�T�C�Y
const int TEXT_SIZE_WIDTH = 24;//��
const int TEXT_SIZE_HEIGHT = 36;//�c

//�I������UI�e�L�X�g�̐F
const DirectX::XMVECTORF32 SELECT_COLOR = DirectX::Colors::GreenYellow;//����
const DirectX::XMVECTORF32 NON_SELECT_COLOR = DirectX::Colors::Green;//��
//�����̓��l�Ō����Ȃ�����̂������H
//const DirectX::XMVECTORF32 INVISIVLE_COLOR= DirectX::Colors::Black;

//�I�����ɓ_�ł��鉺���Ə��
const float UI_TEXT_ALPHA_MIN=0.3f;
const float UI_TEXT_ALPHA_MAX=1.0f;
