#pragma once
#include "common/Vector2.h"
#include <memory>

#define UI_SIZE_X 1280
#define UI_SIZE_Y 144

enum class UI_STATE
{
	IMAGE,
	POS,
	SIZE,
};

class UI
{
public:
	UI();
	virtual void Updata();
	void Draw(void);
	virtual ~UI();
private:
	Vector2Dbl _pos;
};

