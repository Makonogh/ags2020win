#pragma once
#include "common/Vector2.h"
#include <memory>

#define STAGE_SIZE_X 640
#define STAGE_SIZE_Y 216

class Bg;
using shared_BG = std::shared_ptr<Bg>;

enum class BG_TYPE
{
	TITLE,
	GAME,
	RESULT,
	MAX
};

class Bg
{
public:
	Bg();
	virtual void Updata();
	void Draw(void);
	void Draw(int id);
	virtual ~Bg();
	int bgSpeed;
private:
	unsigned int _animFrame;							// なんﾌﾚｰﾑか
	unsigned int _animCount;							// 見出しから何回ﾙｰﾌﾟしてるか
protected:
	Vector2Dbl _pos;
	Vector2Dbl _size;
	int _zOrder;										// 描画優先度
};

