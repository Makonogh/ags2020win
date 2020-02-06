#include "TitleBg.h"
#include "common/ImgMng.h"
#include "Bg.h"



TitleBg::TitleBg()
{
	
}

TitleBg::TitleBg(BG_DATA bg_data)
{
	TitleBgInit(bg_data);
}

TitleBg::~TitleBg()
{

}

bool TitleBg::TitleBgInit(BG_DATA bg_data)
{
	Img_List.insert(std::make_pair(TITLE_TYPE::BG0, "罐把攚宨0"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG1, "罐把攚宨1"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG2, "罐把攚宨2"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG3, "罐把攚宨3"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG4, "罐把攚宨4"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG5, "罐把攚宨5"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG6, "罐把攚宨6"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG7, "罐把攚宨7"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG8, "罐把攚宨8"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG9, "罐把攚宨9"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG10, "罐把攚宨10"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG11, "罐把攚宨11"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG12, "罐把攚宨12"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG13, "罐把攚宨13"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG14, "罐把攚宨14"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG15, "罐把攚宨15"));
	Img_List.insert(std::make_pair(TITLE_TYPE::TEXT, "啦馁梅侥"));
	Img_List.insert(std::make_pair(TITLE_TYPE::TITLE, "啦馁"));

	image = Img_List.at(std::get<static_cast<int>(BG_STATE::IMAGE)>(bg_data));

	_pos = std::get<static_cast<int>(BG_STATE::POS)>(bg_data);
	return false;
}

void TitleBg::Updata(void)
{
	_pos.x -= 4;
}
