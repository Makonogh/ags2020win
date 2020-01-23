#include "ResultBg.h"
#include "common/ImgMng.h"


ResultBg::ResultBg()
{
}

ResultBg::ResultBg(BG_DATA bg_data)
{
	ResultBgInit(bg_data);
}


ResultBg::~ResultBg()
{
}

bool ResultBg::ResultBgInit(BG_DATA bg_data)
{
	Img_List.insert(std::make_pair(RESULT_TYPE::BG, "Ø»ÞÙÄ”wŒi"));
	image = Img_List.at(std::get<static_cast<int>(BG_STATE::IMAGE)>(bg_data));
	_pos = std::get<static_cast<int>(BG_STATE::POS)>(bg_data);

	return false;
}

void ResultBg::Updata(void)
{
}

