#include "GameBg.h"
#include "common/ImgMng.h"

GameBg::GameBg()
{
}

GameBg::GameBg(BG_DATA bg_data)
{
	GameBgInit(bg_data);
}


GameBg::~GameBg()
{
}

bool GameBg::GameBgInit(BG_DATA bg_data)
{
	Img_List.insert(std::make_pair(GAME_TYPE::BG0, "�ްєw�i0"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG1, "�ްєw�i1"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG2, "�ްєw�i2"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG3, "�ްєw�i3"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG4, "�ްєw�i4"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG5, "�ްєw�i5"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG6, "�ްєw�i6"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG7, "�ްєw�i7"));

	image = Img_List.at(std::get<static_cast<int>(BG_STATE::IMAGE)>(bg_data));

	_pos = std::get<static_cast<int>(BG_STATE::POS)>(bg_data);
	return false;
}

void GameBg::Updata(void)
{
	_pos.x -= bgSpeed;


}
