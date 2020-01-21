#pragma once
#include "Bg.h"
#include <map>
#include <tuple>

enum class GAME_TYPE
{
	BG0,
	BG1,
	BG2,
	BG3,
	BG4,
	BG5,
	BG6,
	BG7,
	MAX
};


using BG_DATA = std::tuple<GAME_TYPE, Vector2Dbl, Vector2>;					// <‰æ‘œÀ²ÌßAÀ•WA»²½Þ>

class GameBg :
	public Bg
{
public:
	GameBg();
	GameBg(BG_DATA bg_data);
	~GameBg();
private:
	bool GameBgInit(BG_DATA bg_data);
	void Updata(void);
	std::map<GAME_TYPE, std::string> Img_List;
};

