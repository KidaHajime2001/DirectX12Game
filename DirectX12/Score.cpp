#include "Score.h"
#include"Singleton.h"
#include"SpriteDrawer.h"
#include"SpriteType.h"
#include"StringDrawer.h"
#include"Controller.h"

ScoreUI::ScoreUI()
	:m_drawer(Singleton<StringDrawer>::GetInstance())
	,m_sprite(Singleton<SpriteDrawer>::GetInstance())
    ,m_controller(Singleton<Controller>::GetInstance())
    ,m_pos(XMFLOAT2(0,0))
{
}

ScoreUI::~ScoreUI()
{
}

void ScoreUI::DrawString()
{
    m_drawer.DrawStringBlackAndWhiteForFewNumber(m_pos.x,XMFLOAT2(0,800),0.5f);
    m_drawer.DrawStringBlackAndWhiteForFewNumber(m_pos.y, XMFLOAT2(0, 850), 0.5f);
}

void ScoreUI::DrawSprite()
{
	
    //コントローラー未接続用移動処理
	//  背景描画
	
}

void ScoreUI::Update()
{

}
