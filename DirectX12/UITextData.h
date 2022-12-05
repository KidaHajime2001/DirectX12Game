#pragma once
#include <DirectXMath.h>
#include"SpriteFont.h"
//UIのデータをまとめたヘッダー

//フォントのDefaultサイズ
const int TEXT_SIZE_WIDTH = 24;//横
const int TEXT_SIZE_HEIGHT = 36;//縦

//選択時のUIテキストの色
const DirectX::XMVECTORF32 SELECT_COLOR = DirectX::Colors::GreenYellow;//黄緑
const DirectX::XMVECTORF32 NON_SELECT_COLOR = DirectX::Colors::Green;//緑
//ここはα値で見えなくするのが正解？
//const DirectX::XMVECTORF32 INVISIVLE_COLOR= DirectX::Colors::Black;

//選択時に点滅する下限と上限
const float UI_TEXT_ALPHA_MIN=0.3f;
const float UI_TEXT_ALPHA_MAX=1.0f;
