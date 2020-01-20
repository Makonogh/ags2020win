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

using BG_DATA = std::tuple<TITLE_TYPE, Vector2Dbl, Vector2>;					// <‰æ‘œÀ²ÌßAÀ•WA»²½Þ>

class TitleBg :
	public Bg
{
public:
	TitleBg();
	TitleBg(BG_DATA);
	~TitleBg();
private:
	bool TitleBgInit(BG_DATA);
	void Updata(void);
	std::map<TITLE_TYPE, std::string> Img_List;		
};

