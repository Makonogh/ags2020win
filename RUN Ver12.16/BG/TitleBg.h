#pragma once
#include "Bg.h"
#include <tuple>
#include <map>



enum class TITLE_TYPE
{
	TEXT,
	BG,
	MAX,
};

using BG_STATE = std::tuple<TITLE_TYPE,Vector2Dbl,Vector2Dbl>;					// <‰æ‘œÀ²ÌßAÀ•WA»²½Þ>

class TitleBg :
	public Bg
{
public:
	TitleBg();
	TitleBg(BG_STATE);
	~TitleBg();
private:
	bool TitleBgInit(BG_STATE);
	std::map<TITLE_TYPE, std::string> Img_List;			// 
};

