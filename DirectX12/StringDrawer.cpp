#include"StringDrawer.h"

#include <string>

#include "Singleton.h"
#include "D12Device.h"

StringDrawer::StringDrawer()
    :m_device(Singleton<D12Device>::GetInstance())
{

}

StringDrawer::~StringDrawer()
{
}

//  •‚¢‰e•t‚«‰©F•¶Žš‚Ì•`‰æ
void StringDrawer::DrawStringBlackAndWhite(const char* _string, const XMFLOAT2& _pos, const float _scale, const float _alpha, const float _rotation)
{
    const XMFLOAT2& origin = { 0,0 };

    XMFLOAT2 secondPos = { _pos.x - SHIFT_STRING,_pos.y - SHIFT_STRING };
    
    m_device.spriteFont->DrawString(m_device.spriteBatch, _string, _pos, GetColorWithalpha(_alpha,Colors::Black), _rotation, origin, _scale);
    m_device.spriteFont->DrawString(m_device.spriteBatch, _string, secondPos, GetColorWithalpha(_alpha, Colors::White), _rotation, origin, _scale);
}

void StringDrawer::DrawStringTitle(const char* _string, const XMFLOAT2& _pos, const float _scale, const float _alpha, const XMVECTORF32 _color, const float _rotation)
{
    const XMFLOAT2& origin = { 0,0 };

    XMFLOAT2 secondPos = { _pos.x - SHIFT_STRING,_pos.y - SHIFT_STRING };

    m_device.spriteFont->DrawString(m_device.spriteBatch, _string, secondPos, GetColorWithalpha(_alpha, _color), _rotation, origin, _scale);

}

void StringDrawer::DrawStringTitleForNumber(const int _num, const XMFLOAT2& _pos, const float _scale, const float _alpha, const XMVECTORF32 _color, const float _rotation)
{
    const XMFLOAT2& origin = { 0,0 };

    XMFLOAT2 secondPos = { _pos.x - SHIFT_STRING,_pos.y - SHIFT_STRING };
    std::string str = std::to_string(_num);
    m_device.spriteFont->DrawString(m_device.spriteBatch, str.c_str(), secondPos, GetColorWithalpha(_alpha, _color), _rotation, origin, _scale);

}


//  •‚¢‰e•t‚«‰©F®”‚Ì•`‰æ
void StringDrawer::DrawStringBlackAndWhiteForNumber(const int _num, const XMFLOAT2& _pos, const float _scale, const float _alpha, const float _rotation)
{
    const XMFLOAT2& origin = { 0,0 };

    std::string str = std::to_string(_num);
    XMFLOAT2 secondPos = { _pos.x - SHIFT_STRING,_pos.y - SHIFT_STRING };
    m_device.spriteFont->DrawString(m_device.spriteBatch, str.c_str(), _pos, Colors::Black, _rotation, origin, _scale);
    m_device.spriteFont->DrawString(m_device.spriteBatch, str.c_str(), secondPos, Colors::White, _rotation, origin, _scale);
}

//  •‚¢‰e•t‚«‰©F¬”‚Ì•`‰æ
void StringDrawer::DrawStringBlackAndWhiteForFewNumber(const float _num, const XMFLOAT2& _pos, const float _scale, const float _alpha, const float _rotation)
{
    const XMFLOAT2& origin = { 0,0 };

    std::string str = std::to_string(_num);
    XMFLOAT2 secondPos = { _pos.x - SHIFT_STRING,_pos.y - SHIFT_STRING };
    m_device.spriteFont->DrawString(m_device.spriteBatch, str.c_str(), _pos, GetColorWithalpha(_alpha, Colors::Black), _rotation, origin, _scale);
    m_device.spriteFont->DrawString(m_device.spriteBatch, str.c_str(), secondPos, GetColorWithalpha(_alpha, Colors::White), _rotation, origin, _scale);
}

XMVECTORF32 StringDrawer::GetColorWithalpha(const float _alpha, const XMVECTORF32 _color)
{
    
        return { _color.f[0],_color.f[1],_color.f[2],_alpha };
    
}
