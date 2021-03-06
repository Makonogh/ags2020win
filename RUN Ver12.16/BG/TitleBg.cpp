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
	Img_List.insert(std::make_pair(TITLE_TYPE::BG0, "�ްєw�i0"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG1, "�ްєw�i1"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG2, "�ްєw�i2"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG3, "�ްєw�i3"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG4, "�ްєw�i4"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG5, "�ްєw�i5"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG6, "�ްєw�i6"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG7, "�ްєw�i7"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG8, "�ްєw�i8"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG9, "�ްєw�i9"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG10, "�ްєw�i10"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG11, "�ްєw�i11"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG12, "�ްєw�i12"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG13, "�ްєw�i13"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG14, "�ްєw�i14"));
	Img_List.insert(std::make_pair(TITLE_TYPE::BG15, "�ްєw�i15"));
	Img_List.insert(std::make_pair(TITLE_TYPE::TEXT, "����÷��"));
	Img_List.insert(std::make_pair(TITLE_TYPE::TITLE, "����"));

	image = Img_List.at(std::get<static_cast<int>(BG_STATE::IMAGE)>(bg_data));

	_pos = std::get<static_cast<int>(BG_STATE::POS)>(bg_data);
	return false;
}

void TitleBg::Updata(void)
{
	_pos.x -= 4;
}
