#pragma once
#include<string>
#include <DirectXTex.h>
class UITextParts
{
public:
	UITextParts();
	~UITextParts();

private:
	std::string m_text;
	const DirectX::XMVECTORF32 m_color;

};