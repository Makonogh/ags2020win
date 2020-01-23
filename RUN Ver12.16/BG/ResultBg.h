#pragma once
#include "Bg.h"
class ResultBg :
	public Bg
{
	enum class TITLE_TYPE
	{
		BG,
		MAX,
	};
public:
	ResultBg();
	~ResultBg();
private:
	bool ResultBgInit();
};

