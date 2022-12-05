#pragma once
class UIHeader
{
public:
	UIHeader();
	~UIHeader();

private:
	UIHeader* m_beforeHeader;
	UIHeader* m_afterHeader;
};

UIHeader::UIHeader()
{
}

UIHeader::~UIHeader()
{
}