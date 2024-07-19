#pragma once
#include <d2d1.h>
static std::string WStringToString(const std::wstring& wstr)
{
	std::string convertedString(wstr.begin(), wstr.end());
	return convertedString;
}

enum class Color
{
	RED = D2D1::ColorF::Red,
	BLACK = D2D1::ColorF::Black,
	WHITE = D2D1::ColorF::White,
	BLUE = D2D1::ColorF::Blue,
	GREEN = D2D1::ColorF::Green
};