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
void StringDrawer::DrawStringBlackAndYellow(const char* _string, const XMFLOAT2& _pos, const float _scale, const float _alfa, const float _rotation)
{
    const XMFLOAT2& origin = { 0,0 };

    XMFLOAT2 secondPos = { _pos.x - SHIFT_STRING,_pos.y - SHIFT_STRING };
    m_device.spriteFont->DrawString(m_device.spriteBatch, _string, _pos, DirectX::Colors::Black, _rotation, origin, _scale);
    m_device.spriteFont->DrawString(m_device.spriteBatch, _string, secondPos, DirectX::Colors::White , _rotation, origin, _scale);
}

//  •‚¢‰e•t‚«‰©F®”‚Ì•`‰æ
void StringDrawer::DrawStringBlackAndYellowForNumber(const int _num, const XMFLOAT2& _pos, const float _scale, const float _alfa, const float _rotation)
{
    const XMFLOAT2& origin = { 0,0 };

    std::string str = std::to_string(_num);
    XMFLOAT2 secondPos = { _pos.x - SHIFT_STRING,_pos.y - SHIFT_STRING };
    m_device.spriteFont->DrawString(m_device.spriteBatch, str.c_str(), _pos, DirectX::Colors::Black, _rotation, origin, _scale);
    m_device.spriteFont->DrawString(m_device.spriteBatch, str.c_str(), secondPos, DirectX::Colors::White, _rotation, origin, _scale);
}

//  •‚¢‰e•t‚«‰©F¬”‚Ì•`‰æ
void StringDrawer::DrawStringBlackAndYellowForFewNumber(const float _num, const XMFLOAT2& _pos, const float _scale, const float _alfa, const float _rotation)
{
    const XMFLOAT2& origin = { 0,0 };

    std::string str = std::to_string(_num);
    XMFLOAT2 secondPos = { _pos.x - SHIFT_STRING,_pos.y - SHIFT_STRING };
    m_device.spriteFont->DrawString(m_device.spriteBatch, str.c_str(), _pos, DirectX::Colors::Black, _rotation, origin, _scale);
    m_device.spriteFont->DrawString(m_device.spriteBatch, str.c_str(), secondPos, DirectX::Colors::White, _rotation, origin, _scale);
}
