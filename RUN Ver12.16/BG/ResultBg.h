#pragma once
#include "Bg.h"
#include <tuple>
#include <map>

enum class RESULT_TYPE
{
	BG,
	MAX,
};

using BG_DATA = std::tuple<RESULT_TYPE, Vector2Dbl, Vector2>;

class ResultBg :
	public Bg
{


public:
	ResultBg();
	ResultBg(BG_DATA bg_data);
	~ResultBg();
private:
	bool ResultBgInit(BG_DATA bg_data);
	void Updata(void);
	std::map<RESULT_TYPE, std::string> Img_List;
};

