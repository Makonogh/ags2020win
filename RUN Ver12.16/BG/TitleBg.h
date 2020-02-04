#pragma once
#include "Bg.h"
#include <tuple>
#include <map>



enum class TITLE_TYPE
{
	BG0,
	BG1,
	BG2,
	BG3,
	BG4,
	BG5,
	BG6,
	BG7,
	BG8,
	BG9,
	BG10,
	BG11,
	BG12,
	BG13,
	BG14,
	BG15,
	TEXT,
	TITLE,
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

