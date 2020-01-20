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
	Img_List.insert(std::make_pair(GAME_TYPE::BG1, "πﬁ∞—îwåi1"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG2, "πﬁ∞—îwåi2"));
	Img_List.insert(std::make_pair(GAME_TYPE::BG3, "πﬁ∞—îwåi3"));

	image = Img_List.at(std::get<static_cast<int>(BG_STATE::IMAGE)>(bg_data));

	_pos = std::get<static_cast<int>(BG_STATE::POS)>(bg_data);
	return false;
}

void GameBg::Updata(void)
{
	_pos.x -= bgSpeed;


}
