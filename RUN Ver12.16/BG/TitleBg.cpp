#include "TitleBg.h"
#include "common/ImgMng.h"



TitleBg::TitleBg()
{
	TitleBgInit();
}

TitleBg::TitleBg(BG_STATE bg_state)
{
	TitleBgInit(bg_state);
}

TitleBg::~TitleBg()
{
}

bool TitleBg::TitleBgInit(BG_STATE bg_state)
{
	Img_List.insert(std::make_pair(TITLE_TYPE::BG, "���ٔw�i"));
	Img_List.insert(std::make_pair(TITLE_TYPE::TEXT, "����÷��"));

	image = Img_List.at(std::get<static_cast<int>(STATE::IMAGE)>(bg_state));
	return false;
}
