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
	Img_List.insert(std::make_pair(GAME_TYPE::BG0, "罐把攚宨0"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG1, "罐把攚宨1"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG2, "罐把攚宨2"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG3, "罐把攚宨3"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG4, "罐把攚宨4"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG5, "罐把攚宨5"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG6, "罐把攚宨6"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG7, "罐把攚宨7"));

	image = Img_List.at(std::get<static_cast<int>(BG_STATE::IMAGE)>(bg_data));

	_pos = std::get<static_cast<int>(BG_STATE::POS)>(bg_data);
	return false;
}

void GameBg::Updata(void)
{
	_pos.x -= bgSpeed;


}
