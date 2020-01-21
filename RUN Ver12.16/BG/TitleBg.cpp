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
	Img_List.insert(std::make_pair(TITLE_TYPE::BG, "À²ÄÙ”wŒi"));
	Img_List.insert(std::make_pair(TITLE_TYPE::TEXT, "À²ÄÙÃ·½Ä"));
	Img_List.insert(std::make_pair(TITLE_TYPE::TITLE, "À²ÄÙ"));

	image = Img_List.at(std::get<static_cast<int>(BG_STATE::IMAGE)>(bg_data));

	_pos = std::get<static_cast<int>(BG_STATE::POS)>(bg_data);
	return false;
}

void TitleBg::Updata(void)
{
}
